
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatDecomp.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_LU
//  Solves for the LU decomposition of a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_LU ( matrix* mat, matrix** L, matrix** U ) {

  mat_err( *L != NULL || *U != NULL, "Error (mat_LU): Matricies L and U must be null. ");
  mat_err( mat->rows != mat->cols, "Error (mat_LU): Matrix must be square. ");

  int     n = mat->rows;
  double  sum;

  *L = mat_eye(n);
  *U = mat_init(n,n);

  double* data  = mat->data;
  double* Ldata = (*L)->data;
  double* Udata = (*U)->data;

  // Loop through calculations
  for ( int j=0; j<n; j++ ) {

    // Derive upper matrix
    for ( int i=0; i<=j; i++ ) {
      sum = 0.0;
      for ( int k=0; k<i; k++ ) {  sum += Ldata[i*n+k] * Udata[k*n+j];  }
      Udata[i*n+j] = data[i*n+j] - sum;
    }

    // Derive lower matrix
    for ( int i=j+1; i<n; i++ ) {
      sum = 0.0;
      for ( int k=0; k<j; k++ ) {  sum += Ldata[i*n+k] * Udata[k*n+j];  }
      Ldata[i*n+j] = 1.0/Udata[j*n+j] * ( data[i*n+j] - sum );
    }

  }
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_QR
//  Solves for the QR decomposition of a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_QR ( matrix* mat, matrix** Q, matrix** R ) {

  mat_err( *Q!=NULL || *R!=NULL, "Error (mat_QR): Q and R matrices must be initialized as NULL." );

  int r = mat->rows;
  int c = mat->cols;

  matrix* A    = mat_copy(mat);
  matrix* Acol = mat_init(r,1);
  matrix* Qcol = mat_init(r,1);

  *Q = mat_init(r,c);
  *R = mat_init(c,c);

  for ( int i=1; i<=c; i++ ) {
    Acol = mat_getc(A,i);
    Qcol = mat_copy(Acol);
    for ( int j=1; j<i; j++ ) {  Qcol = mat_sub( Qcol, mat_proj( Acol, mat_getc(*Q,j) ) );  }
    mat_setc(*Q,i,mat_uvec(Qcol));
  }

  *R = mat_mul( mat_trans(*Q), A );

  mat_clear(A);
  mat_clear(Acol);
  mat_clear(Qcol);

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_det
//  Returns the determinant of a square matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double mat_det ( matrix* mat ) {

  mat_err( mat->rows != mat->cols, "Error (mat_det): Matrix must be square.");

  int     n = mat->rows;
  double  product = 1.0;
  matrix* L = NULL;
  matrix* U = NULL;

  mat_LU( mat, &L, &U );
  for ( int i=1; i<=n; i++ )  product *=  mat_get(U,i,i);
  mat_clear(L);
  mat_clear(U);

  return product;
}


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


