
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  RotLib.h
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _ROTLIB_H
#define _ROTLIB_H


//  Standard includes
//#include <math.h>
#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>


void rot_test();

/*
//  Matrix structure declaration
typedef struct _matrix {
  int rows;
  int cols;
  double* data;
} matrix;
*/
/*
//  MatIO functions
void     mat_err    ( int cond, char* msg );
matrix*  mat_init   ( int rows, int cols );
matrix*  mat_read   ( char* file );
void     mat_print  ( matrix* mat );
void     mat_write  ( matrix* mat, char* file );
void     mat_clear  ( matrix* mat );
*/
/*
//  MatManip functions
void     mat_set    ( matrix* mat, int row, int col, double val );
double   mat_get    ( matrix* mat, int row, int col );
matrix*  mat_copy   ( matrix* mat );
matrix*  mat_eye    ( int n );
matrix*  mat_ones   ( int rows, int cols );
matrix*  mat_scale  ( matrix* mat, double scale );
void     mat_swapr   ( matrix* mat, int p, int q );
void     mat_swapc   ( matrix* mat, int n, int m );
*/
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
/*
//  MatProp functions
double   mat_trace   ( matrix* mat );
double   mat_norm    ( matrix* vec, int p );
//double   mat_mean    ( matrix* mat );
//matrix*  mat_meanr   ( matrix* mat );
//matrix*  mat_meanc   ( matrix* mat );
//matrix*  mat_eigval  ( matrix* mat );
//matrix*  mat_eigvec  ( matrix* mat );
//matrix*  mat_cov     ( matrix* mat );
*/
/*
//  MatDecomp functions
void     mat_LU    ( matrix* mat, matrix** L, matrix** U );
double   mat_det   ( matrix* mat );
matrix*  mat_inv   ( matrix* mat );
matrix*  mat_divL  ( matrix* A, matrix* B );
matrix*  mat_divR  ( matrix* B, matrix* A );
*/

#endif



