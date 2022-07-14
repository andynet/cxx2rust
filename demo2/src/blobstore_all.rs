#pragma once
#include "rust/cxx.h"
#include <memory>

namespace org {
namespace blobstore {

struct MultiBuf;
struct BlobMetadata;

class BlobstoreClient {
public:
  BlobstoreClient();
  uint64_t put(MultiBuf &buf) const;
  void tag(uint64_t blobid, rust::Str tag) const;
  BlobMetadata metadata(uint64_t blobid) const;

private:
  class impl;
  std::shared_ptr<impl> impl;
};

std::unique_ptr<BlobstoreClient> new_blobstore_client();

} // namespace blobstore
} // namespace org
#include "demo/include/blobstore.h"
#include "demo/src/main.rs.h"
#include <algorithm>
#include <functional>
#include <set>
#include <string>
#include <unordered_map>

namespace org {
namespace blobstore {

// Toy implementation of an in-memory blobstore.
//
// In reality the implementation of BlobstoreClient could be a large complex C++
// library.
class BlobstoreClient::impl {
  friend BlobstoreClient;
  using Blob = struct {
    std::string data;
    std::set<std::string> tags;
  };
  std::unordered_map<uint64_t, Blob> blobs;
};

BlobstoreClient::BlobstoreClient() : impl(new class BlobstoreClient::impl) {}

// Upload a new blob and return a blobid that serves as a handle to the blob.
uint64_t BlobstoreClient::put(MultiBuf &buf) const {
  std::string contents;

  // Traverse the caller's chunk iterator.
  //
  // In reality there might be sophisticated batching of chunks and/or parallel
  // upload implemented by the blobstore's C++ client.
  while (true) {
    auto chunk = next_chunk(buf);
    if (chunk.size() == 0) {
      break;
    }
    contents.append(reinterpret_cast<const char *>(chunk.data()), chunk.size());
  }

  // Insert into map and provide caller the handle.
  auto blobid = std::hash<std::string>{}(contents);
  impl->blobs[blobid] = {std::move(contents), {}};
  return blobid;
}

// Add tag to an existing blob.
void BlobstoreClient::tag(uint64_t blobid, rust::Str tag) const {
  impl->blobs[blobid].tags.emplace(tag);
}

// Retrieve metadata about a blob.
BlobMetadata BlobstoreClient::metadata(uint64_t blobid) const {
  BlobMetadata metadata{};
  auto blob = impl->blobs.find(blobid);
  if (blob != impl->blobs.end()) {
    metadata.size = blob->second.data.size();
    std::for_each(blob->second.tags.cbegin(), blob->second.tags.cend(),
                  [&](auto &t) { metadata.tags.emplace_back(t); });
  }
  return metadata;
}

std::unique_ptr<BlobstoreClient> new_blobstore_client() {
  return std::make_unique<BlobstoreClient>();
}

} // namespace blobstore
} // namespace org
#[cxx::bridge(namespace = "org::blobstore")]
mod ffi {
    // Shared structs with fields visible to both languages.
    struct BlobMetadata {
        size: usize,
        tags: Vec<String>,
    }

    // Rust types and signatures exposed to C++.
    extern "Rust" {
        type MultiBuf;

        fn next_chunk(buf: &mut MultiBuf) -> &[u8];
    }

    // C++ types and signatures exposed to Rust.
    unsafe extern "C++" {
        include!("demo/include/blobstore.h");

        type BlobstoreClient;

        fn new_blobstore_client() -> UniquePtr<BlobstoreClient>;
        fn put(&self, parts: &mut MultiBuf) -> u64;
        fn tag(&self, blobid: u64, tag: &str);
        fn metadata(&self, blobid: u64) -> BlobMetadata;
    }
}

// An iterator over contiguous chunks of a discontiguous file object.
//
// Toy implementation uses a Vec<Vec<u8>> but in reality this might be iterating
// over some more complex Rust data structure like a rope, or maybe loading
// chunks lazily from somewhere.
pub struct MultiBuf {
    chunks: Vec<Vec<u8>>,
    pos: usize,
}
pub fn next_chunk(buf: &mut MultiBuf) -> &[u8] {
    let next = buf.chunks.get(buf.pos);
    buf.pos += 1;
    next.map_or(&[], Vec::as_slice)
}

fn main() {
    let client = ffi::new_blobstore_client();

    // Upload a blob.
    let chunks = vec![b"fearless".to_vec(), b"concurrency".to_vec()];
    let mut buf = MultiBuf { chunks, pos: 0 };
    let blobid = client.put(&mut buf);
    println!("blobid = {}", blobid);

    // Add a tag.
    client.tag(blobid, "rust");

    // Read back the tags.
    let metadata = client.metadata(blobid);
    println!("tags = {:?}", metadata.tags);
}
