#include <iostream>
#include <sdsl/int_vector.hpp>
#include "demo2/include/intvec.h"

class IntVector::Impl {
    friend IntVector;
    sdsl::int_vector<> v;
};

IntVector::IntVector(uint64_t s, uint64_t d, uint8_t w) {
    pimpl = std::shared_ptr<IntVector::Impl>(new IntVector::Impl());
    pimpl->v = sdsl::int_vector<>(s, d, w);
}

uint64_t IntVector::size() const {
    return pimpl->v.size();
}

uint8_t IntVector::width() const {
    return (int)pimpl->v.width();
}

sdsl::int_vector<> IntVector::get_vector() const {
    return pimpl->v;
}

std::unique_ptr<IntVector> new_intvec(uint64_t size, uint64_t defval, uint8_t width) {
    return std::unique_ptr<IntVector>(new IntVector(size, defval, width));
}

void test_ptr(const std::unique_ptr<IntVector>& pv) {
    sdsl::int_vector<> v = (*pv).get_vector();

    for (size_t i=0; i<v.size(); i++) {
        v[i] = i;
    }

    std::cout << "created int_vector<> containing " << v.size() << " " << (int)v.width() << "-bit integers" << std::endl;

    for (size_t i=0; i<v.size(); i++) {
        std::cout << "v[" << i << "]=" << v[i] << std::endl;
    }
}
