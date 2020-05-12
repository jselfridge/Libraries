
//============================================================
//  optDebug.c
//  Justin M Selfridge
//============================================================
//#include "optDebug.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  main
//  Runs the main OptLib debugging program.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
int main ()  {
  printf("\n   --- OptLib Debugging --- \n\n");
  OptGrad();
  printf("   --- OptLib Complete --- \n\n");
  return 0;
}
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  OptGrad
//  Debugs the gradient method optimization.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
void OptGrad ()  {

  // Define optimization parameters
  double gain = 0.05;
  double tol  = 0.00001;
  int    max  = 100000;

  // Define initial condition
  matrix* x = mat_init(2,1);
  mat_set( x,1,1, 0.6 );
  mat_set( x,2,1, 0.2 );
  printf("x: ");
  mat_print(x);

  // Define target derivative
  matrix* d = mat_init(2,1);
  mat_set( d,1,1,  2.0 );
  mat_set( d,2,1, -3.0 );
  printf("d: ");
  mat_print(d);

  // Run optimization
  opt_grad ( Deriv, &x, d, tol, gain, max );

  // Summarize the results
  printf("Back in main function \n");
  printf("x: ");
  mat_print(x);
  printf("Deriv(x): ");
  mat_print( Deriv(x) );

  printf("\n");
  return;
}
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Deriv
//  Generates a derivative function for optimization debugging.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
matrix* Deriv ( matrix* x )  {

  double x1, x2, f1, f2;
  matrix* f;

  x1 = mat_get(x,1,1);
  x2 = mat_get(x,2,1);

  f1 = x1*x2 + 2*x1 - 3*x2 + 2;
  f2 = pow(x1,2) - pow(x2,2) + 3*x1*x2 -3;

  f = mat_init(2,1);
  mat_set( f,1,1,f1 );
  mat_set( f,2,1,f2 );

  return f;
}
*/


