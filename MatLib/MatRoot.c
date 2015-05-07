
//============================================================
//  matRoot.c
//  Justin M Selfridge
//============================================================
#include "matLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_root
//  Returns complex roots of a polynomial using Durand-Kerner method.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrixz* mat_root ( matrix* poly, double tol, int max )  {

  mat_err( poly->rows !=1, "Error (mat_root): Polynomial must be a row vector." );

  int i, j, c, z;
  double m, b;

  c = poly->cols;
  z = c-1;

  matrix*  coef = mat_init (c,1);
  matrixz* zero = mat_initz(z,1);

  m = mat_get(poly,1,1);
  if ( m!=1.0 )  poly = mat_scale(poly,1/m);

  for ( i=1; i<=c; i++ ) {
    j = c+1-i;
    mat_set( coef,j,1, mat_get(poly,1,i) );
  }

  b = B(coef);
  Z(zero,b);
  L( zero, coef, tol, max );

  mat_clear(coef);
  return zero;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function that bounds the coefficients.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double B ( matrix* coef )  {

  int i, c;
  double val, b = 0.0;

  c = coef->rows;

  for( i=1; i<=c; i++ ) {
    val = fabs( mat_get(coef,i,1) );
    if( val > b )  b = val;
  }

  return b+1;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function initializes values of the complex zeros.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Z ( matrixz* zero, double b )  {

  int i, z;
  double re, im, ratio;

  z = zero->rows;

  for( i=1; i<=z; i++ ) {
    ratio = (double)i / (double)z;
    re = cos( ratio * PI2 );
    im = sin( ratio * PI2 ) * b;
    mat_setz( zero, i, 1, re, im );
  }

  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function loops through the numerical routine.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void L ( matrixz* zero, matrix* coef, double tol, int max )  {

  int j, k, z;
  double  q, qmax;
  double complex n, d, Q, Z;

  z = zero->rows;

  for ( k=0; k<max; k++ ) {
    qmax = 0.0;
    for( j=1; j<=z; j++ ) {
      n = N( zero, coef, j );
      d = D( zero, j );
      Q = -n/d;
      q = cabs(Q);
      Z = mat_getre(zero,j,1) + mat_getim(zero,j,1) *I;
      Z += Q;
      mat_setz( zero, j, 1, creal(Z), cimag(Z) );
      if ( q> qmax )  qmax = q;
    }
    if( qmax <= tol )  break;
  }

  mat_err( k>=max, "Error (mat_root): Exceeded maximum iterations." );

  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function generates the iterative numerator.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double complex N ( matrixz* zero, matrix* coef, int j )  {

  int i, c, z;
  double re, im;
  double complex C, Z, n;

  c = coef->rows;
  z = zero->rows;
  n = mat_get(coef,c,1);

  for( i=z; i>=1; i-- ) {
    C = mat_get(coef,i,1);
    re = mat_getre(zero,j,1);
    im = mat_getim(zero,j,1);
    Z = re + im*I;
    n = Z * n + C;
  }

  return n;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function generates the iterative denominator.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double complex D ( matrixz* zero, int j )  {

  int i, z;
  double complex zi, zj, d;

  z = zero->rows;
  d = 1.0;

  for( i=1; i<=z; i++ ) {
    zi = mat_getre(zero,i,1) + mat_getim(zero,i,1) *I;
    zj = mat_getre(zero,j,1) + mat_getim(zero,j,1) *I;
    if( i!=j )  d *= zj - zi;
  }

  return d;
}



