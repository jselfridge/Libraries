
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatProp.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_trace
//  Returns the trace of a matrix (sum of main diagonal)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double mat_trace ( matrix* mat ) {

  int      n;
  double*  matdata = mat->data;
  double   sum = 0.0;

  if   ( mat->rows < mat->cols )  { n = mat->rows; }
  else                            { n = mat->cols;  }

  for ( int i=0; i<n; i++ ) {  
    sum += *matdata;
    matdata += mat->cols + 1;
  }

  return sum;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_norm
//  Returns the norm of a vector of a specified degree.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double mat_norm ( matrix* vec, int p ) {

  double   norm     = 0.0;
  double   x        = 0.0;
  double*  vecdata  = vec->data;
  int      n        = vec->rows;

  mat_err( p<0, "Error (mat_norm): Degree of a norm must be positive." );
  mat_err( vec->cols!=1, "Error (mat_norm): Input must be a column vector." );

  // Infinity-norm
  if ( p==0 )  {
    for ( int i=0; i<n; i++ ) {
      x = abs( vecdata[i] );
      if (x>norm) { norm = x; }
    }
  }

  // P-norm
  else {
    for ( int i=0; i<n; i++ ) {
      x = abs( vecdata[i] );
      x = pow( x, (double)p );
      norm += x;
    }
    double r = 1.0/ ( (double)p );
    norm = pow( norm, r );
  }

  return norm;
}



