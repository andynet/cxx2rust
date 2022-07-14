#pragma once
#include "rust/cxx.h"
#include <memory>

namespace org {
namespace intvec {

class IntVector {
public:
    IntVector();
    uint64_t size() const;
    uint64_t width() const;
};

} // namespace intvec
} // namespace org
