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


// Standard includes
// #include <complex.h>
// #include <math.h>
// #include <stdbool.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>


// Library includes
// #include "matCommon.h"
// #include "matManip.h"


// Function declarations
void     mat_LU      ( matrix* mat, matrix* L, matrix* U );
void     mat_LDU     ( matrix* mat, matrix* L, matrix* D, matrix* U );
void     mat_QR      ( matrix* mat, matrix* Q, matrix* R );     //---  TODO: QR factorization on short matrices  ---//
void     mat_chol    ( float a[], uint n, uint nn, float u[], uint* nullty, uint* ifault );
void     mat_syminv  ( float a[], uint n, float c[], float w[], uint* nullty, uint* ifault );
matrix*  mat_tri2vec ( matrix* tri );
matrix*  mat_vec2tri ( matrix* vec );


#endif



