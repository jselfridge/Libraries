
//============================================================
//  matDebug.c
//  Justin M Selfridge
//============================================================
#include "matDebug.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  main
//  Runs the main MatLib debugging program.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main ()  {
  printf("\n   --- MatLib Debugging --- \n\n");
  InitMat(); 
  PrintMat();
  MatManip();
  MatComplex();
  MatVec();
  MatArith();
  MatRoot();
  ClearMat();
  printf("   --- MatLib Complete --- \n\n");
  return 0;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  InitMat
//  Initializes the debugging matrices.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void InitMat ()  {

  // Define 1x3 vector
  M13 = mat_init(1,3);
  mat_set(M13,1,1,-0.1);
  mat_set(M13,1,2,4.6);
  mat_set(M13,1,3,7.3);

  // Define 1x4 vector
  M14 = mat_init(1,4);
  mat_set(M14,1,1,2.6);
  mat_set(M14,1,2,5.9);
  mat_set(M14,1,3,3.7);
  mat_set(M14,1,4,1.4);

  // Define first 3x1 vector
  M31a = mat_init(3,1);
  mat_set(M31a,1,1,6.0);
  mat_set(M31a,2,1,2.1);
  mat_set(M31a,3,1,0.3);

  // Define second 3x1 vector
  M31b = mat_init(3,1);
  mat_set(M31b,1,1,-4.2);
  mat_set(M31b,2,1, 8.7);
  mat_set(M31b,3,1,-3.9);
  
  // Define 4x1 vector
  M41 = mat_init(4,1);
  mat_set(M41,1,1,-2.2);
  mat_set(M41,2,1, 7.4);
  mat_set(M41,3,1,-9.1);
  mat_set(M41,4,1, 5.8);
  
  // Define 2x2 matrix
  M22 = mat_init(2,2);
  mat_set(M22,1,1, 3.4);  mat_set(M22,1,2,-5.3);
  mat_set(M22,2,1,-7.2);  mat_set(M22,2,2, 9.2);

  // Define 2x3 matrix
  M23 = mat_init(2,3);
  mat_set(M23,1,1,6.6);  mat_set(M23,1,2, 1.9);  mat_set(M23,1,3,-0.4);
  mat_set(M23,2,1,9.4);  mat_set(M23,2,2,-7.1);  mat_set(M23,2,3, 0.8);

  // Define 3x2 matrix
  M32 = mat_init(3,2);
  mat_set(M32,1,1, 6.8);  mat_set(M32,1,2,-0.1);
  mat_set(M32,2,1, 0.4);  mat_set(M32,2,2, 5.4);
  mat_set(M32,3,1,-9.3);  mat_set(M32,3,2, 4.2);
  
  // Define first 3x3 matrix
  M33a = mat_init(3,3);
  mat_set(M33a,1,1,3.4);  mat_set(M33a,1,2,0.5);  mat_set(M33a,1,3,8.2);
  mat_set(M33a,2,1,7.7);  mat_set(M33a,2,2,-9.3);  mat_set(M33a,2,3,-4.6);
  mat_set(M33a,3,1,-1.8);  mat_set(M33a,3,2,0.2);  mat_set(M33a,3,3,-2.9);

  // Define second 3x3 matrix
  M33b = mat_init(3,3);
  mat_set(M33b,1,1, 3.4);  mat_set(M33b,1,2,-1.9);  mat_set(M33b,1,3, 0.2);
  mat_set(M33b,2,1, 0.5);  mat_set(M33b,2,2,-0.8);  mat_set(M33b,2,3, 6.3);
  mat_set(M33b,3,1,-7.2);  mat_set(M33b,3,2, 4.5);  mat_set(M33b,3,3,-9.5);

  // Define 3x4 matrix
  M34 = mat_init(3,4);
  mat_set(M34,1,1,-3.3);  mat_set(M34,1,2, 7.6);  mat_set(M34,1,3,-0.6);  mat_set(M34,1,4,-7.3);
  mat_set(M34,2,1, 0.5);  mat_set(M34,2,2, 4.2);  mat_set(M34,2,3, 3.2);  mat_set(M34,2,4, 3.4);
  mat_set(M34,3,1, 1.6);  mat_set(M34,3,2,-0.8);  mat_set(M34,3,3, 5.8);  mat_set(M34,3,4,-9.1);

  // Define 4x3 matrix
  M43 = mat_init(4,3);
  mat_set(M43,1,1,-0.8);  mat_set(M43,1,2,-1.2);  mat_set(M43,1,3, 5.9);
  mat_set(M43,2,1, 1.2);  mat_set(M43,2,2, 0.3);  mat_set(M43,2,3,-6.4);
  mat_set(M43,3,1, 4.9);  mat_set(M43,3,2, 7.4);  mat_set(M43,3,3, 0.8);
  mat_set(M43,4,1,-8.3);  mat_set(M43,4,2, 9.3);  mat_set(M43,4,3,-1.8);

  // Define 4x4 matrix
  M44 = mat_init(4,4);
  mat_set(M44,1,1, 3.1);  mat_set(M44,1,2,-0.1);  mat_set(M44,1,3,-2.7);  mat_set(M44,1,4, 7.2);
  mat_set(M44,2,1, 5.4);  mat_set(M44,2,2, 8.2);  mat_set(M44,2,3,-6.4);  mat_set(M44,2,4, 3.2);
  mat_set(M44,3,1, 0.7);  mat_set(M44,3,2, 4.7);  mat_set(M44,3,3, 9.9);  mat_set(M44,3,4,-9.3);
  mat_set(M44,4,1,-4.5);  mat_set(M44,4,2,-8.1);  mat_set(M44,4,3, 0.1);  mat_set(M44,4,4, 2.7);

  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  PrintMat
