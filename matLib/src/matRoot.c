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

  mat_err( ( poly->rows != 1 ), "Error (mat_root): Polynomial must be a row vector." );

  matrix*  coef = mat_init(  poly->cols,   1 );
  matrixz* zero = mat_initz( poly->cols-1, 1 );

  float m = *(poly->data);
  if( m != 1.0 )  poly = mat_scale( poly, 1.0/m );

  for( uint i=0; i<poly->cols; i++ ) {
    uint j = poly->cols - 1 - i;
    *(coef->data+j) = *(poly->data+i);
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
  for( uint i=0; i<coef->rows; i++ ) {
    float val = (float)fabs( *(coef->data+i) );
    if( val > b )  b = val;
  }

  return b + 1.0;
}




/*******************************************************************************
* Auxilliary function initializes values of the complex zeros.
*******************************************************************************/
void Z ( matrixz* zero, float b ) {

  for( uint i=0; i<zero->rows; i++ ) {
    float ratio = (float)i / (float)zero->rows;
    *(zero->data+i) = (float)cos( ratio * M_PI ) + (float)sin( ratio * M_PI ) * b *I;
  }

  return;
}




/*******************************************************************************
* Auxilliary function loops through the numerical routine.
*******************************************************************************/
void L ( matrixz* zero, matrix* coef, float tol, uint max ) {

  for( uint k=0; k<max; k++ ) {
    float qmax = 0.0;
    for( uint j=0; j<zero->rows; j++ ) {
      float complex n = N( zero, coef, j );
      float complex d = D( zero, j );
      float complex Q = -n/d;
      float q = cabsf(Q);
      float complex Z = *(zero->data+j);
      Z += Q;
      *(zero->data+j) = crealf(Z) + cimagf(Z) *I;
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

  float complex n = *( coef->data + coef->rows-1 );

  for( uint i=0; i<zero->rows; i++ ) {
    float complex c = *( coef->data + zero->rows-1 - i );
    float complex z = *( zero->data + j );
    n = z * n + c;
  }

  return n;
}




/*******************************************************************************
* Auxilliary function generates the iterative denominator.
*******************************************************************************/
float complex D ( matrixz* zero, uint j ) {

  float complex d = 1.0;

  for( uint i=0; i<zero->rows; i++ ) {
    float complex zi = *(zero->data+i);
    float complex zj = *(zero->data+j);
    if( i != j )  d *= zj - zi;
  }

  return d;
}



