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
#include "matManip.h"


// Function within matVec
matrix*  mat_skew   ( matrix* vec );
matrix*  mat_sskew  ( matrix* vec );
matrix*  mat_cross  ( matrix* vecA, matrix* vecB );
float    mat_dot    ( matrix* vecA, matrix* vecB );
float    mat_mag    ( matrix* vec );
float    mat_norm   ( matrix* vec, uint p );
matrix*  mat_uvec   ( matrix* vec );
matrix*  mat_proj   ( matrix* u, matrix *v );


#endif