//  Prints the debugging matrices.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void PrintMat ()  {
  printf("General purpose debugging matrices \n");
  mat_print(M13);
  mat_print(M14);
  mat_print(M31a);
  mat_print(M31b);
  mat_print(M41);
  mat_print(M22);
  mat_print(M23);
  mat_print(M32);
  mat_print(M33a);
  mat_print(M33b);
  mat_print(M34);
  mat_print(M43);
  mat_print(M44);
  printf("\n");
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ClearMat
//  Clears the debugging matrices.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ClearMat ()  {
  mat_clear(M13);
  mat_clear(M14);
  mat_clear(M31a);
  mat_clear(M31b);
  mat_clear(M41);
  mat_clear(M22);
  mat_clear(M23);
  mat_clear(M32);
  mat_clear(M33a);
  mat_clear(M33b);
  mat_clear(M34);
  mat_clear(M43);
  mat_clear(M44);
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatManip
//  Debugs the MatManip file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MatManip ()  {
  printf("Matrix manipulation \n");

  // File operations
  matrix* A = mat_init(5,2);
  printf("Rows: %d \n", A->rows );
  printf("Cols: %d \n", A->cols );
  mat_print(A);
  mat_write(A,"test");
  matrix* B = mat_read("test");
  mat_print(B);
  mat_clear(A); 
  mat_clear(B);

  // Identity matrix
  matrix* M = mat_eye(4);
  mat_print(M);

  // Scale matrix
  matrix* N = mat_scale(M,3);
  mat_print(N);

  // Copy matrix
  matrix* P = mat_copy(N);
  mat_print(P);

  // Set element values
  mat_set( P,1,4, 14.0 );
  mat_set( P,3,2, 32.0 );
  mat_print(P);

  // Get element values
  double val;
  val = mat_get(P,1,4);
  printf( "Element value: %f\n", val );
  val = mat_get(P,3,2);
  printf( "Element value: %f\n", val );

  // Ones matrix
  matrix* Q = mat_ones(5,2);
  mat_print(Q);

  // Get matrix row
  mat_print( mat_getr(M22,2) );
  mat_print( mat_getr(M32,1) );
  mat_print( mat_getr(M33b,3) );
  mat_print( mat_getr(M44,4) );

  // Get matrix column
  mat_print( mat_getc(M22,2) );
  mat_print( mat_getc(M32,1) );
  mat_print( mat_getc(M33b,3) );
  mat_print( mat_getc(M44,4) );

  // Set matrix row
  mat_setr(M23,2,M13);
  mat_print(M23);
  mat_setr(M44,1,M14);
  mat_print(M44);

  // Set matrix column
  mat_setc(M32,2,M31a);
  mat_print(M32);
  mat_setc(M44,1,M41);
  mat_print(M44);

  // Swap Rows [2x2]
  mat_print(M22);
  mat_swapr(M22,1,2);
  mat_print(M22);
  mat_swapr(M22,2,1);

  // Swap rows [3x2]
  mat_print(M32);
  mat_swapr(M32,2,3);
  mat_print(M32);
  mat_swapr(M32,3,2);

  // Swap rows [4x4]
  mat_print(M44);
  mat_swapr(M44,1,3);
  mat_print(M44);
  mat_swapr(M44,2,4);
  mat_print(M44);
  mat_swapr(M44,4,2);
  mat_swapr(M44,3,1);

  // Swap cols [2x3]
  mat_print(M23);
  mat_swapc(M23,1,3);
  mat_print(M23);
  mat_swapc(M23,3,1);

  // Swap col [4x3]
  mat_print(M43);
  mat_swapc(M43,1,1);
  mat_print(M43);
  mat_swapc(M43,3,2);
  mat_print(M43);
  mat_swapc(M43,2,3);

  // Append rows
  mat_print( mat_appr(M33a,M33b) );
  mat_print( mat_appr(M13,M33a) );
  mat_print( mat_appr(M44,M14) );

  // Append columns
  mat_print( mat_appc(M33a,M33b) );
  mat_print( mat_appc(M44,M41) );

  // Remove tiny
  matrix* R = mat_init(2,2);
  mat_set(R,1,1, -0.1000 );  mat_set(R,1,2,  0.0100 );
  mat_set(R,2,1,  0.0010 );  mat_set(R,2,2, -0.0001 );
  mat_print(R);
  mat_rmtiny(&R,0.0020);
  mat_print(R);

  // Clear completed matrices 
  mat_clear(M);
  mat_clear(N);
  mat_clear(P);
  mat_clear(Q);
  mat_clear(R);

  printf("\n");
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatComplex
//  Debugs the MatComplex file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MatComplex() {
  printf("Complex matrix manipulation \n");

  // Declare complex column vector
  matrixz* Cz = mat_initz(4,1);
  mat_setz( Cz,1,1,  1.0,  2.0 );
  mat_setz( Cz,2,1,  0.3, -4.0 );
  mat_setz( Cz,3,1, -1.4,  0.6 );
  mat_setz( Cz,4,1, -3.1, -2.7 );
  mat_printz(Cz);

  // Declare complex row vector
  matrixz* Rz = mat_initz(1,2);
  mat_setz( Rz,1,1,  4.2,  1.5 );
  mat_setz( Rz,1,2,  0.9, -3.7 );
  mat_printz(Rz);

  // Get element values
  printf("%f \n", mat_getre(Cz,1,1) );
  printf("%f \n", mat_getre(Cz,3,1) );
  printf("%f \n", mat_getim(Cz,1,1) );
  printf("%f \n", mat_getim(Cz,4,1) );
  printf("%f \n", mat_getre(Rz,1,2) );
  printf("%f \n", mat_getim(Rz,1,2) );

  // Initialize complex matrix
  matrixz* Mz = mat_initz(4,2);
  printf("Rows: %d \n", Mz->rows );
  printf("Cols: %d \n", Mz->cols );

  // Set and get columns and rows
  mat_setzr( Mz,1,Rz );
  mat_setzc( Mz,2,Cz );
  mat_printz(Mz);
  mat_printz(mat_getzr(Mz,1));
  mat_printz(mat_getzc(Mz,2));

  // Write and read complex matrix
  mat_writez(Mz,"testz");
  matrixz* Tz = mat_readz("testz");
  mat_printz(Tz);

  // Clear complex matrices
  mat_clearz(Cz); 
  mat_clearz(Rz); 
  mat_clearz(Mz);
  mat_clearz(Tz);

  printf("\n");
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatVec
//  Debugs the MatVec file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MatVec() {
  printf("Matrix vector operations \n");

  //  Skew symmetric
  matrix* skew = mat_skew(M31a);
  mat_print(skew);  mat_clear(skew);

  //  Double skew symmetric
  matrix* sskew = mat_sskew(M31a);
  mat_print(sskew);  mat_clear(sskew);

  //  Cross product
  matrix* cross;
  cross = mat_cross(M31a,M31b);
  mat_print(cross);
  cross = mat_cross(M31a,M31a);
  mat_print(cross);  
  mat_clear(cross);

  //  Dot product
  double dot;
  dot = mat_dot(M31a,M31b);
  printf("dot: %f \n", dot);
  dot = mat_dot(M31a,M31a);
  printf("dot: %f \n", dot);

  // Norm
  mat_print(M41);
  double NI = mat_norm(M41,0);
  double N1 = mat_norm(M41,1);
  double N2 = mat_norm(M41,2);
  double N3 = mat_norm(M41,3);
  printf("NormI: %f \n", NI);
  printf("Norm1: %f \n", N1);
  printf("Norm2: %f \n", N2);
  printf("Norm3: %f \n", N3);

  // Magnitude
  printf("Mag: %f \n", mat_mag(M31a));
  matrix* unity = mat_init(4,1);
  mat_set(unity,1,1,1);
  mat_set(unity,2,1,0);
  mat_set(unity,3,1,1);
  mat_set(unity,4,1,0);
  printf("Mag: %f \n", mat_mag(unity));

  // Unit vector
  printf("Unit vector: ");
  matrix* quat = mat_init(4,1);
  mat_set(quat,1,1,1);
  mat_set(quat,2,1,0);
  mat_set(quat,3,1,1);
  mat_set(quat,4,1,0);
  mat_print(mat_uvec(M31b));
  mat_print(mat_uvec(M41));
  mat_print(mat_uvec(quat));

  // Vector projection
  matrix* u = mat_init(3,1);
  mat_set(u,1,1,7);
  mat_set(u,2,1,14);
  mat_set(u,3,1,4);
  printf("u: ");
  mat_print(u);
  matrix* v = mat_init(3,1);
  mat_set(v,1,1,-2);
  mat_set(v,2,1,5);
  mat_set(v,3,1,1);
  printf("v: ");
  mat_print(v);
  matrix* proj = mat_proj(u,v);
  printf("proj: ");
  mat_print(proj);
  mat_clear(u);
  mat_clear(v);
  mat_clear(proj);

  printf("\n");
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatArith
//  Debugs the MatArith file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MatArith() {
  printf("Matrix arithmetic functions \n");

  // Addition
  matrix* Vadd = mat_add(M31a,M31b);
  mat_print(Vadd);  mat_clear(Vadd);
  matrix* Madd = mat_add(M33a,M33b);
  mat_print(Madd);  mat_clear(Madd);

  // Subtraction
  matrix* Vsub = mat_sub(M31a,M31b);
  mat_print(Vsub);  mat_clear(Vsub);
  matrix* Msub = mat_sub(M33a,M33b);
  mat_print(Msub);  mat_clear(Msub);

  // Multiplication
  matrix* Mmul33 = mat_mul(M33a,M33b);
  mat_print(Mmul33);  mat_clear(Mmul33);
  matrix* Mmul23 = mat_mul(M23,M33a);
  mat_print(Mmul23);  mat_clear(Mmul23);
  matrix* Mmul4 = mat_mul(M44,M41);
  mat_print(Mmul4);  mat_clear(Mmul4);

  // Power
  int i;
  matrix* Mpow;
  for ( i=0; i<4; i++ ) {
    Mpow= mat_pow(M33a,i);
    mat_print(Mpow);
  }
  mat_clear(Mpow);

  // Absolute value
  mat_print( mat_abs(M32) );
  mat_print( mat_abs(M44) );
  mat_print( mat_abs(M41) );

  //  Transpose
  matrix* T1 = mat_trans(M41);
  mat_print(T1);  mat_clear(T1);
  matrix* T2 = mat_trans(M23);
  mat_print(T2);  mat_clear(T2);
  matrix* T3 = mat_trans(M43);
  mat_print(T3);  mat_clear(T3);
  matrix* T4 = mat_trans(M33a);
  mat_print(T4);  mat_clear(T4);

  printf("\n");
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatRoot
//  Debugs the MatRoot file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void MatRoot() {
  printf("Matrix root \n");

  // Routine values
  double tol = 0.000002;
  int max = 50000;

  // First polynomial matrix
  matrix* poly1 = mat_init(1,4);
  mat_set(poly1,1,1,  1 );
  mat_set(poly1,1,2, 10 );
  mat_set(poly1,1,3, 31 );
  mat_set(poly1,1,4, 30 );
  printf("poly1: ");  mat_print(poly1);
  matrixz* zero1 = mat_root(poly1,tol,max);
  printf("zero1: ");  mat_printz(zero1);

  // Second polynomial matrix
  matrix* poly2 = mat_init(1,4);
  mat_set(poly2,1,1, 1 );
  mat_set(poly2,1,2, 4 );
  mat_set(poly2,1,3, 6 );
  mat_set(poly2,1,4, 4 );
  printf("poly2: ");  mat_print(poly2);
  matrixz* zero2 = mat_root(poly2,tol,max);
  printf("zero2: ");  mat_printz(zero2);

  // Third polynomial matrix
  matrix* poly3 = mat_init(1,4);
  mat_set(poly3,1,1,  -3 );
  mat_set(poly3,1,2, -12 );
  mat_set(poly3,1,3, -18 );
  mat_set(poly3,1,4, -12 );
  printf("poly3: ");  mat_print(poly3);
  matrixz* zero3 = mat_root(poly3,tol,max);
  printf("zero3: ");  mat_printz(zero3);

  // Fourth polynomial matrix
  matrix* poly4 = mat_init(1,13);
  mat_set(poly4,1, 1,       1 );
  mat_set(poly4,1, 2,       6 );
  mat_set(poly4,1, 3,     -19 );
  mat_set(poly4,1, 4,    -132 );
  mat_set(poly4,1, 5,     115 );
  mat_set(poly4,1, 6,     434 );
  mat_set(poly4,1, 7,   -4449 );
  mat_set(poly4,1, 8,   -8932 );
  mat_set(poly4,1, 9,   34484 );
  mat_set(poly4,1,10,  164720 );
  mat_set(poly4,1,11,  296748 );
  mat_set(poly4,1,12,  268704 );
  mat_set(poly4,1,13,  112320 );
  printf("poly4: ");  mat_print(poly4);
  matrixz* zero4 = mat_root(poly4,tol,max);
  printf("zero4: ");  mat_printz(zero4);

  // Clear matrices
  mat_clear(poly1);
  mat_clear(poly2);
  mat_clear(poly3);
  mat_clear(poly4);
  mat_clearz(zero1);
  mat_clearz(zero2);
  mat_clearz(zero3);
  mat_clearz(zero4);

  printf("\n");
  return;
}



