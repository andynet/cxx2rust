#include "demo2/include/intvec.h"
#include "demo2/src/main.rs.h"
#include <iostream>
#include <sdsl/int_vector.hpp>

namespace org {
namespace intvec {

// class int_vector {
// public:
//     int_vector(size_type size, value_type default_value, uint8_t int_width) {
//         return sdsl::int_vector(size, default_value, int_width);
//     }
//     size_type size() const {};
//     uint8_t width() const {};
// };

std::unique_ptr<int_vector> new_int_vector();

void print_hello() {
    std::cout << "Hello World!" << std::endl;
}

} // namespace intvec
} // namespace org
