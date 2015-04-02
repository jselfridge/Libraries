
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



