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
matrix*  mat_add      ( matrix* A, matrix* B );
matrix*  mat_sub      ( matrix* A, matrix* B );
matrix*  mat_emul     ( matrix* A, matrix* B );
matrix*  mat_ediv     ( matrix* A, matrix* B );
matrix*  mat_mul      ( matrix* A, matrix* B );
matrix*  mat_inv      ( matrix* A );
matrix*  mat_divL     ( matrix* A, matrix* B );
matrix*  mat_divR     ( matrix* A, matrix* B );
matrix*  mat_epow     ( matrix* A, uint power );
matrix*  mat_pow      ( matrix* A, uint power );
matrix*  mat_abs      ( matrix* A );
matrix*  mat_trans    ( matrix* A );
matrix*  mat_reshape  ( matrix* A, uint r, uint c );


#endif



