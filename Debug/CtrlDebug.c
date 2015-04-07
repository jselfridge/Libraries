
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  CtrlDebug.c
//  Justin M Selfridge
//  Script to debug the CtrlLib Library
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CtrlDebug.h"


// Debugging function 
void DebugCtrlLib() {
  printf("\n   --- CtrlLib Debugging --- \n\n");
  CtrlLin();
  printf("   --- CtrlLib Complete --- \n\n");
  return;
}


// Linearization
void CtrlLin() {

  printf("Linearization \n");

  // Define states
  matrix* x = mat_init(4,1);
  mat_set(x,1,1,0.0);
  mat_set(x,2,1,0.0);
  mat_set(x,3,1,0.0);
  mat_set(x,4,1,0.0);
  printf("x: ");  mat_print(x);

  // Define inputs
  matrix* u = mat_init(2,1);
  mat_set(u,1,1,0.0);
  mat_set(u,2,1,0.0);
  printf("u: ");  mat_print(u);

  // Initialize martices
  matrix* A = mat_init(4,4);
  matrix* B = mat_init(4,2);

  // Define perturbation
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

  printf("\n");
}




// Linearization function
void ctrl_lin( matrix* f ( matrix*, matrix* ), matrix* x, matrix* u, matrix** A, matrix** B, double d ) {

  int n = x->rows;
  int m = u->rows;

  mat_err( x->cols!=1, "Error (ctrl_lin): States (x) must be a column vector." );
  mat_err( u->cols!=1, "Error (ctrl_lin): Inputs (u) must be a column vector." );
  mat_err( (*A)->rows!=n || (*A)->cols!=n, "Error (ctrl_lin): State matrix (A) must be [nxn]." );
  mat_err( (*B)->rows!=n || (*B)->cols!=m, "Error (ctrl_lin): Input matrix (B) must be [nxm]." );

  matrix* xp = mat_init(n,1);
  matrix* xn = mat_init(n,1);
  matrix* up = mat_init(m,1);
  matrix* un = mat_init(m,1);
  matrix* fp = mat_init(n,1);
  matrix* fn = mat_init(n,1);
  matrix* C  = mat_init(n,1);

  for ( int i=1; i<=n; i++ ) {
    xp = mat_copy(x);  mat_set( xp,i,1, mat_get(x,i,1)+d );
    xn = mat_copy(x);  mat_set( xn,i,1, mat_get(x,i,1)-d );
    fp = f(xp,u);
    fn = f(xn,u);
    C = mat_scale( mat_sub(fp,fn), 1/(2*d));
    for ( int j=1; j<=n; j++ ) {  mat_set( *A,j,i, mat_get(C,j,1) );  }
  }

  for ( int i=1; i<=m; i++ ) {
    up = mat_copy(u);  mat_set( up,i,1, mat_get(u,i,1)+d );
    un = mat_copy(u);  mat_set( un,i,1, mat_get(u,i,1)-d );
    fp = f(x,up);
    fn = f(x,un);
    C = mat_scale( mat_sub(fp,fn), 1/(2*d));
    for ( int j=1; j<=n; j++ ) {  mat_set( *B,j,i, mat_get(C,j,1) );  }
  }

  mat_clear(xp);
  mat_clear(xn);
  mat_clear(up);
  mat_clear(un);
  mat_clear(fp);
  mat_clear(fn);
  mat_clear(C);

}




// Derivative function
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



// Derivative function
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



