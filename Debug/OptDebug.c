
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  OptDebug.c
//  Justin M Selfridge
//  Script to debug the OptLib Library
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "OptDebug.h"




// Debugging function 
void DebugOptLib() {
  printf("\n   --- OptLib Debugging --- \n\n");

  // Define optimization parameters
  double gain = 0.001;
  double tol  = 0.001;
  int    iter = 0;

  // Define initial condition
  matrix* x = mat_init(2,1);
  mat_set(x,1,1,0.0);
  mat_set(x,2,1,0.1);
  printf("x: ");
  mat_print(x);

  // Define target condition
  matrix* t = mat_init(2,1);
  mat_set(t,1,1,2.0);
  mat_set(t,2,1,-3.0);
  printf("t: ");
  mat_print(t);

  // Initialize stuff within the loop
  matrix* f;
  double  e;
  int     iterate = 0;  // change to bool later

  // Optimization loop
  do {

    // Derivative
    f = F(x);
    printf("f: ");
    mat_print(f);

    // Error magnitude
    e = mat_norm( mat_sub(f,t), 1 );
    printf("e: %1.6f \n", e);

    // Revise state
    if (e>tol) {
      iterate = 1;
      x = mat_sub( x, mat_scale(f,gain) );
      printf("x: ");
      mat_print(x);
      iter++;
    }
    else { iterate = 0; }

  // Keep looping
  } while ( iterate );

  printf("Iterations: %d", iter);

  // Exit program
  printf("\n");
  printf("   --- OptLib Complete --- \n\n");
  return;
}



// Derivative function
matrix* F ( matrix* x ) {

  matrix* f = mat_init(2,1);

  double x1 = mat_get(x,1,1);
  double x2 = mat_get(x,2,1);

  double f1 = x1*x2 + 2*x1 - 3*x2 + 2;
  double f2 = pow(x1,2) - pow(x2,2) + 3*x1*x2 -3;

  mat_set( f,1,1,f1 );
  mat_set( f,2,1,f2 );

  return f;
}
