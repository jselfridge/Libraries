
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  RotLib.h
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _ROTLIB_H
#define _ROTLIB_H


//  Standard includes
#include <math.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>


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
//Eul2Q();
//Q2DCM();
//Q2Eul();
//QDeriv();
//QMat();
//Vec2Q();


/*
//  MatArith functions
matrix*  mat_add    ( matrix* matA, matrix* matB );
matrix*  mat_sub    ( matrix* matA, matrix* matB );
matrix*  mat_mul    ( matrix* matA, matrix* matB );
matrix*  mat_pow    ( matrix* mat, int power );
matrix*  mat_trans  ( matrix* mat );
matrix*  mat_skew   ( matrix* vec );
matrix*  mat_cross  ( matrix* vecA, matrix* vecB );
double   mat_dot    ( matrix* vecA, matrix* vecB );
*/


#endif



