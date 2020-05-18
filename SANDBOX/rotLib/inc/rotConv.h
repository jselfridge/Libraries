/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* rotConv.h
* Header file for the 'rotConv' library functions.
*
*******************************************************************************/
#ifndef ROT_CONV_H
#define ROT_CONV_H


// Standard includes
//#include <math.h>
//#include <stdio.h>


// Function declarations
matrix*  rot_deg2rad  ( matrix* deg );
matrix*  rot_rad2deg  ( matrix* rad );
void     rot_wrappi   ( matrix* rad );
void     rot_wrap2pi  ( matrix* rad );


#endif



