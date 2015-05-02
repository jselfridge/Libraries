
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  CtrlDebug.c
//  Justin M Selfridge
//  Script to debug the CtrlLib Library
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CtrlDebug.h"




// Debugging function 
void DebugCtrlLib() {
  printf("\n   --- CtrlLib Debugging --- \n\n");
  CtrlFunc();
  printf("   --- CtrlLib Complete --- \n\n");
  return;
}




// Control functions
void CtrlFunc() {
  /*
  // Define states
  matrix* x = mat_init(4,1);
  mat_set(x,1,1,1.0);
  mat_set(x,2,1,1.0);
  mat_set(x,3,1,1.0);
  mat_set(x,4,1,1.0);
  printf("x: ");  mat_print(x);

  // Define inputs
  matrix* u = mat_init(2,1);
  mat_set(u,1,1,0.0);
  mat_set(u,2,1,0.0);
  printf("u: ");  mat_print(u);

  // Initialize martices
  matrix* A = mat_init(4,4);
  matrix* B = mat_init(4,2);

  // Linearization
  printf("Linearization \n");
  double d = 0.001;

  // First linearization
  printf("\nPlant1 linearization \n");
  ctrl_lin( Plant1, x, u, &A, &B, d );
  printf("A: ");  mat_print(A);
  printf("B: ");  mat_print(B);

  // Second linearization
  printf("\nPlant2 linearization \n");
  ctrl_lin( Plant2, x, u, &A, &B, d );
  printf("A: ");  mat_print(A);
  printf("B: ");  mat_print(B);

  // Controllability
  matrix* ctrb = ctrl_ctrb(A,B);
  printf("\nCtrb: ");  mat_print(ctrb);
  mat_clear(ctrb);

  // Observability
  matrix* obsv = ctrl_obsv(A,mat_trans(B));
  printf("\nObsv: ");  mat_print(obsv);
  mat_clear(obsv);
  */
  printf("\n");
}



/*
// Derivative function 1
matrix* Plant1 ( matrix* x, matrix* u ) {

  // Initialize derivative
  matrix* f = mat_init(4,1);

  // Collect states
  double x1 = mat_get(x,1,1);
  double x2 = mat_get(x,2,1);
  double x3 = mat_get(x,3,1);
  double x4 = mat_get(x,4,1);

  // Collect inputs
  double u1 = mat_get(u,1,1);
  double u2 = mat_get(u,2,1);

  double f1 = x3;
  double f2 = x4;
  double f3 = -2*x1 -3*x3 + 4*u1;
  double f4 = -4*x2 -5*x4 + u2;

  mat_set( f,1,1,f1 );
  mat_set( f,2,1,f2 );
  mat_set( f,3,1,f3 );
  mat_set( f,4,1,f4 );

  return f;
}
*/


/*
// Derivative function 2
matrix* Plant2 ( matrix* x, matrix* u ) {

  // Initialize derivative
  matrix* f = mat_init(4,1);

  // Collect states
  double x1 = mat_get(x,1,1);
  double x2 = mat_get(x,2,1);
  double x3 = mat_get(x,3,1);
  double x4 = mat_get(x,4,1);

  // Collect inputs
  double u1 = mat_get(u,1,1);
  double u2 = mat_get(u,2,1);

  double f1 = x1*x2 -x1*x3 + 2*x1 - 3*x2 + x4 + 4*u1;
  double f2 = pow(x1,2) - pow(x2,2) + 3*x1*x2 + x2*x3 + - x2*x4 + 2*u2 - u1;
  double f3 = pow(x3,2) + 2*x1*x3 - 4*x2*x3 + x1*x2 + x1*x4 - 3*u2;
  double f4 = 3*x1 - 2*x4 + pow(x4,2) + 2*u1 - u2;

  mat_set( f,1,1,f1 );
  mat_set( f,2,1,f2 );
  mat_set( f,3,1,f3 );
  mat_set( f,4,1,f4 );

  return f;
}
*/


