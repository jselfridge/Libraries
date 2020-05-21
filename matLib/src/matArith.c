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

  matrix* N = mat_init( A->r, A->c );
  for( uint i=0; i < A->r * A->c; i++ )  *(N->e+i) = *(A->e+i) + *(B->e+i);

  return N;
}




/*******************************************************************************
* matrix* mat_sub ( matrix* A, matrix* B )
* Subtracts two matrices with indentical dimensions.
*******************************************************************************/
matrix* mat_sub ( matrix* A, matrix* B ) {

  mat_err( ( A->r != B->r ), "Error (mat_sub): Matrices must have same number of rows."    );
  mat_err( ( A->c != B->c ), "Error (mat_sub): Matrices must have same number of columns." );

  matrix* N = mat_init( A->r, A->c );
  for( uint i=0; i < A->r * A->c; i++ )  *(N->e+i) = *(A->e+i) - *(B->e+i);

  return N;
}




/*******************************************************************************
* matrix* mat_emul ( matrix* A, matrix* B )
* Element-wise multiplication of two matrices with identical dimensions.
*******************************************************************************/
matrix* mat_emul ( matrix* A, matrix* B ) {

  mat_err( ( A->r != B->r ), "Error (mat_emul): Matrices must have same number of rows."    );
  mat_err( ( A->c != B->c ), "Error (mat_emul): Matrices must have same number of columns." );

  matrix* N = mat_init( A->r, A->c );
  for( uint i=0; i < A->r * A->c; i++ )  *(N->e+i) = *(A->e+i) * *(B->e+i);

  return N;
}




/*******************************************************************************
* matrix* mat_ediv ( matrix* A, matrix* B )
* Element-wise division of two matrices with identical dimensions.
*******************************************************************************/
matrix* mat_ediv ( matrix* A, matrix* B ) {

  mat_err( ( A->r != B->r ), "Error (mat_ediv): Matrices must have same number of rows."    );
  mat_err( ( A->c != B->c ), "Error (mat_ediv): Matrices must have same number of columns." );

  matrix* N = mat_init( A->r, A->c );
  for( uint i=0; i < A->r * A->c; i++ )  *(N->e+i) = *(A->e+i) / *(B->e+i);

  return N;
}




/*******************************************************************************
* matrix* mat_mul ( matrix* A, matrix* B )
* Multiplication of two matrices with proper dimensions.
*******************************************************************************/
matrix* mat_mul ( matrix* A, matrix* B ) {

  mat_err( ( A->c != B->r ), "Error (mat_mul): Matrix dimensions do not agree." );

  matrix* N = mat_init( A->r, B->c );

  for( uint i=0; i<A->r; i++ ) {
    for( uint j=0; j<B->c; j++ ) {
      float val = 0.0;
      for( uint k=0; k<A->c; k++ ) {
        val += *( A->e + i*A->c + k ) * *( B->e + k*B->c + j );
      }
      *( N->e + i*N->c + j ) = val;
    }
  }

  return N;
}




/*******************************************************************************
* matrix* mat_inv ( matrix* M )
* Calculates the inverse of a square matrix
*******************************************************************************/
/*matrix* mat_inv ( matrix* M ) {

  mat_err( ( M->r != M->c ), "Error (mat_inv): Matrix must be square." );

  return mat_divL( M, mat_eye( M->r ) );
}*/




/*******************************************************************************
* matrix* mat_divL ( matrix* A, matrix* B )
* Solves for X in AX=B; which is equivalent to X=A\B.
*******************************************************************************/
/*matrix* mat_divL ( matrix* A, matrix* B ) {

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
}*/




/*******************************************************************************
* matrix* mat_divR ( matrix* A, matrix* B )
* Solves for X in XA=B; which is equivalent to X=B/A.
*******************************************************************************/
/*matrix* mat_divR ( matrix* A, matrix* B ) {

  mat_err( ( A->r != A->c ), "Error (mat_divR): A matrix must be square.       " );
  mat_err( ( A->c != B->c ), "Error (mat_divR): A and B must be the same width." );

  return mat_mul( B, mat_inv(A) );
}*/




/*******************************************************************************
* matrix* mat_epow ( matrix* M, uint power )
* Element-wise operation which raises each entry to a specified power.
*******************************************************************************/
matrix* mat_epow ( matrix* M, uint power ) {

  matrix* N = mat_init( M->r, M->c );
  for( uint i=0; i < M->r * M->c; i++ )  *(N->e+i) = powf( *(M->e+i), (float)power );

  return N;
}




/*******************************************************************************
* matrix* mat_pow ( matrix* M, uint power )
* Raises a square matrix to a specified integer power.
*******************************************************************************/
matrix* mat_pow ( matrix* M, uint power ) {

  mat_err( ( M->r != M->c ), "Error (mat_pow): Matrix must be square." );

  switch(power) {
    case 0 : return mat_eye(M->r);
    case 1 : return M;
    default : {
      matrix* N = mat_eye(M->r);
      for( uint i=0; i<power; i++ )  N = mat_mul( N, M );
      return N;
    }
  }

}




/*******************************************************************************
* matrix* mat_abs ( matrix* M )
* Applies absolute value to all elements within a matrix.
*******************************************************************************/
matrix* mat_abs ( matrix* M ) {

  matrix* N = mat_init( M->r, M->c );
  for( uint i=0; i < M->r * M->c; i++ )  *(N->e+i) = fabsf( *(M->e+i) );

  return N;
}




/*******************************************************************************
* matrix* mat_trans ( matrix* M )
* Returns the transpose of a rectangular matrix.
*******************************************************************************/
matrix* mat_trans ( matrix* M ) {

  matrix* N = mat_init( M->c, M->r );

  for( uint i=0; i < M->r * M->c; i++ )
    *( N->e + (i%M->c) * N->c + i/M->c ) = *( M->e + (i/M->c) * M->c + i%M->c );

  return N;
}




/*******************************************************************************
* matrix* mat_reshape ( matrix* M, uint r, uint c )
* Reshapes an existing matrix to fit within the specified dimensions.
*******************************************************************************/
matrix* mat_reshape ( matrix* M, uint r, uint c ) {

  mat_err( ( M->r * M->c != r * c ), "Error (mat_reshape): Number of elements do not match." );

  matrix* N = mat_init( r, c );
  for( uint i=0; i < M->r * M->c; i++ ) {
    *( N->e + (i/c) * c + i%c ) = *( M->e + (i/M->c) * M->c + i%M->c );
  }

  return N;
}



