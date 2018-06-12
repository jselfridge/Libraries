/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatDecomp.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_divL
//  Solves for X in B=AX, equivalent to X=A\B.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_divL ( matrix* A, matrix* B ) {

  mat_err( A->rows != A->cols, "Error (mat_divL): A matrix must be square. " );
  mat_err( A->rows != B->rows, "Error (mat_divL): A and B must be the same height." );

  int     n  = A->rows;  
  int     r  = B->rows;
  int     c  = B->cols;
  double* Bd = B->data;

  matrix* L = NULL;  
  matrix* U = NULL;
  mat_LU( A, &L, &U );
  double* Ld = L->data;
  double* Ud = U->data;

  matrix* Y;
  matrix* X;
  Y = mat_init(1,n);
  X = mat_init(r,c);
  double* Yd = Y->data;
  double* Xd = X->data;

  double  sum;
  double* row;

  for ( int k=0; k<c; k++ ) {

    // L backward subsitituion:  L * y = B
    for ( int i=0; i<n; i++ ) {
      row = Ld + i*n;
      sum = 0;
      for ( int j=0; j<i; j++ ) {
	sum += Yd[j] * (*row++);
      }
      Yd[i] = ( Bd[i*c+k] - sum) / *row;
    }

    // U backward subsitituion:  U * x = y
    for ( int i=n-1; i>=0; i-- ) {
      row = Ud + (i*n) + (n-1);
      sum = 0;
      for ( int j=n-1; j>i; j-- ) {
	sum += Xd[j*c+k] * (*row--);
      }
      Xd[i*c+k] = (Yd[i] - sum) / *row;
    }

  }

  mat_clear(L);
  mat_clear(U);
  mat_clear(Y);

  return X;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_divR
//  Solves for X in B=XA, equivalent to X=B/A.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_divR ( matrix* B, matrix* A ) {

  mat_err( A->rows != A->cols, "Error (mat_divR): A matrix must be square. " );
  mat_err( A->cols != B->cols, "Error (mat_divR): A and B must be the same width." );

  matrix* X = mat_init( B->rows, B->cols );
  X = mat_mul( B, mat_inv(A) );

  return X;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_inv
//  Returns the inverse of a square matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_inv ( matrix* mat ) {

  mat_err( mat->rows != mat->cols, "Error (mat_inv): Matrix must be square." );

  matrix* eye = mat_eye( mat->rows );
  matrix* inv = mat_divL( mat, eye );

  mat_clear(eye);
  return inv;
}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Mat_DivL (temp replacement for mat_divL)
//  Solves for X in B=AX, equivalent to X=A\B.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//matrix* Mat_DivL ( matrix* A, matrix* B ) {

  //mat_err( A->rows != B->rows, "Error (mat_divL): A and B must be the same height." );

  //matrix* x;
  //return x;
  
//}

  /*
  int     n  = A->rows;  
  int     r  = B->rows;
  int     c  = B->cols;
  double* Bd = B->data;

  matrix* L = NULL;  
  matrix* U = NULL;
  mat_LU( A, &L, &U );
  double* Ld = L->data;
  double* Ud = U->data;

  matrix* Y;
  matrix* X;
  Y = mat_init(1,n);
  X = mat_init(r,c);
  double* Yd = Y->data;
  double* Xd = X->data;

  double  sum;
  double* row;

  for ( int k=0; k<c; k++ ) {

    // L backward subsitituion:  L * y = B
    for ( int i=0; i<n; i++ ) {
      row = Ld + i*n;
      sum = 0;
      for ( int j=0; j<i; j++ ) {
	sum += Yd[j] * (*row++);
      }
      Yd[i] = ( Bd[i*c+k] - sum) / *row;
    }

    // U backward subsitituion:  U * x = y
    for ( int i=n-1; i>=0; i-- ) {
      row = Ud + (i*n) + (n-1);
      sum = 0;
      for ( int j=n-1; j>i; j-- ) {
	sum += Xd[j*c+k] * (*row--);
      }
      Xd[i*c+k] = (Yd[i] - sum) / *row;
    }

  }

  mat_clear(L);
  mat_clear(U);
  mat_clear(Y);

  return X;
  */


