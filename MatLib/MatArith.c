
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

  matrix* out;
  double* outdata;
  double* Adata;
  double* Bdata;
  int     elem = matA->rows * matA->cols;

  mat_err( matA->rows != matB->rows, "Error (mat_add): matrices must have same number of rows" );
  mat_err( matA->cols != matB->cols, "Error (mat_add): matrices must have same number of columns" );

  out = mat_init( matA->rows, matA->cols );
  outdata = out->data;
  Adata = matA->data;
  Bdata = matB->data;

  for ( int i=0; i<elem; i++ ) {
    *(outdata++) = *(Adata++) + *(Bdata++);
  }

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_sub
//  Subtracts two arrays of identical dimension.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_sub ( matrix* matA, matrix* matB ) {

  matrix* out;
  double* outdata;
  double* Adata;
  double* Bdata;
  int     elem = matA->rows * matA->cols;

  mat_err( matA->rows != matB->rows, "Error (mat_sub): matrices must have same number of rows" );
  mat_err( matA->cols != matB->cols, "Error (mat_sub): matrices must have same number of columns" );

  out = mat_init( matA->rows, matA->cols );
  outdata = out->data;
  Adata = matA->data;
  Bdata = matB->data;

  for ( int i=0; i<elem; i++ ) {
    *(outdata++) = *(Adata++) - *(Bdata++);
  }

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_mul
//  Matrix multiplication on two matrices with proper dimension.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_mul ( matrix* matA, matrix* matB ) {

  matrix* out;
  double* outdata;
  double* Adata;
  double* Bdata;

  mat_err( matA->cols != matB->rows, "Error (mat_mul): matrix dimensions do not agree" );

  out = mat_init( matA->rows, matB->cols );
  outdata = out->data;

  for ( int i=0; i< matA->rows; i++ ) {
    for ( int j=0; j< matB->cols; j++ ) {

      Adata = &matA->data[ i * matA->cols ];
      Bdata = &matB->data[j];
      *outdata = 0;

      for ( int k=0; k< matA->cols; k++ ) {
        *outdata += (*Adata) * (*Bdata);
        Adata++;
        Bdata += matB->cols;
      }
      outdata++;

    }
  }

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_pow
//  Raise a square matrix to the specified power.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_pow ( matrix* mat, int power ) {

  matrix* out;

  mat_err( mat->rows != mat->cols, "Error (mat_pow): matrix must be square to raise to a power" );
  mat_err( power<0, "Error (mat_pow): power must be nonnegative" );

  if      ( power==0 )  {  out = mat_eye(mat->rows);  return out;  }
  else if ( power==1 )  {  out = mat_copy(mat);       return out;  }
  else {

    out = mat_init( mat->rows, mat->cols );
    for ( int i=0; i< power-1; i++ ) {
      if ( i==0 )  { out = mat_mul( mat, mat ); }
      else         { out = mat_mul( out, mat ); }
    }

  }

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_trans
//  Returns the transpose of a rectangular matrix or an array.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_trans ( matrix* mat ) {

  matrix*  out      = mat_init( mat->cols, mat->rows );
  double*  outdata  = out->data;
  double*  matdata  = mat->data;

  for ( int i=0; i< mat->rows; i++ ) {
    outdata = &out->data[i];
    for ( int j=0; j< mat->cols; j++ ) {
      *outdata = *matdata;
      matdata++;
      outdata += out->cols;
    }
  }

  return out;
}



