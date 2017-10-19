from cython.operator cimport dereference as deref

cdef class CArray:

    def __cinit__(self, size_t len=0, double v=0.0):
        if len > 0:
            self.c_array = new Array(len, v)
        else:
            self.c_array = NULL

    def __dealloc__(self):
        del self.c_array

    cdef set_obj(self, Array *arr):
        if self.c_array != NULL:
            del self.c_array
        self.c_array = arr

    def __add__(x, y):
        z = CArray()
        if isinstance(x, CArray):
            z.set_obj((<CArray>x).c_array[0] + <double>y)
        elif isinstance(y, CArray):
            z.set_obj((<CArray>y).c_array[0] + <double>x)
        else:
            raise NotImplementedError
        return z

    def __str__(self):
        cdef Py_ssize_t i, n
        n = self.c_array.size()
        v = []
        for i in range(n):
            v.append('%.4f' % self.c_array.at(i))
        return '[' + ' '.join(v) + ']'

    def __repr__(self):
        return self.__str__()

