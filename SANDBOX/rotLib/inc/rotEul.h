/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* rotEul.h
* Header file for the 'rotEul' library functions.
*
*******************************************************************************/
#ifndef ROT_EUL_H
#define ROT_EUL_H


// Standard includes
//#include <math.h>
//#include <stdio.h>


// Function declarations
matrix*  rot_xaxis  ( float angle );
matrix*  rot_yaxis  ( float angle );
matrix*  rot_zaxis  ( float angle );
matrix*  rot_eul    ( matrix* att  );


#endif



