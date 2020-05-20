/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matRoot.c
* Source code to find the roots of a polynomial stored as a vector.
*
*******************************************************************************/
#include "../inc/matRoot.h"




/*******************************************************************************
* Local internal function declarations.
*******************************************************************************/
float          B  ( matrix*  coef );
void           Z  ( matrixz* zero, float b );
void           L  ( matrixz* zero, matrix* coef, float tol, uint max );
float complex  N  ( matrixz* zero, matrix* coef, uint j );
float complex  D  ( matrixz* zero, uint j );




/*******************************************************************************
* matrixz* mat_root ( matrix* poly, float tol, uint max )
* Returns complex roots of a polynomial using Durand-Kerner method.
*******************************************************************************/
matrixz* mat_root ( matrix* poly, float tol, uint max ) {

  mat_err( ( poly->r != 1 ), "Error (mat_root): Polynomial must be a row vector." );

  matrix*  coef = mat_init(  poly->c,   1 );
  matrixz* zero = mat_initz( poly->c-1, 1 );

  float m = *(poly->e);
  if( m != 1.0 )  poly = mat_scale( poly, 1.0/m );

  for( uint i=0; i<poly->c; i++ ) {
    uint j = poly->c - 1 - i;
    *(coef->e+j) = *(poly->e+i);
  }

  float b = B(coef);
  Z( zero, b );
  L( zero, coef, tol, max );

  mat_clear(coef);

  return zero;
}




/*******************************************************************************
* Auxilliary function that bounds the coefficients.
*******************************************************************************/
float B ( matrix* coef ) {

  float b = 0.0;
  for( uint i=0; i<coef->r; i++ ) {
    float val = fabsf( *(coef->e+i) );
    if( val > b )  b = val;
  }

  return b + 1.0;
}




/*******************************************************************************
* Auxilliary function initializes values of the complex zeros.
*******************************************************************************/
void Z ( matrixz* zero, float b ) {

  for( uint i=0; i<zero->r; i++ ) {
    float ratio = (float)i / (float)zero->r;
    *(zero->e+i) = cosf( ratio * M_PI ) + sinf( ratio * M_PI ) * b *I;
  }

  return;
}




/*******************************************************************************
* Auxilliary function loops through the numerical routine.
*******************************************************************************/
void L ( matrixz* zero, matrix* coef, float tol, uint max ) {

  for( uint k=0; k<max; k++ ) {
    float qmax = 0.0;
    for( uint j=0; j<zero->r; j++ ) {
//      float complex n = ;
//      float complex d = ;
      float complex Q = - N( zero, coef, j ) / D( zero, j );
      float q = cabsf(Q);
      float complex Z = *(zero->e+j);
      Z += Q;
      *(zero->e+j) = crealf(Z) + cimagf(Z) *I;
      if( q > qmax )  qmax = q;
    }
    if( qmax <= tol )  return;
  }

  mat_err( (true), "Error (mat_root): Exceeded maximum iterations." );

  return;
}




/*******************************************************************************
* Auxilliary function generates the iterative numerator.
*******************************************************************************/
float complex N ( matrixz* zero, matrix* coef, uint j ) {

  float complex n = *( coef->e + coef->r-1 );

  for( uint i=0; i<zero->r; i++ ) {
    n *= *(zero->e+j);
    n += *( coef->e + zero->r-1 - i );
//     float complex c = *( coef->e + zero->r-1 - i );
//     float complex z = *( zero->e + j );
//     n = z * n + c;
  }

  return n;
}




/*******************************************************************************
* Auxilliary function generates the iterative denominator.
*******************************************************************************/
float complex D ( matrixz* zero, uint j ) {

  float complex d = 1.0;

  for( uint i=0; i<zero->r; i++ ) {
    if( i != j )  d *= *(zero->e+j) - *(zero->e+i);
//     float complex zi = *(zero->e+i);
//     float complex zj = *(zero->e+j);
//     if( i != j )  d *= zj - zi;
  }

  return d;
}



