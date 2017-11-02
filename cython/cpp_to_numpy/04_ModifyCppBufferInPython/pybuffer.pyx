import numpy


cdef class BufferWrapper:

    def __cinit__(self):
        self.buf = new Buffer()

    def __dealloc__(self):
        if self.buf != NULL:
            del self.buf
    
    def printString(self):
        self.buf.printString()

    def __setitem__(self, key, item):
        key = int(key)
        item = int(item)
        assert 0 <= key < 10, '0 <= key < 10'
        self.buf[0][key] = item

    def get_array(self):
        cdef object arr
        arr = <object>self.buf.to_array()
        return numpy.asarray(arr)
