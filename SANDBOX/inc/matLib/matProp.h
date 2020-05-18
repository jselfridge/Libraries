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
float  mat_det    ( matrix* mat );
float  mat_trace  ( matrix* mat );
bool   mat_sym    ( matrix* mat, float tol );


#endif



