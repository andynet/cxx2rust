#pragma once
#include <memory>
#include <sdsl/int_vector.hpp>

class IntVector {
public:
    IntVector();
};

std::unique_ptr<IntVector> new_intvec();

void test(uint64_t size, uint64_t width);


// #pragma once
// #include "rust/cxx.h"
// #include <memory>

// namespace org {
// namespace intvec {

// std::unique_ptr<IntVector> new_int_vector(uint64_t size, uint64_t value, uint64_t width);

// } // namespace intvec
// } // namespace org
