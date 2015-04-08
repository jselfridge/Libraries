
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatLib.h
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _MATLIB_H
#define _MATLIB_H


//  Standard includes
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//  Matrix structure declaration
typedef struct _matrix {
  int rows;
  int cols;
  double* data;
  char* name;
} matrix;

/*
//  Complex structure declaration
typedef struct _matrixz {
  int rows;
  int cols;
  double complex *data;
} matrixz;
*/

//  MatIO functions
void     mat_err     ( bool cond, char* msg );
matrix*  mat_init    ( int rows, int cols );//
matrix*  mat_read    ( char* file );//
void     mat_print   ( matrix* mat );//
void     mat_write   ( matrix* mat, char* file );//
void     mat_clear   ( matrix* mat );//


//  MatIOZ functions


//  MatManip functions
double   mat_get     ( matrix* mat, int row, int col );
matrix*  mat_getr    ( matrix* mat, int row );
matrix*  mat_getc    ( matrix* mat, int col );
void     mat_set     ( matrix* mat, int row, int col, double val );
void     mat_setr    ( matrix* mat, int row, matrix* vec );
void     mat_setc    ( matrix* mat, int col, matrix* vec );
matrix*  mat_copy    ( matrix* mat );
matrix*  mat_eye     ( int n );
matrix*  mat_ones    ( int rows, int cols );
matrix*  mat_scale   ( matrix* mat, double scale );
void     mat_swapr   ( matrix* mat, int p, int q );
void     mat_swapc   ( matrix* mat, int n, int m );
matrix*  mat_appr    ( matrix* matT, matrix* matB );
matrix*  mat_appc    ( matrix* matL, matrix* matR );
matrix*  mat_rmtiny  ( matrix* mat, double tol );


//  MatVec functions
matrix*  mat_skew    ( matrix* vec );
matrix*  mat_sskew   ( matrix* vec );
matrix*  mat_cross   ( matrix* vecA, matrix* vecB );
double   mat_dot     ( matrix* vecA, matrix* vecB );
double   mat_norm    ( matrix* vec, int p );
double   mat_mag     ( matrix* vec );
matrix*  mat_uvec    ( matrix* vec );
matrix*  mat_proj    ( matrix* u, matrix* v );


//  MatArith functions
matrix*  mat_add     ( matrix* matA, matrix* matB );
matrix*  mat_sub     ( matrix* matA, matrix* matB );
matrix*  mat_mul     ( matrix* matA, matrix* matB );
matrix*  mat_pow     ( matrix* mat, int power );
matrix*  mat_abs     ( matrix* mat );
matrix*  mat_trans   ( matrix* mat );


//  MatProp functions
double   mat_trace   ( matrix* mat );
int      mat_rank    ( matrix* mat );  // WIP
void     mat_eigval  ( matrix* mat, double tol, int max );  // WIP
//double   mat_mean    ( matrix* mat );
//matrix*  mat_meanr   ( matrix* mat );
//matrix*  mat_meanc   ( matrix* mat );
//matrix*  mat_eigvec  ( matrix* mat );
//matrix*  mat_cov     ( matrix* mat );


//  MatDecomp functions
void     mat_LU    ( matrix* mat, matrix** L, matrix** U );
void     mat_QR    ( matrix* mat, matrix** Q, matrix** R ); 
double   mat_det   ( matrix* mat );
matrix*  mat_inv   ( matrix* mat );
matrix*  mat_divL  ( matrix* A, matrix* B );
matrix*  mat_divR  ( matrix* B, matrix* A );


//  MatRoot function
void     mat_root  ( matrix* poly );
// scan();  // Not needed...
// radius();
// init();
// dk();
// f();
// q();

#endif



