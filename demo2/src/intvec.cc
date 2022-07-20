// #include "demo2/include/intvec.h"
// #include <iostream>
// #include <sdsl/int_vector.hpp>

// namespace org {
// namespace intvec {

// std::unique_ptr<IntVector> new_int_vector(uint64_t size, uint64_t value, uint64_t width) {
//     cout << size << " " << value << " " << width << endl;
//     sdsl::int_vector<> v(size, value, int_width);
//     return std::unique_ptr<IntVector>(v);
// }

// } // namespace intvec
// } // namespace org

#include <iostream>
#include <sdsl/int_vector.hpp>
#include "demo2/include/intvec.h"

IntVector::IntVector() {
    v = sdsl::int_vector<>(8, 0, 2);
}

std::unique_ptr<IntVector> new_intvec() {
  return std::unique_ptr<IntVector>(new IntVector());
}

void test_ptr(std::unique_ptr<IntVector> pv) {
    sdsl::int_vector<> v = (*pv).v;

    for (size_t i=0; i<v.size(); i++) {
        v[i] = i;
    }

    std::cout << "created int_vector<> containing " << v.size() << " " << (int)v.width() << "-bit integers" << std::endl;

    for (size_t i=0; i<v.size(); i++) {
        std::cout << "v[" << i << "]=" << v[i] << std::endl;
    }
}
