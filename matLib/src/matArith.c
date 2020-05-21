/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matArith.c
* Source code for matrix arithmetic functions within the 'matLib' library.
*
*******************************************************************************/
#include "../inc/matArith.h"




/*******************************************************************************
* matrix* mat_add ( matrix* A, matrix* B )
* Adds two matrices with indentical dimensions.
*******************************************************************************/
matrix* mat_add ( matrix* A, matrix* B ) {

  mat_err( ( A->r != B->r ), "Error (mat_add): Matrices must have same number of rows."    );
  mat_err( ( A->c != B->c ), "Error (mat_add): Matrices must have same number of columns." );

  matrix* add = mat_init( A->r, A->c );
  for( uint i=0; i < A->r * A->c; i++ )  *(add->e+i) = *(A->e+i) + *(B->e+i);

  return add;
}




/*******************************************************************************
* matrix* mat_sub ( matrix* A, matrix* B )
* Subtracts two matrices with indentical dimensions.
*******************************************************************************/
matrix* mat_sub ( matrix* A, matrix* B ) {

  mat_err( ( A->r != B->r ), "Error (mat_sub): Matrices must have same number of rows."    );
  mat_err( ( A->c != B->c ), "Error (mat_sub): Matrices must have same number of columns." );

  matrix* sub = mat_init( A->r, A->c );
  for( uint i=0; i < A->r * A->c; i++ )  *(sub->e+i) = *(A->e+i) - *(B->e+i);

  return sub;
}




/*******************************************************************************
* matrix* mat_emul ( matrix* A, matrix* B )
* Element-wise multiplication of two matrices with identical dimensions.
*******************************************************************************/
matrix* mat_emul ( matrix* A, matrix* B ) {

  mat_err( ( A->r != B->r ), "Error (mat_emul): Matrices must have same number of rows."    );
  mat_err( ( A->c != B->c ), "Error (mat_emul): Matrices must have same number of columns." );

  matrix* emul = mat_init( A->r, A->c );
  for( uint i=0; i < A->r * A->c; i++ )  *(emul->e+i) = *(A->e+i) * *(B->e+i);

  return emul;
}




/*******************************************************************************
* matrix* mat_ediv ( matrix* A, matrix* B )
* Element-wise division of two matrices with identical dimensions.
*******************************************************************************/
matrix* mat_ediv ( matrix* A, matrix* B ) {

  mat_err( ( A->r != B->r ), "Error (mat_ediv): Matrices must have same number of rows."    );
  mat_err( ( A->c != B->c ), "Error (mat_ediv): Matrices must have same number of columns." );

  matrix* ediv = mat_init( A->r, A->c );
  for( uint i=0; i < A->r * A->c; i++ )  *(ediv->e+i) = *(A->e+i) / *(B->e+i);

  return ediv;
}




/*******************************************************************************
* matrix* mat_mul ( matrix* A, matrix* B )
* Multiplication of two matrices with proper dimensions.
*******************************************************************************/
matrix* mat_mul ( matrix* A, matrix* B ) {

  mat_err( ( A->c != B->r ), "Error (mat_mul): Matrix dimensions do not agree." );

  matrix* mul = mat_init( A->r, B->c );

  for( uint i=0; i<A->r; i++ ) {
    for( uint j=0; j<B->c; j++ ) {
      float val = 0.0;
      for( uint k=0; k<A->c; k++ ) {
        val += *( A->e + i*A->c + k ) * *( B->e + k*B->c + j );
      }
      *( mul->e + i*mul->c + j ) = val;
    }
  }

  return mul;
}




/*******************************************************************************
* matrix* mat_inv ( matrix* A )
* Calculates the inverse of a square matrix
*******************************************************************************/
matrix* mat_inv ( matrix* A ) {

  mat_err( ( A->r != A->c ), "Error (mat_inv): Matrix must be square." );

  return mat_divL( A, mat_eye( A->r ) );
}




