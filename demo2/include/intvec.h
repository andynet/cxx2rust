#pragma once
#include <memory>
#include <sdsl/int_vector.hpp>

class IntVector {
public:
    IntVector(uint64_t, uint64_t, uint8_t);
    uint64_t size() const;
    uint8_t width() const;
    sdsl::int_vector<> get_vector() const;

private:
    class Impl;
    std::shared_ptr<Impl> pimpl;
};

// fn new_intvec(size: u64, defval: u64, width: u8) -> UniquePtr<IntVector>;
std::unique_ptr<IntVector> new_intvec(uint64_t, uint64_t, uint8_t);

// fn test_ptr(v: &UniquePtr<IntVector>);
void test_ptr(const std::unique_ptr<IntVector>&);
