OptLib
======

This directory is C code for a static library that
contains optimization functions.  The only function
currently under development is the gradient method
(or method of steepest descent) for solving an 
unconstrained minimization problem.





COPIED FROM MATLIB

This directory is C code for a static library that 
delivers linear algebra functionality.  The 
functions are grouped in the following categories:

    MatIO     - Input and output capabilities
    MatManip  - Manipulations and matrix modifications
    MatVec    - Operations with vectors
    MatArith  - Arithmetic and matrix math functions
    MatProp   - Properties of a matrix
    MatDecomp - Decompositions for det() and inv()

The primary intention is to keep this as a static 
library that can be referenced throughout multiple
projects.  The command:

    ar -cvq libMat.a *.o

is used to generate the static library.  It is
included in the 'makefile' and places the 
library in the appropriate folder.

Functions for future development:
double   mat_mean    ( matrix* mat );  
matrix*  mat_meanr   ( matrix* mat );  
matrix*  mat_meanc   ( matrix* mat );  
matrix*  mat_eigval  ( matrix* mat );  
matrix*  mat_eigvec  ( matrix* mat );  
matrix*  mat_cov     ( matrix* mat );  



