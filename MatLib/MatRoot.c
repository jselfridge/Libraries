
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatRoot.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_root
//  Finds the roots of a polynomial.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_root ( matrix* poly ) {

  mat_err( poly->rows!=1, "Error(mat_root): Polynomial must be input as a row vector." );

  // Declare counters
  int n = poly->cols;
  int d = n-1;

  // Assign coefficients
  matrix* c = mat_init(n,1);
  for ( int i=1; i<=n; i++ ) {
    int j = n+1-i;
    mat_set( c,j,1, mat_get(poly,1,i) );
  }
  mat_print(c);





  // Clean up matrices
  mat_clear(c);


  // return;
}



