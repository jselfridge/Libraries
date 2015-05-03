
//============================================================
//  CtrlDebug.c
//  Justin M Selfridge
//============================================================
#include "CtrlDebug.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  main
//  Runs the main CtrlLib debugging program.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main ()  {
  printf("\n   --- CtrlLib Debugging --- \n\n");
  CtrlFunc();
  printf("   --- CtrlLib Complete --- \n\n");
  return 0;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  CtrlFunc
//  Debugs the CtrlFunc file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void CtrlFunc ()  {

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
  ctrl_lin( Plant1, x, u, A, B, d );
  printf("A: ");  mat_print(A);
  printf("B: ");  mat_print(B);

  // Second linearization
  printf("\nPlant2 linearization \n");
  ctrl_lin( Plant2, x, u, A, B, d );
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

  printf("\n");
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Plant1
//  Provides a nonlinear system to test linearization function.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* Plant1 ( matrix* x, matrix* u )  {

  double x1, x2, x3, x4;
  double u1, u2;
  double f1, f2, f3, f4;
  matrix* f;

  x1 = mat_get(x,1,1);
  x2 = mat_get(x,2,1);
  x3 = mat_get(x,3,1);
  x4 = mat_get(x,4,1);

  u1 = mat_get(u,1,1);
  u2 = mat_get(u,2,1);

  f1 = x3;
  f2 = x4;
  f3 = -2*x1 -3*x3 + 4*u1;
  f4 = -4*x2 -5*x4 + u2;

  f = mat_init(4,1);
  mat_set( f,1,1,f1 );
  mat_set( f,2,1,f2 );
  mat_set( f,3,1,f3 );
  mat_set( f,4,1,f4 );

  return f;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Plant2
//  Provides a nonlinear system to test linearization function.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* Plant2 ( matrix* x, matrix* u )  {

  double x1, x2, x3, x4;
  double u1, u2;
  double f1, f2, f3, f4;
  matrix* f;

  x1 = mat_get(x,1,1);
  x2 = mat_get(x,2,1);
  x3 = mat_get(x,3,1);
  x4 = mat_get(x,4,1);

  u1 = mat_get(u,1,1);
  u2 = mat_get(u,2,1);

  f1 = x1*x2 -x1*x3 + 2*x1 - 3*x2 + x4 + 4*u1;
  f2 = pow(x1,2) - pow(x2,2) + 3*x1*x2 + x2*x3 + - x2*x4 + 2*u2 - u1;
  f3 = pow(x3,2) + 2*x1*x3 - 4*x2*x3 + x1*x2 + x1*x4 - 3*u2;
  f4 = 3*x1 - 2*x4 + pow(x4,2) + 2*u1 - u2;

  f = mat_init(4,1);
  mat_set( f,1,1,f1 );
  mat_set( f,2,1,f2 );
  mat_set( f,3,1,f3 );
  mat_set( f,4,1,f4 );

  return f;
}



