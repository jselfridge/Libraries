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
* float mat_det ( matrix* M )
* Returns the determinant of a matrix.
*******************************************************************************/
float mat_det ( matrix* M ) {

  mat_err( ( M->r != M->c ), "Error (mat_det): Matrix must be square." );

  if( M->r == 1 )  return *(M->e);
  if( M->r == 2 )  return *(M->e) * *(M->e+3) - *(M->e+1) * *(M->e+2);
  if( M->r == 3 )  return
      *(M->e  ) * *(M->e+4) * *(M->e+8)
    + *(M->e+1) * *(M->e+5) * *(M->e+6)
    + *(M->e+2) * *(m->e+3) * *(M->e+7)
    - *(M->e+2) * *(M->e+4) * *(M->e+6)
    - *(M->e+1) * *(M->e+3) * *(M->e+8)
    - *(M->e  ) * *(M->e+5) * *(M->e+7);

  matrix* L = NULL;
  matrix* D = NULL;
  matrix* U = NULL;
  mat_LDU( M, &L, &D, &U );

  float product = 1.0;
  for( uint i=0; i < M->r * M->c; i += M->c+1 )  product *= *(D->e+i);

  mat_clear(L);
  mat_clear(D);
  mat_clear(U);

  return product;
}




/*******************************************************************************
* float mat_trace ( matrix* M )
* Returns the trace of a square matrix (sum of main diagonal).
*******************************************************************************/
float mat_trace ( matrix* M ) {

  mat_err( ( M->r != M->c ), "Error (mat_trace): Matrix must be square." );

  float sum = 0.0;
  for( uint i=0; i < M->r * M->c; i += M->c+1 )  sum += *(M->e+i);

  return sum;
}




/*******************************************************************************
* bool mat_sym ( matrix** M, float tol )
* Evaluates whether a matrix is symmetric within a prescribed tolerance.
*******************************************************************************/
bool mat_sym ( matrix** M, float tol ) {

  mat_err( ( (*M)->r != (*M)->c ), "Error (mat_sym): A symmetric matrix must be square." );

  for( uint r=0; r<(*M)->r; r++ ) {
    for( uint c=0; c<=r; c++ ) {
      float l = *( (*M)->e + r*(*M)->c + c );
      float u = *( (*M)->e + c*(*M)->c + r );
      if( fabs(l-u) >= tol )  return false;
      else {
        float val = (l+u) / 2.0;
        *( (*M)->e + r * (*M)->c + c ) = val;
        *( (*M)->e + c * (*M)->c + r ) = val;
      }
    }
  }

  return true;
}



