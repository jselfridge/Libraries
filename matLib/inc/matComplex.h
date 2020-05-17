/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matComplex.h
* Header file for the 'matComplex' library functions.
*
*******************************************************************************/
#ifndef MAT_COMPLEX_H
#define MAT_COMPLEX_H


// Standard includes
#include <math.h>
#include <string.h>


// Library includes
#include "matCommon.h"


// Function declarations
matrixz*  mat_initz   ( uint rows, uint cols );
void      mat_clearz  ( matrixz* mat );
void      mat_printz  ( matrixz* mat );
matrixz*  mat_readz   ( char* file );
void      mat_writez  ( matrixz* mat, char* file );
float     mat_getre   ( matrixz* mat, uint row, uint col );
float     mat_getim   ( matrixz* mat, uint row, uint col );
matrixz*  mat_getrz   ( matrixz* mat, uint row );
matrixz*  mat_getcz   ( matrixz* mat, uint col );
void      mat_setz    ( matrixz* mat, uint row, uint col, float re, float im );
void      mat_setrz   ( matrixz* mat, uint row, matrixz* vec );
void      mat_setcz   ( matrixz* mat, uint col, matrixz* vec );


#endif



