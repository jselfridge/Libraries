
==============
MatDebug.c WIP
==============



/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatProp
//  Debugs the MatProp file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MatProp() {
  printf("Matrix properties \n");

  // Rank
  int rank = mat_rank(M44);
  printf( "Rank: %d \n", rank );

  // Test eigenvalues
  double tol  = 0.0000001;
  int    iter = 10;

  // First eigenvalue test
  matrix* A1 = mat_init(3,3);
  mat_set(A1,1,1, 1 );  mat_set(A1,1,2, 0 );  mat_set(A1,1,3, 0 );
  mat_set(A1,2,1, 4 );  mat_set(A1,2,2, 2 );  mat_set(A1,2,3, 0 );
  mat_set(A1,3,1, 5 );  mat_set(A1,3,2, 6 );  mat_set(A1,3,3, 3 );
  printf("A1: ");  mat_print(A1);
  mat_eigval(A1,tol,iter);
  mat_clear(A1);

  // Second eigenvalue test
  matrix* A2 = mat_init(3,3);
  mat_set(A2,1,1, 0 );  mat_set(A2,1,2, 1 );  mat_set(A2,1,3, 0 );
  mat_set(A2,2,1, 0 );  mat_set(A2,2,2, 0 );  mat_set(A2,2,3, 1 );
  mat_set(A2,3,1,-30);  mat_set(A2,3,2,-31);  mat_set(A2,3,3,-10);
  printf("A2: ");  mat_print(A2);
  mat_eigval(A2,tol,iter);
  mat_clear(A2);

  // Third eigenvalue test
  matrix* A3 = mat_init(3,3);
  mat_set(A3,1,1, 0 );  mat_set(A3,1,2, 1 );  mat_set(A3,1,3, 0 );
  mat_set(A3,2,1, 0 );  mat_set(A3,2,2, 0 );  mat_set(A3,2,3, 1 );
  mat_set(A3,3,1, 1 );  mat_set(A3,3,2, 0 );  mat_set(A3,3,3, 0 );
  printf("A3: ");  mat_print(A3);
  mat_eigval(A3,tol,iter);
  mat_clear(A3);

  // Fourth eigenvalue test
  matrix* A4 = mat_init(3,3);
  mat_set(A4,1,1, 0 );  mat_set(A4,1,2, 1 );  mat_set(A4,1,3, 0 );
  mat_set(A4,2,1, 0 );  mat_set(A4,2,2, 0 );  mat_set(A4,2,3, 1 );
  mat_set(A4,3,1,-4 );  mat_set(A4,3,2,-6 );  mat_set(A4,3,3, -4 );
  printf("A4: ");  mat_print(A4);
  mat_eigval(A4,tol,iter);
  mat_clear(A4);

  printf("\n");
  return;
}
*/




/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatEchelon
//  Debugs the MatEchelon file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MatEchelon() {
  printf("Reduced row echelon form of a matrix \n");

  int r = 4;
  int c = 7;
  matrix* X = mat_init(r,c);
  mat_set(X,1,1, 0);  mat_set(X,1,2, 0);  mat_set(X,1,3, 6);  mat_set(X,1,4, 0);  mat_set(X,1,5, 19);  mat_set(X,1,6, 11);  mat_set(X,1,7,-27);
  mat_set(X,2,1, 3);  mat_set(X,2,2,12);  mat_set(X,2,3, 9);  mat_set(X,2,4,-6);  mat_set(X,2,5, 26);  mat_set(X,2,6, 31);  mat_set(X,2,7,-63);
  mat_set(X,3,1, 1);  mat_set(X,3,2, 4);  mat_set(X,3,3, 3);  mat_set(X,3,4,-2);  mat_set(X,3,5, 10);  mat_set(X,3,6,  9);  mat_set(X,3,7,-17);
  mat_set(X,4,1,-1);  mat_set(X,4,2,-4);  mat_set(X,4,3,-4);  mat_set(X,4,4, 2);  mat_set(X,4,5,-13);  mat_set(X,4,6,-11);  mat_set(X,4,7, 22);
  printf("X: ");  mat_print(X);

  matrix* Y = mat_echelon(X);
  printf("Y: ");  mat_print(Y);
  
  mat_clear(X);
  mat_clear(Y);

  printf("\n");
  return;
}
*/



