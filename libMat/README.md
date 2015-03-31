LinAlg_Sandbox
=============

This set of code serves as a snadbox for implementing linear
algebra functionality within the C programming language.  The
code relies on the CLAPACK library which is built upon a Basic
Linear Algebra Subroutine (BLAS) foundation.  This capability 
will be incorporated into "SampleSim" which is the sandbox 
program for developing Matlab-like capabilities within a 
C language.

Functions for future development:
double   mat_norm1   ( matrix* mat );
double   mat_norm2   ( matrix* mat );
double   mat_normi   ( matrix* mat );
double   mat_mean    ( matrix* mat );
matrix*  mat_meanr   ( matrix* mat );
matrix*  mat_meanc   ( matrix* mat );
matrix*  mat_eigval  ( matrix* mat );
matrix*  mat_eigvec  ( matrix* mat );
matrix*  mat_cov     ( matrix* mat );


