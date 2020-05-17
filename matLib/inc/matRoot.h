/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matRoot.h
* Header file for the 'matRoot' library functions.
*
*******************************************************************************/
#ifndef MAT_ROOT_H
#define MAT_ROOT_H


// Standard includes
#include <math.h>
#include <stdbool.h>


// Library includes
#include "matCommon.h"
#include "matManip.h"
#include "matComplex.h"


// Function declarations
matrixz*  mat_root  ( matrix* poly, float tol, uint max );


#endif



