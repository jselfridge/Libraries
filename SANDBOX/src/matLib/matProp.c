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

  if( mat->rows == 1 )  return *(mat->data);
  if( mat->rows == 2 )  return *(mat->data) * *(mat->data+3) - *(mat->data+1) * *(mat->data+2);
  if( mat->rows == 3 )  return
      *(mat->data+a) * *(mat->data+e) * *(mat->data+i)
    + *(mat->data+b) * *(mat->data+f) * *(mat->data+g)
    + *(mat->data+c) * *(mat->data+d) * *(mat->data+h)
    - *(mat->data+c) * *(mat->data+e) * *(mat->data+g)
    - *(mat->data+b) * *(mat->data+d) * *(mat->data+i)
    - *(mat->data+a) * *(mat->data+f) * *(mat->data+h);

  matrix* L = NULL;
  matrix* D = NULL;
  matrix* U = NULL;
  mat_LU( mat, L, D, U );

  double product = 1.0;
  for( uint i=0; i < mat->rows * mat->cols; i += mat->cols+1 )  product *= *(D->data+i);

  mat_clear(L);
  mat_clear(D);
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




/*******************************************************************************
* bool mat_sym ( matrix* mat, float tol )
* Evaluates whether a matrix is symmetric within a prescribed tolerance.
*******************************************************************************/
bool mat_sym ( matrix* mat, float tol ) {

  mat_err( ( mat->rows != mat->cols ), "Error (mat_sym): A symmetric matrix must be square." );

  // Loop through lower triangle
  for( uint r=0; r<mat->rows; r++ ) {
    for( uint c=0; c<=r; c++ ) {

      // Get upper and lower elements
      float l = *( mat->data + r*mat->cols + c );
      float u = *( mat->data + c*mat->cols + r );

      // Compare the absolute difference to the tolerance
      if( fabs(l-u) >= tol )  return false;

      // Set the average of the two values
      float val = (l+u) / 2.0;
      *( mat->data + r*mat->cols + c ) = val;
      *( mat->data + c*mat->cols + r ) = val;

    }
  }

  return true;
}



