

#include "matLib.h"


/**
 *  mat_det
 *  Returns the determinant of a matrix.
 */
double mat_det ( matrix *mat )  {

  mat_err( mat->rows != mat->cols, "Error (mat_det): Matrix must be square." );

  uint i, n;
  double product = 1.0;
  matrix *L = NULL;
  matrix *U = NULL;

  mat_LU( mat, &L, &U );
  n = mat->rows;

  for ( i=1; i<=n; i++ )  product *= mat_get( U, i, i );

  mat_clear(L);
  mat_clear(U);

  return product;
}


/**
 *  mat_trace
 *  Returns the trace of a square matrix (sum of main diagonal).
 */
double mat_trace ( matrix *mat )  {

  mat_err( mat->rows != mat->cols, "Error (mat_trace): Matrix must be square." );

  uint i, n;
  double sum;

  n = mat->rows;
  sum = 0.0;
  for ( i=1; i<=n; i++ )  sum += mat_get( mat, i, i );

  return sum;
}


/**
 *  mat_sym
 *  Evaluates whether a matrix is symmetric within a prescribed tolerance.
 */
bool mat_sym ( matrix *mat, double tol )  {

  mat_err( mat->rows != mat->cols, "Error (mat_sym): A symmetric matrix must be square." );

  uint r, c;
  double u, l;
  double diff, val;
  bool sym = true;

  // Loop through lower triangle
  for ( r=1; r <= mat->rows; r++ )  {
    for ( c=1; c<r; c++ )  {

      // Get upper and lower elements 
      l = mat_get( mat, r, c );
      u = mat_get( mat, c, r );

      // Compare the absolute difference to the tolerance
      diff = fabs( l - u );
      if ( diff >= tol )  sym = false;

      // Average the two values 
      val = ( l + u ) / 2.0;
      mat_set( mat, r, c, val );
      mat_set( mat, c, r, val );

    }
  }

  return sym;
}



