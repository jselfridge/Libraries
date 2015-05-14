
//============================================================
//  matLib.h
//  Justin M Selfridge
//============================================================
#ifndef _MATLIB_H_
#define _MATLIB_H_


// Standard includes
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define statements
#define PI  M_PI
#define PI2 (2.0*PI)
#define PIH (PI/2.0)
#define PIQ (PI/4.0)
#define PIE (PI/8.0)
#define PIS (PI/16.0)


//  Matrix structure declaration
typedef struct _matrix {
  int rows;
  int cols;
  double* data;
} matrix;


//  Complex structure declaration
typedef struct _matrixz {
  int rows;
  int cols;
  double complex* data;
} matrixz;


// MatManip functions
void      mat_err     ( bool cond, char* msg );
matrix*   mat_init    ( int rows, int cols );
matrix*   mat_read    ( char* file );
void      mat_print   ( matrix* mat );
void      mat_write   ( matrix* mat, char* file );
void      mat_clear   ( matrix* mat );
double    mat_get     ( matrix* mat, int row, int col );
matrix*   mat_getr    ( matrix* mat, int row );
matrix*   mat_getc    ( matrix* mat, int col );
void      mat_set     ( matrix* mat, int row, int col, double val );
void      mat_setr    ( matrix* mat, int row, matrix* vec );
void      mat_setc    ( matrix* mat, int col, matrix* vec );
matrix*   mat_copy    ( matrix* mat );
matrix*   mat_eye     ( int n );
matrix*   mat_ones    ( int rows, int cols );
matrix*   mat_scale   ( matrix* mat, double scale );
void      mat_swapr   ( matrix* mat, int p, int q );
void      mat_swapc   ( matrix* mat, int p, int q );
matrix*   mat_appr    ( matrix* matT, matrix* matB );
matrix*   mat_appc    ( matrix* matL, matrix* matR );
void      mat_rmtiny  ( matrix** mat, double tol );


// MatComplex functions
matrixz*  mat_initz   ( int rows, int cols );
matrixz*  mat_readz   ( char* file );
void      mat_printz  ( matrixz* mat );
void      mat_writez  ( matrixz* mat, char* file );
void      mat_clearz  ( matrixz* mat );
double    mat_getre   ( matrixz* mat, int row, int col );
double    mat_getim   ( matrixz* mat, int row, int col );
matrixz*  mat_getzr   ( matrixz* mat, int row );
matrixz*  mat_getzc   ( matrixz* mat, int col );
void      mat_setz    ( matrixz* mat, int row, int col, double re, double im );
void      mat_setzr   ( matrixz* mat, int row, matrixz* vec );
void      mat_setzc   ( matrixz* mat, int col, matrixz* vec );


// MatVec functions
matrix*   mat_skew    ( matrix* vec );
matrix*   mat_sskew   ( matrix* vec );
matrix*   mat_cross   ( matrix* vecA, matrix* vecB );
double    mat_dot     ( matrix* vecA, matrix* vecB );
double    mat_norm    ( matrix* vec, int p );
double    mat_mag     ( matrix* vec );
matrix*   mat_uvec    ( matrix* vec );
matrix*   mat_proj    ( matrix* u, matrix* v );


// MatArith functions
matrix*   mat_add     ( matrix* matA, matrix* matB );
matrix*   mat_sub     ( matrix* matA, matrix* matB );
matrix*   mat_mul     ( matrix* matA, matrix* matB );
matrix*   mat_pow     ( matrix* mat, int power );
matrix*   mat_abs     ( matrix* mat );
matrix*   mat_trans   ( matrix* mat );


// MatRoot functions
matrixz*  mat_root    ( matrix* poly, double tol, int max );
double           B    ( matrix* coef );
void             Z    ( matrixz* zero, double b );
void             L    ( matrixz* zero, matrix* coef, double tol, int max );
double complex   N    ( matrixz* zero, matrix* coef, int j );
double complex   D    ( matrixz* zero, int j );


// MatDecomp functions
void      mat_LU      ( matrix* mat, matrix** L, matrix** U );
void      mat_LDU     ( matrix* mat, matrix** L, matrix** D, matrix** U );

#endif



