#ifndef BUFFER_H
#define BUFFER_H

#include <cstring>
#include <cstdint>
#include <iostream>

using namespace std;

#include <Python.h>


class Buffer {
public:
    Buffer() {
        cout << "Calling the constructor" << endl;
        data_ = new int32_t[10];
        memset(data_, 0, sizeof(int32_t) * 10);
    }

    ~Buffer() {
        cout << "Calling the destructor" << endl;
        if (data_ != nullptr) {
            delete [] data_;
        }
    }

    int32_t& operator[](int i) { return data_[i]; }

    void printString() const {
        for (size_t i=0; i<10; i++) {
            cout << data_[i] << ' ';
        }
        cout << endl;
    }

    PyObject* to_array();

private:
    int32_t * data_;

};

#endif
