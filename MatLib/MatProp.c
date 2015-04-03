
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
  int      r    = mat->rows;
  int      c    = mat->cols;
  double*  data = mat->data;
  double   sum  = 0.0;

  if   (r<c) { n=r; }
  else       { n=c; }

  for ( int i=0; i<n; i++ ) {  
    sum += *data;
    data += c+1;
  }

  return sum;
}



