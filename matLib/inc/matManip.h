/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matManip.h
* Header file for the 'matManip' library functions.
*
*******************************************************************************/
#ifndef MAT_MANIP_H
#define MAT_MANIP_H


// Standard includes
#include <math.h>
#include <string.h>


// Library includes
#include "matCommon.h"


// Function declarations
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
void      mat_rmtiny  ( matrix* mat, float tol );


#endif



