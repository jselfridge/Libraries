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
  uint    rows;
  uint    cols;
  float*  data;
} matrix;


// Matrix (complex) structure
typedef struct matrixz {
  uint            rows;
  uint            cols;
  float complex*  data;
} matrixz;


// Error message macro
#define  mat_err( cond, msg )  ({               \
           if(cond) {                           \
             fprintf( stderr, "%s\n\n", msg );  \
             exit(1);                           \
           }                                    \
         })


// Functions within matManip
matrix*   mat_init    ( uint rows, uint cols );
void      mat_clear   ( matrix* mat );
void      mat_print   ( matrix* mat );
matrix*   mat_read    ( char* file );
void      mat_write   ( matrix* mat, char* file );
float     mat_get     ( matrix* mat, uint row, uint col );
matrix*   mat_getr    ( matrix* mat, uint row );
matrix*   mat_getc    ( matrix* mat, uint col );
void      mat_set     ( matrix* mat, uint row, uint col, float val );
void      mat_setr    ( matrix* mat, uint row, matrix* vec );
void      mat_setc    ( matrix* mat, uint col, matrix* vec );
matrix*   mat_copy    ( matrix* mat );
matrix*   mat_eye     ( uint n );
matrix*   mat_ones    ( uint rows, uint cols );
matrix*   mat_scale   ( matrix* mat, float scale );
void      mat_swapr   ( matrix* mat, uint p, uint q );
void      mat_swapc   ( matrix* mat, uint p, uint q );
matrix*   mat_appr    ( matrix* matT, matrix* matB );
matrix*   mat_appc    ( matrix* matL, matrix* matR );
void      mat_rmtiny  ( matrix** mat, float tol );


// Functions within matComplex
matrixz*  mat_initz   ( uint rows, uint cols );
void      mat_clearz  ( matrixz* mat );
void      mat_printz  ( matrixz* mat );
matrixz*  mat_readz   ( char* file );
void      mat_writez  ( matrixz* mat, char* file );
float     mat_getre   ( matrixz* mat, uint row, uint col );
float     mat_getim   ( matrixz* mat, uint row, uint col );
matrixz*  mat_getrz   ( matrixz* mat, uint row );
matrixz*  mat_getcz   ( matrixz* mat, uint col );
void      mat_setz    ( matrixz* mat, uint row, uint col, float re, float im );
void      mat_setrz   ( matrixz* mat, uint row, matrixz* vec );
void      mat_setcz   ( matrixz* mat, uint col, matrixz* vec );


// Functions within matVec
matrix*  mat_skew   ( matrix* vec );
matrix*  mat_sskew  ( matrix* vec );
matrix*  mat_cross  ( matrix* vecA, matrix* vecB );
float    mat_dot    ( matrix* vecA, matrix* vecB );
float    mat_mag    ( matrix* vec );
float    mat_norm   ( matrix* vec, uint p );
matrix*  mat_uvec   ( matrix* vec );
matrix*  mat_proj   ( matrix* u, matrix *v );


// Functions within matArith
matrix*  mat_add    ( matrix* matA, matrix* matB );
matrix*  mat_sub    ( matrix* matA, matrix* matB );
matrix*  mat_emul   ( matrix* matA, matrix* matB );
matrix*  mat_ediv   ( matrix* matA, matrix* matB );
matrix*  mat_mul    ( matrix* matA, matrix* matB );
//matrix*  mat_inv    ( matrix* mat );
//matrix*  mat_divL   ( matrix* matA, matrix* matB );
//matrix*  mat_divR   ( matrix* matA, matrix* matB );
matrix*  mat_epow   ( matrix* mat, uint power );
matrix*  mat_pow    ( matrix* mat, uint power );
matrix*  mat_abs    ( matrix* mat );
matrix*  mat_trans  ( matrix* mat );


// // Functions within matRoot
// matrixz*  mat_root  ( matrix* poly, float tol, ushort max );


// // Functions within matProp
// float  mat_det    ( matrix* mat );
// float  mat_trace  ( matrix* mat );
// bool   mat_sym    ( matrix* mat, float tol );


// // Functions within matDecomp
// void     mat_LU      ( matrix* mat, matrix** L, matrix** U );
// void     mat_LDU     ( matrix* mat, matrix** L, matrix** D, matrix** U );
// void     mat_QR      ( matrix* mat, matrix** Q, matrix** R );     //---  TODO: QR factorization on short matrices  ---//
// //void     mat_chol    ( float a[], ushort n, ushort nn, float u[], ushort* nullty, ushort* ifault );
// //void     mat_syminv  ( float a[], ushort n, float c[], float w[], ushort* nullty, ushort* ifault );
// matrix*  mat_tri2vec ( matrix* tri );
// matrix*  mat_vec2tri ( matrix* vec );


#endif



