
matLib
======

This directory is C code for a static library that delivers linear 
algebra functionality.  The functions are grouped in the following 
categories:

      matManip    - Matrix input, output and general manipulations
      matComplex  - Similar to MatManip, but for complex matrices
      matVec      - Operations appplied to vectors
      matArith    - Arithmetic and matrix math functions
      matRoot     - Method to find complex roots of a polynomial

The primary intention is to keep this as a static library which 
can be referenced throughout multiple projects.  The command:

      ar -cvq libmat.a *.o

is run in the <code>makefile</code>, which generates a static 
library that can be included in other projects. 


<!--
    matProp   - Properties of a matrix
    matDecomp - Useful matrix decompositions
-->



