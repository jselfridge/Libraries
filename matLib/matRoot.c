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
#include <matLib.h>




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

  //uint i, j, c, z;
  //float m, b;
  //c = poly->cols;
  //z = c-1;

  matrix*  coef = mat_init( poly->cols, 1 );
  matrixz* zero = mat_initz( poly->cols-1, 1 );

  float m = *(poly->data);
  if( m != 1.0 )  poly = mat_scale( poly, 1.0/m );

  for( ushort i=1; i<=c; i++ ) {
    j = c + 1 - i;
    mat_set( coef, j, 1, mat_get( poly, 1, i ) );
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

  //ushort i, c;
  //c = coef->rows;

  float val, b = 0.0;
  for( ushort i=1; i<=coef->rows; i++ ) {
    val = (float)fabs( mat_get( coef, i, 1 ) );
    if( val > b )  b = val;
  }

  return b+1;
}




/*******************************************************************************
* Auxilliary function initializes values of the complex zeros.
*******************************************************************************/
void Z ( matrixz* zero, float b ) {

  //ushort i, z;
  //float re, im, ratio;
  //z = zero->rows;

  for( ushort i=1; i<=zero->rows; i++ ) {
    float ratio = (float)i / (float)zero->rows;
    float re = cos( ratio * PI2 );
    float im = sin( ratio * PI2 ) * b;
    mat_setz( zero, i, 1, re, im );
  }

  return;
}




/*******************************************************************************
* Auxilliary function loops through the numerical routine.
*******************************************************************************/
void L ( matrixz* zero, matrix* coef, float tol, uint max ) {

  //ushort j, k, z;
  //float q, qmax;
  //float complex n, d, Q, Z;
  //z = zero->rows;

  for( ushort k=0; k<max; k++ ) {
    float qmax = 0.0;
    for( ushort j=1; j<=zero->rows; j++ ) {
      float complex n = N( zero, coef, j );
      float complex d = D( zero, j );
      float complex Q = -n/d;
      float q = cabs(Q);
      float complex Z = mat_getre( zero, j, 1 ) + mat_getim( zero, j, 1 ) *I;
      Z += Q;
      mat_setz( zero, j, 1, creal(Z), cimag(Z) );
      if( q > qmax )  qmax = q;
    }
    if( qmax <= tol )  break;
  }

  mat_err( ( k >= max ), "Error (mat_root): Exceeded maximum iterations." );

  return;
}




/*******************************************************************************
* Auxilliary function generates the iterative numerator.
*******************************************************************************/
float complex N ( matrixz* zero, matrix* coef, uint j ) {

  //ushort i, c, z;
  //float re, im;
  //float complex C, Z, n;
  //c = coef->rows;
  //z = zero->rows;

  float complex n = mat_get( coef, coef->rows, 1 );

  for( ushort i=zero->rows; i>=1; i-- ) {
    float complex C = mat_get( coef, i, 1 );
    float re = mat_getre( zero, j, 1 );
    float im = mat_getim( zero, j, 1 );
    float complex Z = re + im *I;
    n = Z * n + C;
  }

  return n;
}




/*******************************************************************************
* Auxilliary function generates the iterative denominator.
*******************************************************************************/
float complex D ( matrixz* zero, uint j ) {

  //ushort i, z;
  //float complex zi, zj, d;
  //z = zero->rows;

  float complex d = 1.0;

  for( ushort i=1; i<=zero->rows; i++ ) {
    float complex zi = mat_getre( zero, i, 1 ) + mat_getim( zero, i, 1) *I;
    float complex zj = mat_getre( zero, j, 1 ) + mat_getim( zero, j, 1) *I;
    if( i != j )  d *= zj - zi;
  }

  return d;
}



