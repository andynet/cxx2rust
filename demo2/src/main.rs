#[cxx::bridge(namespace = "org::intvec")]
mod ffi {
    // Shared structs with fields visible to both languages.
    struct IntVector {
        size: usize,
        tags: Vec<String>,
    }

    // C++ types and signatures exposed to Rust.
    unsafe extern "C++" {
        // include!("demo/include/blobstore.h");
        include!("/usr/local/include/sdsl/int_vector.hpp");

        // type BlobstoreClient;
        type IntVector;

        fn load_from_file(self: Pin<&mut IntVector>, file: &str);
        fn size(&self);
        fn width(&self);
        fn at(&self, i: usize);
    }
}

fn main() {
    let v = ffi::int_vector();  // int_vector<> v;
    ffi::load_from_file(v, "data/intvec.dat");
    println!("loaded int_vector<> containing {} {}-bit integers.", v.size(), v.width());

    for i in 0..v.size() {
        println!("v[{}]={}", i, v.at(i))
    }
}
