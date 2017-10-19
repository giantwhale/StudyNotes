from distutils.core import setup, Extension
from Cython.Build import cythonize


from distutils.core import setup, Extension
from Cython.Build import cythonize

import os
os.environ['CPPFLAGS'] = '-fPIC --std=c++11'


ext = Extension(
    name='array_wrapper',
    sources=['array_wrapper.pyx'],
    language='c++',
    # extra_compiler_args=['--std=c++11'],
    extra_link_args=['--std=c++11'],
)

setup(
    name='Python Object Makers',
    ext_modules=cythonize([ext]),
)
