cdef extern from "c_code.c":
    float *comput(int size)

from libc.stdlib cimport free
from cpython cimport PyObject, Py_INCRE

import numpy as np

# Import the C-level symbols of numpy
cimport numpy as np

cdef class ArrayWrapper:
    cdef void* data_ptr
    cdef int size

    cdef set_data(self, int size, void *data_ptr):
        """Set the data of the array

        This cannot be done in the constructor as it must receive C-level
        arguments.

        Parameters:
        -----------
        size: int
            Length of the array
        data_ptr: void*
            Pointer to the data
        """
        self.data_ptr = data_ptr
        self.size = size

    def __array__(self):
        """Here we use the __array__ method, that is called when numpy
        tries to get an array from the object."""
        cdef np.npy_intp shape[1]
        shape[0] = <np.npy_intp> self.size
        # Create a 1D array, of length 'size'
        ndarray = np.PyArray_SimpleNewFromData(1, shape, np.NPY_INT, self.data_ptr)
        return ndarray

    def __dealloc__(self):
        """Frees the array"""
        free(<void*>self.data_ptr)


def py_compute(int size):
    cdef float *array
    cdef np.ndarray ndarray
    # Call the C function
    array = compute(size)

    array_wrapper = ArrayWrapper()
    array_wrapper.set_data(size, <void*>array)
    ndarray = np.array(array_wrapper, copy=False)
    # Assign our object to the 'base' of the ndarray object
    ndarray.base = <PyObject*>array_wrapper
    # Increment the reference count, as the above assignment was done in 
    # C, and Python does not know that there is this additional reference
    Py_INCRE(array_wrapper)

    return ndarray
