Cython
===========================================================

Compile Cython Scripts
-----------------------------------------------------------

### The Standard Way - Using distutils with cythonize

`distutils` compiles projects via pipelines. For `Cython`, the first pipeline stage is done by
the `cythonize` command which converts Cython source code into `C/C++`.

    # === helloworld.pyx ===
    print("Hello World")

    # === setup.py ===
    from distutils.core import setup
    from Cython.Build import cythonize

    setup(ext_modules=cythonize('script.pyx'))

#### Compiling with distutils on Linux

The Cython extension can be build by:

    $ python setup.py build_ext --inplace
    $ python
    Python 3.5.2 |Anaconda custom (64=bit) ...
    [GCC 4.4.7 20120313 (Red Hat 4.4.7-1)] on linux
    ...
    >>> import helloworld
    hello world

The `build_ext` command instructs `distutils` to build the `Extension` object or objects that the
`cythonize` call created. The optinal `--inplace` instructs `distutils` to place each extension
module next to its respective `Cython` `.pyx` source file. On my Linux, the following files will be
created:

    build/  # contains .o files
    helloworld.cpython-35m-x86_64-linux-gnu.so
    helloworld.c


#### Compiling with distutils on Windows

On Windows, one shall compile `Cython` scripts using mingw32 or MSVC (recommended).

    python setup.py build_ext -i --compiler=mingw32 -DMS_WIN64
    python setup.py build_ext -i --compiler=msvc -DMS_WIN64

#### Compiling with Pre-compiled Dynamic Library

If we are given a pre-compiled dynamic library `libhw.so` rather than source code, we can instruct `distutils` to link against `libhw.so` at link time.

    from distuils.core import setup, Extension
    from Cython.Build import cythonize

    ext = Extension(name='wrap_hw',
                    sources=['wrap_hw.pyx'],
                    library_dirs=['/path/to/libhw.so'],
                    libraries=['hw'])
    setup(ext_modules=cythonize(ext))

** Unfinished **

#### Compile by Hand

**Step 1** convert `Cython` code into `C/C++` scripts:

    cython helloworld.pyx           # generates helloworld.c
    cython --cplus helloworld.pyx   # generates helloworld.cpp

Simply type `cython` in the terminal to get a list of options.

**Step 2** build the shared library:

    # Linux
    $ CFLAGS=$(python-config --cflags)
    $ LDFLAGS=$(python-config --ldflags)
    $ cython helloworld.pyx  # output helloworld.c
    $ gcc -c helloworld.c ${CFLAGS}  # output helloworld.o
    $ gcc helloworld.o -o hw.so -shared ${LDFLAGS}  $ output hw.so

#### Using Cython and CMake

Unfinished

Cython Syntax
-----------------------------------------------------------

### Static type declaration with `cdef`

Simple types:

    cdef int i
    cdef float k

    cdef int i, j k
    cdef int i = 0, k = 0
    cdef float price = 0.0

    def integrate(a, b, f):
        cdef:
            int i
            int N = 2000,
            float dx, s = 0.0
        # ...

More types:

    # pointer 
    cdef int *p
    cdef void **buf = NULL

    # stack-allocated C arrays
    cdef int arr[10]
    cdef double points[20][30]

    # typedefined aliases types
    cdef size_t len

    # Compound types (structs and unions)
    cdef tm time_struct
    cdef int_short_union_t hi_lo_btypes

    # Function pointers
    cdef void (*f)(int, double)
    cdef int (*signal(int (*f)(int))(int)

### More on Pointers

Use `&` to get the address of a variable:

    cdef double golden_ratio
    cdef double *p_double
    p_double = &golden_ratio

Cython does not support `*` operator for pointers, instead, we index into the pointer at location 0 to dereference a pointer in Cython.

    p_double[0] = 1.618
    print(golden_ratio)

Cython does not support `->` for pointer to `C` `struct`s. Instead we use dot access *whether we have a nonpointer struct variable or a pointer to a struct*:

    cdef st_t *p_st = make_struct()
    cdef int a_doubled = p_st.a + p_st.a

