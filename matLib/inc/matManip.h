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
matrix*   mat_init    ( uint r, uint c );
void      mat_clear   ( matrix* M );
void      mat_print   ( matrix* M );
matrix*   mat_read    ( char* file );
void      mat_write   ( matrix* M, char* file );
float     mat_get     ( matrix* M, uint r, uint c );
matrix*   mat_getr    ( matrix* M, uint r );
matrix*   mat_getc    ( matrix* M, uint c );
void      mat_set     ( matrix* M, uint r, uint c, float val );
void      mat_setr    ( matrix* M, uint r, matrix* V );
void      mat_setc    ( matrix* M, uint c, matrix* V );
matrix*   mat_copy    ( matrix* M );
matrix*   mat_eye     ( uint n );
matrix*   mat_ones    ( uint r, uint c );
matrix*   mat_scale   ( matrix* M, float scale );
void      mat_swapr   ( matrix* M, uint p, uint q );
void      mat_swapc   ( matrix* M, uint p, uint q );
matrix*   mat_appr    ( matrix* T, matrix* B );
matrix*   mat_appc    ( matrix* L, matrix* R );
void      mat_rmtiny  ( matrix* M, float tol );


#endif



