#pragma once
#include "rust/cxx.h"
#include <memory>

namespace org {
namespace intvec {

void print_hello();

class int_vector {
public:
    int_vector(uint64_t size, uint64_t default_value, uint8_t int_width);
    uint64_t size() const;
    uint8_t width() const;

private:
    class impl;
    std::shared_ptr<impl> impl;
};

// size: u64, default_val: u64, width: u64
std::unique_ptr<int_vector> new_int_vector(uint64_t, uint64_t, uint64_t);

} // namespace intvec
} // namespace org
