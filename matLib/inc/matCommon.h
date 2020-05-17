/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matCommon.h
* Header file which provides common features across the 'matLib' library.
*
*******************************************************************************/
#ifndef MAT_COMMON_H
#define MAT_COMMON_H


// Standard includes
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>


// Matrix (real) structure
typedef struct matrix {
  uint    rows;
  uint    cols;
  float*  data;
} matrix;


// Matrix (complex) structure
typedef struct matrixz {
  uint            rows;
  uint            cols;
  float complex*  data;
} matrixz;


// Error message macro
#define  mat_err( cond, msg )  ({               \
           if(cond) {                           \
             fprintf( stderr, "%s\n\n", msg );  \
             exit(1);                           \
           }                                    \
         })


#endif



