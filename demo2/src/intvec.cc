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

IntVector::IntVector() {}

std::unique_ptr<IntVector> new_intvec() {
  return std::unique_ptr<IntVector>(new IntVector());
}

sdsl::int_vector<> test2() {
    sdsl::int_vector<> v(5, 0, 5);
    return v;
}

std::unique_ptr<sdsl::int_vector<> > new_intvec2() {
    std::unique_ptr<sdsl::int_vector<> > pv(new sdsl::int_vector<>(8, 0, 6));
    return pv;
}

void test(uint64_t _size, uint64_t _width) {
    // sdsl::int_vector<> v(size, 0, width);
    std::unique_ptr<sdsl::int_vector<> > pv = new_intvec2();
    sdsl::int_vector<> v = *pv;

    for (size_t i=0; i<v.size(); i++) {
        v[i] = i;
    }

    std::cout << "created int_vector<> containing " << v.size() << " " << (int)v.width() << "-bit integers" << std::endl;

    for (size_t i=0; i<v.size(); i++) {
        std::cout << "v[" << i << "]=" << v[i] << std::endl;
    }
}