/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatSS
//  Debugs the MatSS file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MatSS() {
  printf("Matrix state space \n");

  // Define system dimensions
  int n = 3;
  int m = 1;

  // Declare state matrix
  matrix* A = mat_init(n,n);
  mat_set(A,1,1, 0.0 );  mat_set(A,1,2, 1.0 );  mat_set(A,1,3, 0.0 );
  mat_set(A,2,1, 0.0 );  mat_set(A,2,2, 0.0 );  mat_set(A,2,3, 1.0 );
  mat_set(A,3,1, 7.0 );  mat_set(A,3,2, 8.0 );  mat_set(A,3,3, 9.0 );
  printf("A: ");  mat_print(A);

  // Declare input matrix
  matrix* B = mat_init(n,m);
  mat_set(B,1,1, 0.0 );
  mat_set(B,2,1, 0.0 );
  mat_set(B,3,1, 5.0 );
  printf("B: ");  mat_print(B);

  // Declare output matrix
  matrix* C = mat_init(m,n);
  mat_set(C,1,1, 1.0 );  mat_set(C,1,2, 2.0 );  mat_set(C,1,3, 3.0 );
  printf("C: ");  mat_print(C);

  // Controllability and observability
  matrix* ctrb = mat_ctrb(A,B);  
  printf("Ctrb: ");  mat_print(ctrb);
  matrix* obsv = mat_obsv(A,C);
  printf("Obsv: ");  mat_print(obsv);

  // Ctrl canonical transformation
  matrix* Tc = NULL;
  matrix* Ac = NULL;
  mat_Tctrl (A,B,&Tc,&Ac);

  //mat_print(mat_inv(Ac));

  // Linearization
  printf("Linearization \n");
  double d = 0.001;

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
  matrix* Alin = mat_init(4,4);
  matrix* Blin = mat_init(4,2);

  // First linearization
  printf("\nPlant1 linearization \n");
  mat_lin( Plant1, x, u, &Alin, &Blin, d );
  printf("Alin: ");  mat_print(Alin);
  printf("Blin: ");  mat_print(Blin);

  // Second linearization
  printf("\nPlant2 linearization \n");
  mat_lin( Plant2, x, u, &Alin, &Blin, d );
  printf("Alin: ");  mat_print(Alin);
  printf("Blin: ");  mat_print(Blin);

  // Clear matrices
  mat_clear(A);
  mat_clear(B);
  mat_clear(C);
  mat_clear(ctrb);
  mat_clear(obsv);
  //mat_clear(Ac);
  //mat_clear(Bc);
  //mat_clear(Tcc);
  //mat_clear(Acc);
  //mat_clear(Alin);
  //mat_clear(Blin);

  printf("\n");
  return;
}
*/



/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Plant1
//  Provides a nonlinear plant model for testing.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* Plant1 ( matrix* x, matrix* u ) {

  // Initialize derivative
  matrix* dx = mat_init(4,1);

  // Collect states
  double x1 = mat_get(x,1,1);
  double x2 = mat_get(x,2,1);
  double x3 = mat_get(x,3,1);
  double x4 = mat_get(x,4,1);

  // Collect inputs
  double u1 = mat_get(u,1,1);
  double u2 = mat_get(u,2,1);

  double dx1 = x3;
  double dx2 = x4;
  double dx3 = -2*x1 -3*x3 + 4*u1;
  double dx4 = -4*x2 -5*x4 + u2;

  mat_set( dx,1,1,dx1 );
  mat_set( dx,2,1,dx2 );
  mat_set( dx,3,1,dx3 );
  mat_set( dx,4,1,dx4 );

  return dx;
}
*/




/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Plant2
//  Provides a nonlinear plant model for testing.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* Plant2 ( matrix* x, matrix* u ) {

  // Initialize derivative
  matrix* dx = mat_init(4,1);

  // Collect states
  double x1 = mat_get(x,1,1);
  double x2 = mat_get(x,2,1);
  double x3 = mat_get(x,3,1);
  double x4 = mat_get(x,4,1);

  // Collect inputs
  double u1 = mat_get(u,1,1);
  double u2 = mat_get(u,2,1);

  double dx1 = x1*x2 -x1*x3 + 2*x1 - 3*x2 + x4 + 4*u1;
  double dx2 = pow(x1,2) - pow(x2,2) + 3*x1*x2 + x2*x3 + - x2*x4 + 2*u2 - u1;
  double dx3 = pow(x3,2) + 2*x1*x3 - 4*x2*x3 + x1*x2 + x1*x4 - 3*u2;
  double dx4 = 3*x1 - 2*x3 + pow(x4,2) + 2*u1 - u2;

  mat_set( dx,1,1,dx1 );
  mat_set( dx,2,1,dx2 );
  mat_set( dx,3,1,dx3 );
  mat_set( dx,4,1,dx4 );

  return dx;
}
*/



