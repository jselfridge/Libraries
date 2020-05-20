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
matrixz*  mat_initz   ( uint r, uint c );
void      mat_clearz  ( matrixz* M );
void      mat_printz  ( matrixz* M );
matrixz*  mat_readz   ( char* file );
void      mat_writez  ( matrixz* M, char* file );
float     mat_getre   ( matrixz* M, uint r, uint c );
float     mat_getim   ( matrixz* M, uint r, uint c );
matrixz*  mat_getrz   ( matrixz* M, uint r );
matrixz*  mat_getcz   ( matrixz* M, uint c );
void      mat_setz    ( matrixz* M, uint r, uint c, float re, float im );
void      mat_setrz   ( matrixz* M, uint r, matrixz* V );
void      mat_setcz   ( matrixz* M, uint c, matrixz* V );


#endif



