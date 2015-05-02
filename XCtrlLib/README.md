
CtrlLib
=======

This directory is C code for a static library that contains functions 
for controls analysis and development.  


<!--

The only function currently 
under development is a linearization algorithm which takes a 
nonlinear system and linearizes around and operating point.



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

-->