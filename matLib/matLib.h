/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matLib.h
* Header file for the 'matLib' library functions.
*
*******************************************************************************/
#ifndef MATLIB_H
#define MATLIB_H


// Standard includes
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Matrix (real) structure
typedef struct matrix {
  ushort  rows;
  ushort  cols;
  float*  data;
} matrix;


// Matrix (complex) structure
typedef struct matrixz {
  ushort          rows;
  ushort          cols;
  float complex*  data;
} matrixz;


// MatManip Functions
void      mat_err     ( bool cond, char* msg );
matrix*   mat_init    ( ushort rows, ushort cols );
void      mat_clear   ( matrix* mat );
void      mat_print   ( matrix* mat );
matrix*   mat_read    ( char* file );
void      mat_write   ( matrix* mat, char* file );
float     mat_get     ( matrix* mat, ushort row, ushort col );
matrix*   mat_getr    ( matrix* mat, ushort row );
matrix*   mat_getc    ( matrix* mat, ushort col );
void      mat_set     ( matrix* mat, ushort row, ushort col, float val );
void      mat_setr    ( matrix* mat, ushort row, matrix* vec );
void      mat_setc    ( matrix* mat, ushort col, matrix* vec );
matrix*   mat_copy    ( matrix* mat );
matrix*   mat_eye     ( ushort n );
matrix*   mat_ones    ( ushort rows, ushort cols );
matrix*   mat_scale   ( matrix* mat, float scale );
void      mat_swapr   ( matrix* mat, ushort p, ushort q );
void      mat_swapc   ( matrix* mat, ushort p, ushort q );
matrix*   mat_appr    ( matrix* matT, matrix* matB );
matrix*   mat_appc    ( matrix* matL, matrix* matR );
void      mat_rmtiny  ( matrix** mat, float tol );


// // MatComplex functions
// matrixz*  mat_initz   ( ushort rows, ushort cols );
// void      mat_clearz  ( matrixz* mat );
// void      mat_printz  ( matrixz* mat );
// matrixz*  mat_readz   ( char* file );
// void      mat_writez  ( matrixz* mat, char* file );
// float     mat_getre   ( matrixz* mat, ushort row, ushort col );
// float     mat_getim   ( matrixz* mat, ushort row, ushort col );
// matrixz*  mat_getrz   ( matrixz* mat, ushort row );
// matrixz*  mat_getcz   ( matrixz* mat, ushort col );
// void      mat_setz    ( matrixz* mat, ushort row, ushort col, float re, float im );
// void      mat_setrz   ( matrixz* mat, ushort row, matrixz* vec );
// void      mat_setcz   ( matrixz* mat, ushort col, matrixz* vec );


// // MatVec functions
// matrix*  mat_skew   ( matrix* vec );
// matrix*  mat_sskew  ( matrix* vec );
// matrix*  mat_cross  ( matrix* vecA, matrix* vecB );
// float    mat_dot    ( matrix* vecA, matrix* vecB );
// float    mat_norm   ( matrix* vec, ushort p );
// float    mat_mag    ( matrix* vec );
// matrix*  mat_uvec   ( matrix* vec );
// matrix*  mat_proj   ( matrix* u, matrix *v );


// // MatArith functions
// matrix*  mat_add    ( matrix* matA, matrix* matB );
// matrix*  mat_sub    ( matrix* matA, matrix* matB );
// matrix*  mat_emul   ( matrix* matA, matrix* matB );
// matrix*  mat_ediv   ( matrix* matA, matrix* matB );
// matrix*  mat_mul    ( matrix* matA, matrix* matB );
// //matrix*  mat_inv    ( matrix* mat );
// //matrix*  mat_divL   ( matrix* matA, matrix* matB );
// //matrix*  mat_divR   ( matrix* matA, matrix* matB );
// matrix*  mat_pow    ( matrix* mat, ushort power );
// matrix*  mat_abs    ( matrix* mat );
// matrix*  mat_trans  ( matrix* mat );


// // MatRoot function
// matrixz*  mat_root  ( matrix* poly, float tol, ushort max );


// // MatProp functions
// float  mat_det    ( matrix* mat );
// float  mat_trace  ( matrix* mat );
// bool   mat_sym    ( matrix* mat, float tol );


// // MatDecomp functions
// void     mat_LU      ( matrix* mat, matrix** L, matrix** U );
// void     mat_LDU     ( matrix* mat, matrix** L, matrix** D, matrix** U );
// void     mat_QR      ( matrix* mat, matrix** Q, matrix** R );     //---  TODO: QR factorization on short matrices  ---//
// //void     mat_chol    ( float a[], ushort n, ushort nn, float u[], ushort* nullty, ushort* ifault );
// //void     mat_syminv  ( float a[], ushort n, float c[], float w[], ushort* nullty, ushort* ifault );
// matrix*  mat_tri2vec ( matrix* tri );
// matrix*  mat_vec2tri ( matrix* vec );


#endif



