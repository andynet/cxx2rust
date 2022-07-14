#include "demo/include/intvec.h"
#include "demo/src/main.rs.h"
#include <algorithm>
#include <cstdint>
#include <functional>
#include <set>
#include <string>
#include <unordered_map>

namespace org {
namespace intvec {

class IntVector {
public:
    IntVector();
    uint64_t size() const;
    uint64_t width() const;
    uint64_t at(uint64_t i) const;
};

} // namespace intvec
} // namespace org
