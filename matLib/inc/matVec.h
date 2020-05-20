/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matVec.h
* Header file for the 'matVec' library functions.
*
*******************************************************************************/
#ifndef MAT_VEC_H
#define MAT_VEC_H


// Standard includes
#include <math.h>
#include <string.h>


// Library includes
#include "matCommon.h"
// #include "matManip.h"


// Function declarations
matrix*  mat_skew   ( matrix* V );
matrix*  mat_sskew  ( matrix* V );
matrix*  mat_cross  ( matrix* A, matrix* B );
float    mat_dot    ( matrix* A, matrix* B );
float    mat_mag    ( matrix* V );
float    mat_norm   ( matrix* V, uint p );
matrix*  mat_uvec   ( matrix* V );
matrix*  mat_proj   ( matrix* U, matrix* V );


#endif



