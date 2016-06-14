
//============================================================
//  optFunc.c
//  Justin M Selfridge
//============================================================
//#include "optLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  opt_grad
//  Performs a gradient method type of optimization.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
void opt_grad ( matrix* F ( matrix* ), matrix** x, matrix* d, double tol, double gain, int max )  {

  mat_err( (*x)->cols !=1, "Error (opt_grad): State (x) must be a column vector."              );
  mat_err( d->cols !=1,    "Error (opt_grad): Target derivative (d) must be a column vector."  );

  bool loop = true;
  int  iter = 0;

  do {

    matrix* f = F(*x);
    float err = mat_norm( mat_sub(f,d), 1 );

    if ( err > tol ) {
      iter++;
      *x = mat_sub( *x, mat_scale( mat_sub(f,d), gain ) );
      loop = true;
    }
    else  loop = false;

  } while ( loop && iter < max );

  mat_err( loop, "Error (opt_gard): Optimization exceeded maximum number of steps." );
  printf( "\nOptimization completed in %d steps \n", iter );
  printf("x: ");
  mat_print(*x);
  printf("\n");

  return;
}
*/


