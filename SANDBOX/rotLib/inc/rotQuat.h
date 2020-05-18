/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* rotQuat.h
* Header file for the 'rotQuat' library functions.
*
*******************************************************************************/
#ifndef ROT_QUAT_H
#define ROT_QUAT_H


// Standard includes
//#include <math.h>
//#include <stdio.h>


// Function declarations
matrix*  rot_qDef    ( float rot, matrix* vec );
matrix*  rot_qConj   ( matrix* quat );
matrix*  rot_e2q     ( matrix* att  );
matrix*  rot_q2e     ( matrix* quat );
matrix*  rot_q2dcm   ( matrix* quat );

matrix*  rot_vec2q   ( matrix* vecA, matrix* vecB );
matrix*  rot_vec2e   ( matrix* vecA, matrix* vecB );
matrix*  rot_qskew   ( matrix* quat );
matrix*  rot_qmul    ( matrix* quatA, matrix* quatB );
matrix*  rot_qderiv  ( matrix* quat );


#endif



