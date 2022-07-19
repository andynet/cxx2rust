#pragma once
#include "rust/cxx.h"
#include <memory>

namespace org {
namespace intvec {

class IntVector {
public:
    IntVector(uint64_t size, uint64_t default_value, uint8_t int_width);
    uint64_t size() const;
    uint8_t width() const;

private:
    class impl;
    std::shared_ptr<impl> impl;
};

// size: u64, default_val: u64, width: u64
std::unique_ptr<IntVector> new_int_vector(uint64_t, uint64_t, uint64_t);

} // namespace intvec
} // namespace org
