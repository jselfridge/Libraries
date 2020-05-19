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
void     mat_LU       ( matrix* mat, matrix** L, matrix** U );                  // optimize
void     mat_LDU      ( matrix* mat, matrix** L, matrix** D, matrix** U );      // optimize
void     mat_QR       ( matrix* mat, matrix** Q, matrix** R );                  // optimize and short matrices
matrix*  mat_tri2vec  ( matrix* tri );
matrix*  mat_vec2tri  ( matrix* vec );


// Under development
// void     mat_chol    ( float a[], uint n, uint nn, float u[], uint* nullty, uint* ifault );
// void     mat_syminv  ( float a[], uint n, float c[], float w[], uint* nullty, uint* ifault );


#endif



