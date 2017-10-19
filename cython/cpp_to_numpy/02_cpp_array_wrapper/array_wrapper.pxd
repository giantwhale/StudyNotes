

cdef extern from "array.h" namespace "yz":
    cdef cppclass Array:
        Array(size_t, double)
        size_t size() 
        double at(size_t)
        Array* operator+(double)


cdef class CArray:

    cdef Array* c_array

    cdef set_obj(self, Array *arr)

