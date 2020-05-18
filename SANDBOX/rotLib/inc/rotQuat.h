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
matrix*  rot_qProd   ( matrix* a, matrix* b );
matrix*  rot_qDeriv  ( matrix* quat, matrix* ang );
matrix*  rot_vec2q   ( matrix* a, matrix* b );
matrix*  rot_dRqw    ( matrix* quat );
matrix*  rot_dRqx    ( matrix* quat );
matrix*  rot_dRqy    ( matrix* quat );
matrix*  rot_dRqz    ( matrix* quat );


// Work in progress
//matrix*  rot_dRot    ( matrix* quat );


#endif



