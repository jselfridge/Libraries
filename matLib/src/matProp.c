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
* float mat_det ( matrix* A )
* Returns the determinant of a matrix.
*******************************************************************************/
float mat_det ( matrix* A ) {

  mat_err( ( A->r != A->c ), "Error (mat_det): Matrix must be square." );

  if( A->r == 1 )  return *(A->e);
  if( A->r == 2 )  return *(A->e) * *(A->e+3) - *(A->e+1) * *(A->e+2);
  if( A->r == 3 )  return
      *(A->e  ) * *(A->e+4) * *(A->e+8)
    + *(A->e+1) * *(A->e+5) * *(A->e+6)
    + *(A->e+2) * *(A->e+3) * *(A->e+7)
    - *(A->e+2) * *(A->e+4) * *(A->e+6)
    - *(A->e+1) * *(A->e+3) * *(A->e+8)
    - *(A->e  ) * *(A->e+5) * *(A->e+7);

  matrix* L = NULL;
  matrix* D = NULL;
  matrix* U = NULL;
  mat_LDU( A, &L, &D, &U );

  float product = 1.0;
  for( uint i=0; i < A->r * A->c; i += A->c+1 )  product *= *(D->e+i);

  mat_clear(L);
  mat_clear(D);
  mat_clear(U);

  return product;
}




/*******************************************************************************
* float mat_trace ( matrix* A )
* Returns the trace of a square matrix (sum of main diagonal).
*******************************************************************************/
float mat_trace ( matrix* A ) {

  mat_err( ( A->r != A->c ), "Error (mat_trace): Matrix must be square." );

  float sum = 0.0;
  for( uint i=0; i < A->r * A->c; i += A->c+1 )  sum += *(A->e+i);

  return sum;
}




/*******************************************************************************
* bool mat_sym ( matrix** A, float tol )
* Evaluates whether a matrix is symmetric within a prescribed tolerance.
*******************************************************************************/
bool mat_sym ( matrix** A, float tol ) {

  mat_err( ( (*A)->r != (*A)->c ), "Error (mat_sym): A symmetric matrix must be square." );

  for( uint r=0; r<(*A)->r; r++ ) {
    for( uint c=0; c<=r; c++ ) {
      float l = *( (*A)->e + r*(*A)->c + c );
      float u = *( (*A)->e + c*(*A)->c + r );
      if( fabsf(l-u) > tol )  return false;
      else {
        float val = (l+u) / 2.0;
        *( (*A)->e + r * (*A)->c + c ) = val;
        *( (*A)->e + c * (*A)->c + r ) = val;
      }
    }
  }

  return true;
}



