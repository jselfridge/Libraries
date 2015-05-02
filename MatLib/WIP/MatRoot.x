/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatRoot.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_root
//  Returns complex roots of a polynomial using Durand-Kerner method.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrixz* mat_root ( matrix* poly, double tol, int max ) {

  mat_err( poly->rows!=1, "Error(mat_root): Polynomial must be input as a row vector." );

  int c = poly->cols;
  int z = c-1;

  matrixz* zero = mat_initz(z,1);
  matrix*  coef = mat_init (c,1);

  for ( int i=1; i<=c; i++ ) {
    int j = c+1-i;
    mat_set( coef,j,1, mat_get(poly,1,i) );
  }

  double b = B(coef);
  Z(zero,b);
  L( zero, coef, tol, max );

  mat_clear(coef);
  return zero;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function that bounds the coefficients.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double B ( matrix* coef ) {

  int c = coef->rows;
  double val, b = 0;

  for( int i=1; i<=c; i++ ) {
    val = fabs( mat_get(coef,i,1) );
    if( val > b )  b = val;
  }

  return b+1;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function initializes values of the complex zeros.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Z ( matrixz* zero, double b ) {

  int z = zero->rows;
  double re, im, ratio;

  for( int i=1; i<=z; i++ ) {
    ratio = (double)i / (double)z;
    re = cos( ratio * PI2 );
    im = sin( ratio * PI2 ) * b;
    mat_setz( zero, i, 1, re, im );
  }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function loops through the numerical routine.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void L ( matrixz* zero, matrix* coef, double tol, int max ) {

  int k, z = zero->rows;
  double complex n, d, Q, Z;
  double  q, qmax;

  for ( k=0; k<max; k++ ) {
    qmax = 0.0;
    for( int j=1; j<=z; j++ ) {
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
  mat_err( k>=max, "Error (mat_root): Exceeded maximum iterations."  );
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function generates the iterative numerator.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double complex N ( matrixz* zero, matrix* coef, int j ) {

  int c = coef->rows;
  int z = zero->rows;
  double complex C, Z, n = mat_get(coef,c,1);
  double re, im;

  for( int i=z; i>=1; i-- ) {
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
double complex D ( matrixz* zero, int j ) {

  int z = zero->rows;
  double complex zi, zj, d = 1.0;

  for( int i=1; i<=z; i++ ) {
    zi = mat_getre(zero,i,1) + mat_getim(zero,i,1) *I;
    zj = mat_getre(zero,j,1) + mat_getim(zero,j,1) *I;
    if( i!=j )  d *= zj - zi;
  }

  return d;
}



*/
