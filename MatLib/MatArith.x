/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatArith.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_add
//  Adds two arrays of indentical dimension.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_add ( matrix* matA, matrix* matB ) {

  mat_err( matA->rows != matB->rows, "Error (mat_add): Matrices must have same number of rows." );
  mat_err( matA->cols != matB->cols, "Error (mat_add): Matrices must have same number of columns." );

  matrix* out   = mat_init( matA->rows, matA->cols );
  double* odata = out->data;
  double* Adata = matA->data;
  double* Bdata = matB->data;
  int     n     = matA->rows * matA->cols;

  for ( int i=0; i<n; i++ ) {
    *(odata++) = *(Adata++) + *(Bdata++);
  }

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_sub
//  Subtracts two arrays of identical dimension.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_sub ( matrix* matA, matrix* matB ) {

  mat_err( matA->rows != matB->rows, "Error (mat_sub): Matrices must have same number of rows." );
  mat_err( matA->cols != matB->cols, "Error (mat_sub): Matrices must have same number of columns." );

  matrix* out   = mat_init( matA->rows, matA->cols );
  double* odata = out->data;
  double* Adata = matA->data;
  double* Bdata = matB->data;
  int     n     = matA->rows * matA->cols;

  for ( int i=0; i<n; i++ ) {
    *(odata++) = *(Adata++) - *(Bdata++);
  }

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_mul
//  Matrix multiplication on two matrices of proper dimension.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_mul ( matrix* matA, matrix* matB ) {

  int Ar = matA->rows;  int Ac = matA->cols;
  int Br = matB->rows;  int Bc = matB->cols;

  mat_err( Ac!=Br, "Error (mat_mul): Matrix dimensions do not agree." );

  matrix* out   = mat_init(Ar,Bc);
  double* odata = out->data;
  double* Adata = matA->data;
  double* Bdata = matB->data;

  for ( int i=0; i<Ar; i++ ) {
    for ( int j=0; j<Bc; j++ ) {
      double val = 0.0;
      for ( int k=0; k<Ac; k++ ) {
	double Aval = *( Adata + (i*Ac) + k );
	double Bval = *( Bdata + (k*Bc) + j );
        val += Aval * Bval;
      }
      *odata = val;
      odata++;
    }
  }

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_pow
//  Raise a square matrix to the specified power.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_pow ( matrix* mat, int power ) {

  mat_err( mat->rows != mat->cols, "Error (mat_pow): Matrix must be square." );
  mat_err( power<0, "Error (mat_pow): Exponent must be nonnegative." );

  int n = mat->rows;
  matrix* out;

  if      ( power == 0 )  {  out = mat_eye(n);     return out;  }
  else if ( power == 1 )  {  out = mat_copy(mat);  return out;  }
  else {
    out = mat_init(n,n);
    for ( int i=0; i< power-1; i++ ) {
      if ( i == 0 )  { out = mat_mul( mat, mat ); }
      else           { out = mat_mul( out, mat ); }
    } return out;
  }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_abs
//  Applies absolute value to elements within a matrix or an array.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_abs ( matrix* mat ) {

  int r = mat->rows;
  int c = mat->cols;
  int n = r*c;

  matrix* abs = mat_init(r,c);
  double* adata = abs->data;
  double* mdata = mat->data;

  for ( int i=0; i<n; i++ ) {
    *adata = fabs(*mdata);
    mdata++;
    adata++;
  }

  return abs;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_trans
//  Returns the transpose of a rectangular matrix or an array.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_trans ( matrix* mat ) {

  int      r        = mat->rows;
  int      c        = mat->cols;
  matrix*  out      = mat_init(c,r);
  double*  outdata  = out->data;
  double*  matdata  = mat->data;

  for ( int i=0; i<r; i++ ) {
    for ( int j=0; j<c; j++ ) {
      int offset = (j*r)+i;
      *( outdata + offset ) = *matdata;
      matdata++;
    }
  }

  return out;
}



*/
