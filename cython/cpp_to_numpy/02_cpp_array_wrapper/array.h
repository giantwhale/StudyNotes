#ifndef cpp_object
#define cpp_object

#include <iostream>
#include <memory>
#include <algorithm>

namespace yz {

using std::cout;
using std::endl;
using std::shared_ptr;

class Array {
public:
    Array(size_t len, double val=0.0): _len(len) {
        cout << "Constructing Array" << endl;
        _v = new double[len];
        for (size_t i=0; i<len; i++) {
            _v[i] = val;
        }
    }

    ~Array() {
        cout << "Destructing Array" << endl;
        if (_v != nullptr) {
            delete[] _v;
        }
    }

    Array() = delete;
    Array(const Array &) = delete;
    Array &operator=(Array &) = delete;

    size_t size() { return _len; }

    double at(size_t i) { return _v[i]; }

    double  operator[](size_t i) { return _v[i]; }
    // double& operator[](size_t i) { return _v[i]; }

    double* begin() { return _v; }
    double* end() { return _v + _len; }

    Array* operator+(double x);

private:
    size_t _len;
    double *_v;

};

inline Array* Array::operator+(double x) {
    Array *res = new Array(_len, 0.0);
    std::transform(begin(), end(), res->_v, [x](double y) { return x + y; });
    return res;
}


} // namespace yz


#endif 
