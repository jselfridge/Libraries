/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatProp.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


// WORK IN PROGRESS !!!
// Need to find eigenvalues first
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_rank
//  Returns the rank of a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int mat_rank ( matrix* mat ) {

  printf("mat_rank is a work in progress... \n");

  return 0;
}


// WORK IN PROGRESS !!!
// Only works for real eigenvalues, not complex...
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_eigval
//  Returns the eigenvalues of a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_eigval ( matrix* mat, double tol, int max ) {

  printf("mat_eigval is a work in progress...\n");

  mat_err( mat->rows != mat->cols, "Error (mat_eigval): Matrix must be square." );

  bool    loop = true;
  int     iter = 0;
  int     n    = mat->rows;
  matrix* old  = mat_copy(mat);
  matrix* new  = mat_init(n,n);

  // Start while loop
  while(1) {
    //while(loop) {

    // Find QR of old matrix
    matrix* Q = NULL;
    matrix* R = NULL;
    mat_QR( old, &Q, &R );
    //printf("Q: ");  mat_print(Q);
    //printf("R: ");  mat_print(R);

    // Use RQ to find new matrix
    new = mat_mul(R,Q);
    printf("mat: ");  mat_print(new);

    // Test changes
    for ( int i=1; i<=n; i++ ) {
      double err = fabs( mat_get(new,i,i) - mat_get(old,i,i) );
      //printf("err: %f \n", err);
      if ( err > tol )  {  old = mat_copy(new);  break;  }
      if ( i == n )     {  loop = false;  }
    }

    // Debugging statements
    //if (loop) { printf("Keep looping \n"); }
    //else      { printf("Exit loop \n"); }

    // Increment number of iterations
    iter++;
    printf("iter: %d \n",iter);
    mat_err( iter >= max, "Error (mat_eigval): Exceeded maximum number of iterations." );

  }  // Exit while loop

  printf("Result [%d steps]: ", iter);  mat_print(new);

  mat_clear(old);
  mat_clear(new);

}



*/
