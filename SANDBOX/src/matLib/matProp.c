/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matProp.c
* Source code to determine matrix properties used within the 'matLib' library.
*
*******************************************************************************/
#include "../inc/matProp.h"




/*******************************************************************************
* float mat_det ( matrix* mat )
* Returns the determinant of a matrix.
*******************************************************************************/
float mat_det ( matrix* mat ) {

  mat_err( ( mat->rows != mat->cols ), "Error (mat_det): Matrix must be square." );

  matrix* L = NULL;
  matrix* U = NULL;
  mat_LU( mat, L, U );

  double product = 1.0;
  for( uint i=0; i < mat->rows * mat->cols; i += mat->cols+1 )  product *= *(U->data+i);

  mat_clear(L);
  mat_clear(U);

  return product;
}




/*******************************************************************************
* float mat_trace ( matrix* mat )
* Returns the trace of a square matrix (sum of main diagonal).
*******************************************************************************/
float mat_trace ( matrix* mat ) {

  mat_err( ( mat->rows != mat->cols ), "Error (mat_trace): Matrix must be square." );

  float sum = 0.0;
  for( uint i=0; i < mat->rows * mat->cols; i += mat->cols+1 )  sum += *(mat->data+i);

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



