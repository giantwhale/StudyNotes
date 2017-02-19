The Scythe Statistical Library
=========================================================

Scythe has three important components: 

* the `Matrix` class
* Pseudo-random number generators
* routines for numerical optimization


Matrix Templates
----------------------------------------------------------

Matrices may be maintained in either column-major or row-major order. Column-major is recommended as the library only takes advantage of LAPACK/BLAS functionality when working with column-major matrices. 

Scythe matrices use a "data-view" model of data management. This means that it is possible for two or more distinct Matrix objects to refer to – or view – the same underlying block of data. All views must be sub-matrices of some Matrix. It is not possible to create a view of the diagonal of a matrix.  

It is also possible to create concrete matrices using deep copies through the Matrix class's `copy()` method. 


### Matrix construction

One of the most basic `Matrix` constructor forms looks like:

    Matrix<double,Col,Concrete> M(4, 5, true, 0);

and constructs a `4x5` column-major concrete Matrix, filled with double precision floating point values, all intialized to zero. The four arguments are:

* num of rows
* num of columns
* initialize the matrix
* initialize value

The three template parameters are (always in this order):

* element type
* ordering (`Col` or `Row`)
* style (`Concrete` or `View`)

Here are some more ways to instantiate matrices:

    double vals[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    Matrix<> Xcol(3, 4, vals);

    Matrix<double,Row,View> Xrow(3, 4, false);
    Xrow = 1, 4, 7, 10, 2, 5, 8, 11, 3, 6, 9, 12;
    
    cout << Xcol << endl << Xrow;
    
    1.000000 4.000000 7.000000 10.000000
    2.000000 5.000000 8.000000 11.000000
    3.000000 6.000000 9.000000 12.000000
    
    1.000000 4.000000 7.000000 10.000000
    2.000000 5.000000 8.000000 11.000000
    3.000000 6.000000 9.000000 12.000000

File constructor: with a space-delimited, row-major ordered list of values, with one rwo per line, one can construct a Matrix object with:

    Matrix<> F("filename.txt")

(currently csv files are not supported, stay tuned.)

