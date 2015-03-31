
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


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_skew
//  Returns skew symmetric matrix of a three element vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_skew ( matrix* vec ) {

  matrix*  out = mat_init(3,3);
  double   x, y, z;

  mat_err( ( vec->rows!=3 || vec->cols!=1 ), "Error (mat_skew): vector must be [3x1]" );

  x = mat_get(vec,1,1);  mat_set(out,3,2,x);  mat_set(out,2,3,-x);
  y = mat_get(vec,2,1);  mat_set(out,1,3,y);  mat_set(out,3,1,-y);
  z = mat_get(vec,3,1);  mat_set(out,2,1,z);  mat_set(out,1,2,-z);

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_cross
//  Returns cross product of two three element vectors.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_cross ( matrix* vecA, matrix* vecB ) {

  matrix*  out = mat_init(3,1);

  mat_err( ( vecA->rows!=3 || vecA->cols!=1 ), "Error (mat_cross): vector A must be [3x1]" );
  mat_err( ( vecB->rows!=3 || vecB->cols!=1 ), "Error (mat_cross): vector B must be [3x1]" );

  return out = mat_mul( mat_skew(vecA), vecB );
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_dot
//  Returns dot product of two arbitrary length vectors.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double mat_dot ( matrix* vecA, matrix* vecB ) {

  mat_err( ( vecA->cols!=1 || vecB->cols!=1 ), "Error (mat_dot): dot product requires vector inputs" );
  mat_err( ( vecA->rows != vecB->rows ), "Error (mat_dot): vectors must be the same length" );

  double out = 0.0;
  for ( int r=1; r<= vecA->rows; r++ ) {
    out += (mat_get(vecA,r,1)) * (mat_get(vecB,r,1)) ;
  }

  return out;
}



