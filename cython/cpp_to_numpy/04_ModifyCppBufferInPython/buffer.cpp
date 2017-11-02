#include "buffer.h"

#include <iostream> 

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#define PY_ARRAY_UNIQUE_SYMBOL yz_ARRAY_API

#include <numpy/numpyconfig.h>
#include <numpy/arrayobject.h>
#include <numpy/ufuncobject.h>

int init_numpy() {
    import_array();
    return 0;
}
static int numpy_initialized = init_numpy();


PyObject* Buffer::to_array() {
    int nd = 1;
    npy_intp dims[] = {10};
    PyObject *obj = PyArray_SimpleNewFromData(nd, &dims[0], NPY_INT32, (void *)data_);
    // PyArrayObject *arr = reinterpret_cast<PyArrayObject *>(obj);
    return obj;
}