/*******************************************************************************
* matrix* mat_divL ( matrix* A, matrix* B )
* Solves for X in AX=B; which is equivalent to X=A\B.
*******************************************************************************/
matrix* mat_divL ( matrix* A, matrix* B ) {

  mat_err( ( A->r != A->c ), "Error (mat_divL): A matrix must be square. "        );
  mat_err( ( A->r != B->r ), "Error (mat_divL): A and B must be the same height." );

  matrix* X = mat_init( B->r, B->c );

  matrix* Q = NULL;
  matrix* R = NULL;

  mat_QR( A, &Q, &R );

  matrix* Y = mat_mul( mat_trans(Q), B );

  for( uint k=0; k<B->c; k++ ) {
    for( uint i=B->r-1; i<B->r; i-- ) {
      float val = *( Y->e + i*Y->c + k );
      for( uint j=B->r-1; j>i; j-- )
        val -= *( R->e + i*R->c + j ) * *( X->e + j*X->c + k );
      val /= *( R->e + i*R->c + i );
      *( X->e + i*X->c + k ) = val;
    }
  }

  mat_clear(Q);
  mat_clear(R);
  mat_clear(Y);

  return X;
}




/*******************************************************************************
* matrix* mat_divR ( matrix* A, matrix* B )
* Solves for X in XA=B; which is equivalent to X=B/A.
*******************************************************************************/
matrix* mat_divR ( matrix* A, matrix* B ) {

  mat_err( ( A->r != A->c ), "Error (mat_divR): A matrix must be square.       " );
  mat_err( ( A->c != B->c ), "Error (mat_divR): A and B must be the same width." );

  return mat_mul( B, mat_inv(A) );
}




/*******************************************************************************
* matrix* mat_epow ( matrix* A, uint power )
* Element-wise operation which raises each entry to a specified power.
*******************************************************************************/
matrix* mat_epow ( matrix* A, uint power ) {

  matrix* epow = mat_init( A->r, A->c );
  for( uint i=0; i < A->r * A->c; i++ )  *(epow->e+i) = powf( *(A->e+i), (float)power );

  return epow;
}




/*******************************************************************************
* matrix* mat_pow ( matrix* A, uint power )
* Raises a square matrix to a specified integer power.
*******************************************************************************/
matrix* mat_pow ( matrix* A, uint power ) {

  mat_err( ( A->r != A->c ), "Error (mat_pow): Matrix must be square." );

  switch(power) {
    case 0 : return mat_eye(A->r);
    case 1 : return A;
    default : {
      matrix* pow = mat_eye(A->r);
      for( uint i=0; i<power; i++ )  pow = mat_mul( pow, A );
      return pow;
    }
  }

}




/*******************************************************************************
* matrix* mat_abs ( matrix* A )
* Applies absolute value to all elements within a matrix.
*******************************************************************************/
matrix* mat_abs ( matrix* A ) {

  matrix* abs = mat_init( A->r, A->c );
  for( uint i=0; i < A->r * A->c; i++ )  *(abs->e+i) = fabsf( *(A->e+i) );

  return abs;
}




/*******************************************************************************
* matrix* mat_trans ( matrix* A )
* Returns the transpose of a rectangular matrix.
*******************************************************************************/
matrix* mat_trans ( matrix* A ) {

  matrix* trans = mat_init( A->c, A->r );

  for( uint i=0; i < A->r * A->c; i++ )
    *( trans->e + (i%A->c) * trans->c + i/A->c ) = *( A->e + (i/A->c) * A->c + i%A->c );

  return trans;
}




/*******************************************************************************
* matrix* mat_reshape ( matrix* A, uint r, uint c )
* Reshapes an existing matrix to fit within the specified dimensions.
*******************************************************************************/
matrix* mat_reshape ( matrix* A, uint r, uint c ) {

  mat_err( ( A->r * A->c != r * c ), "Error (mat_reshape): Number of elements do not match." );

  matrix* reshape = mat_init( r, c );
  for( uint i=0; i < A->r * A->c; i++ ) {
    *( reshape->e + (i/c) * c + i%c ) = *( A->e + (i/A->c) * A->c + i%A->c );
  }

  return reshape;
}



