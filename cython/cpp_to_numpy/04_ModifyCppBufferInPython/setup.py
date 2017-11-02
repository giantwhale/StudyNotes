from distutils.core import setup, Extension
from Cython.Build import cythonize

import numpy as np

ext = Extension(
    name='pybuffer',
    sources=['pybuffer.pyx', 'buffer.cpp'],
    language='c++',
    include_dirs=[np.get_include()],
    extra_compile_args=['-fPIC', '--std=c++11', '-g', '-O1'],
    extra_link_args=['-fPIC', '--std=c++11', '-g', '-O1'],
)

setup(
    name='pybuffer',
    ext_modules=cythonize([ext])
    )
