from cpython.ref cimport PyObject


cdef extern from "buffer.h":
    cdef cppclass Buffer:
        Buffer()
        int & operator[](int i)
        void printString()
        PyObject* to_array()


cdef class BufferWrapper:
    cdef Buffer * buf
