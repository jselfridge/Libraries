/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matArith.h
* Header file for the 'matArith' library functions.
*
*******************************************************************************/
#ifndef MAT_ARITH_H
#define MAT_ARITH_H


// Standard includes
#include <math.h>


// Library includes
#include "matCommon.h"
#include "matManip.h"
#include "matDecomp.h"


// Function declarations
matrix*  mat_add      ( matrix* matA, matrix* matB );
matrix*  mat_sub      ( matrix* matA, matrix* matB );
matrix*  mat_emul     ( matrix* matA, matrix* matB );
matrix*  mat_ediv     ( matrix* matA, matrix* matB );
matrix*  mat_mul      ( matrix* matA, matrix* matB );
matrix*  mat_inv      ( matrix* mat );
matrix*  mat_divL     ( matrix* matA, matrix* matB );
matrix*  mat_divR     ( matrix* matA, matrix* matB );
matrix*  mat_epow     ( matrix* mat, uint power );
matrix*  mat_pow      ( matrix* mat, uint power );
matrix*  mat_abs      ( matrix* mat );
matrix*  mat_trans    ( matrix* mat );
matrix*  mat_reshape  ( matrix* mat, uint rows, uint cols );


#endif



