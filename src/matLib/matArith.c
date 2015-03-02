
//============================================================
//  matArith.c
//  Justin M Selfridge
//============================================================
#include "matLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_add
//  Adds two matrices with indentical dimensions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_add ( matrix* matA, matrix* matB )  {

  mat_err( matA->rows != matB->rows, "Error (mat_add): Matrices must have same number of rows."     );
  mat_err( matA->cols != matB->cols, "Error (mat_add): Matrices must have same number of columns."  );

  int i, j;
  double a, b;
  int r = matA->rows;
  int c = matA->cols;
  matrix* add = mat_init(r,c);

  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ ) {
      a = mat_get(matA,i,j);
      b = mat_get(matB,i,j);
      mat_set( add,i,j, a+b );
    }
  }

  return add;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_sub
//  Subtracts two matrices with indentical dimensions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_sub ( matrix* matA, matrix* matB )  {

  mat_err( matA->rows != matB->rows, "Error (mat_sub): Matrices must have same number of rows."     );
  mat_err( matA->cols != matB->cols, "Error (mat_sub): Matrices must have same number of columns."  );

  int i, j;
  double a, b;
  int r = matA->rows;
  int c = matA->cols;
  matrix* sub = mat_init(r,c);

  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ ) {
      a = mat_get(matA,i,j);
      b = mat_get(matB,i,j);
      mat_set( sub,i,j, a-b );
    }
  }

  return sub;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_emul
//  Element-wise multiplication of two matrices with identical dimensions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_emul ( matrix* matA, matrix* matB )  {

  mat_err( matA->rows != matB->rows, "Error (mat_emul): Matrices must have same number of rows."     );
  mat_err( matA->cols != matB->cols, "Error (mat_emul): Matrices must have same number of columns."  );

  int i, j;
  double a, b;
  int r = matA->rows;
  int c = matA->cols;
  matrix* emul = mat_init(r,c);

  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ ) {
      a = mat_get(matA,i,j);
      b = mat_get(matB,i,j);
      mat_set( emul,i,j, a*b );
    }
  }

  return emul;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_ediv
//  Element-wise division of two matrices with identical dimensions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_ediv ( matrix* matA, matrix* matB )  {

  mat_err( matA->rows != matB->rows, "Error (mat_ediv): Matrices must have same number of rows."     );
  mat_err( matA->cols != matB->cols, "Error (mat_ediv): Matrices must have same number of columns."  );

  int i, j;
  double a, b;
  int r = matA->rows;
  int c = matA->cols;
  matrix* ediv = mat_init(r,c);

  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ ) {
      a = mat_get(matA,i,j);
      b = mat_get(matB,i,j);
      mat_set( ediv,i,j, a/b );
    }
  }

  return ediv;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_mul
//  Multiplication of two matrices with proper dimensions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_mul ( matrix* matA, matrix* matB )  {

  mat_err( matA->cols != matB->rows, "Error (mat_mul): Matrix dimensions do not agree." );

  int i, j, k;
  double a, b, val;
  int r = matA->rows;
  int c = matB->cols;
  matrix* mul = mat_init(r,c);

  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ ) {
      val = 0.0;
      for ( k=1; k<= matA->cols; k++ ) {
	a = mat_get(matA,i,k);
	b = mat_get(matB,k,j);
	val += a * b;
      }
      mat_set( mul,i,j, val );
    }
  }

  return mul;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_pow
//  Raises a square matrix to the specified power.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_pow ( matrix* mat, int power )  {

  mat_err( mat->rows != mat->cols, "Error (mat_pow): Matrix must be square."         );
  mat_err( power <0,               "Error (mat_pow): Exponent must be nonnegative."  );

  int i; 
  int n = mat->rows;
  matrix* pow;

  if      ( power == 0 )  pow = mat_eye(n);
  else if ( power == 1 )  pow = mat_copy(mat);
  else {
    pow = mat_init(n,n);
    for ( i=1; i<= power-1; i++ ) {
      if (i==1)  pow = mat_mul( mat, mat );
      else       pow = mat_mul( pow, mat );
    }
  }

  return pow;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_abs
//  Applies absolute value to all elements within a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_abs ( matrix* mat )  {

  int i, j, r, c;
  double val;
  matrix* abs;

  r   = mat->rows;
  c   = mat->cols;
  abs = mat_init(r,c);

  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ ) {
      val = fabs( mat_get(mat,i,j) );
      mat_set( abs,i,j, val );
    }
  }

  return abs;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_trans
//  Returns the transpose of a rectangular matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_trans ( matrix* mat ) {

  int i, j, r, c;
  double val;
  matrix* trans;

  r = mat->rows;
  c = mat->cols;
  trans = mat_init(c,r);

  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ ) {
      val = mat_get(mat,i,j);
      mat_set( trans,j,i, val );
    }
  }

  return trans;
}



