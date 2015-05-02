
MatLib
======

This directory is C code for a static library that delivers linear 
algebra functionality.  The functions are grouped in the following 
categories:

      MatManip    - Matrix input, output and general manipulations
      MatComplex  - Similar to MatManip, but for complex matrices
      MatVec      - Operations appplied to vectors
      MatArith    - Arithmetic and matrix math functions

The primary intention is to keep this as a static library which 
can be referenced throughout multiple projects.  The command:

      ar -cvq libMat.a *.o

is run in the <code>makefile</code>, which generates a static 
library that can be included in other projects.


<!--
    MatProp   - Properties of a matrix
    MatDecomp - Useful matrix decompositions
-->



