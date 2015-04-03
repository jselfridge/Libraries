
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  RotLib.h
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _ROTLIB_H
#define _ROTLIB_H


//  Standard includes
#include <math.h>
#include <stdio.h>


// Custom includes
#include "../MatLib/MatLib.h"


// Precompiled define
#define PI  M_PI
#define PI2 (2.0*PI)
#define PIH (PI/2.0)
#define PIQ (PI/4.0)
#define PIE (PI/8.0)
#define PIS (PI/16.0)


// RotConv functions
matrix*  rot_d2r( matrix* deg );
matrix*  rot_r2d( matrix* rad );
matrix*  rot_wrappi( matrix* rad );
matrix*  rot_wrap2pi( matrix* rad );


// RotEuler functions
matrix* rot_xaxis  ( double angle );
matrix* rot_yaxis  ( double angle );
matrix* rot_zaxis  ( double angle );
matrix* rot_eul    ( matrix* att );


// RotQuat functions
matrix* rot_e2q    ( matrix* att );
matrix* rot_q2e    ( matrix* quat );
matrix* rot_q2dcm  ( matrix* quat );
matrix* rot_vec2q  ( matrix* vecA, matrix* vecB );
matrix* rot_qskew  ( matrix* quat );
matrix* rot_qmul   ( matrix* quatA, matrix* quatB );
matrix* rot_qderiv ( matrix* quat );


#endif



