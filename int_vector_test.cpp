#include "sdsl/int_vector.hpp"
#include <iostream>

using namespace std;
using namespace sdsl;

int main() {
    uint64_t size  = 10;
    uint64_t width = 5;
    int_vector<> v(size, 0, width);

    for (size_t i=0; i<size; i++) {
        v[i] = i;
    }

    cout << "created int_vector<> containing " << v.size() << " " << (int)v.width() << "-bit integers" << endl;

    for (size_t i=0; i<size; i++) {
        cout << "v[" << i << "]=" << v[i] << endl;
    }
}