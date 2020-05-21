/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matDecomp.h
* Header file for the 'matDecomp' library functions.
*
*******************************************************************************/
#ifndef MAT_DECOMP_H
#define MAT_DECOMP_H


// Library includes
#include "matCommon.h"
#include "matManip.h"
#include "matVec.h"
#include "matArith.h"


// Function declarations
matrix*  mat_tri2vec  ( matrix* tri );
float*   mat_tri2arr  ( matrix* tri );
matrix*  mat_vec2tri  ( matrix* vec );
matrix*  mat_arr2tri  ( float*  arr, uint n );
void     mat_LU       ( matrix* A, matrix** L, matrix** U );  // optimize, debug non-existance check
void     mat_LDU      ( matrix* A, matrix** L, matrix** D, matrix** U );  // optimize
void     mat_QR       ( matrix* A, matrix** Q, matrix** R );  // optimize, develop short matrices
void     mat_chol     ( float a[], uint n, float u[], uint* nullity, uint* err );


#endif



