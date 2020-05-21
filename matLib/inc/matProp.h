/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matProp.h
* Header file for the 'matProp' library functions.
*
*******************************************************************************/
#ifndef MAT_PROP_H
#define MAT_PROP_H


// Standard includes
#include <math.h>
#include <stdbool.h>


// Library includes
#include "matCommon.h"
#include "matDecomp.h"


// Function declarations
float  mat_det    ( matrix* A );
float  mat_trace  ( matrix* A );
bool   mat_sym    ( matrix** A, float tol );


#endif



