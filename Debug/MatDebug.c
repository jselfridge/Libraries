
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatDebug.c
//  Justin M Selfridge
//  Script to debug the MatLib Library
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatDebug.h"




// Debugging function 
void DebugMatLib() {
  printf("\n   --- MatLib Debugging --- \n\n");
  InitMat(); 
  PrintMat();  
  //MatIO();
  //MatManip();
  //MatVec();
  //MatArith();
  MatProp();
  //MatDecomp();
  ClearMat();
  printf("   --- MatLib Complete --- \n\n");
  return;
}




// InitMat (initialize the matrices)
void InitMat() {

  //  Define first 3x1 vector
  V3a = mat_init(3,1);
  mat_set(V3a,1,1,6.0);
  mat_set(V3a,2,1,2.1);
  mat_set(V3a,3,1,0.3);

  //  Define second 3x1 vector
  V3b = mat_init(3,1);
  mat_set(V3b,1,1,-4.2);
  mat_set(V3b,2,1, 8.7);
  mat_set(V3b,3,1,-3.9);
  
  //  Define 4x1 vector
  V4 = mat_init(4,1);
  mat_set(V4,1,1,-2.2);
  mat_set(V4,2,1, 7.4);
  mat_set(V4,3,1,-9.1);
  mat_set(V4,4,1, 5.8);
  
  //  Define 2x2 matrix
  M22 = mat_init(2,2);
  mat_set(M22,1,1, 3.4);  mat_set(M22,1,2,-5.3);
  mat_set(M22,2,1,-7.2);  mat_set(M22,2,2, 9.2);

  //  Define 2x3 matrix
  M23 = mat_init(2,3);
  mat_set(M23,1,1,6.6);  mat_set(M23,1,2, 1.9);  mat_set(M23,1,3,-0.4);
  mat_set(M23,2,1,9.4);  mat_set(M23,2,2,-7.1);  mat_set(M23,2,3, 0.8);

  //  Define 3x2 matrix
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

}




// ClearMat (clear the matrices used in demo)
void PrintMat() {
  printf("General purpose matrices \n");
  mat_print(V3a);
  mat_print(V3b);
  mat_print(V4);
  mat_print(M22);
  mat_print(M23);
  mat_print(M32);
  mat_print(M33a);
  mat_print(M33b);
  mat_print(M34);
  mat_print(M43);
  mat_print(M44);
  printf("\n");
}




// ClearMat (clear the matrices used in demo)
void ClearMat() {
  mat_clear(V3a);
  mat_clear(V3b);
  mat_clear(V4);
  mat_clear(M22);
  mat_clear(M23);
  mat_clear(M32);
  mat_clear(M33a);
  mat_clear(M33b);
  mat_clear(M34);
  mat_clear(M43);
  mat_clear(M44);
}




// Matrix Input and Output
void MatIO() {
  printf("Matrix input and output \n");
  matrix* M = mat_init(5,2);
  mat_print(M);
  mat_write(M,"test");
  matrix* N = mat_read("test");
  mat_print(N);
  mat_clear(M); 
  mat_clear(N);
  printf("\n");
}




// Matrix Manipulation
void MatManip() {
  printf("Matrix manipulation \n");

  // Identity matrix
  matrix* M = mat_eye(4);
  mat_print(M);

  // Scale matrix
  matrix* N = mat_scale(M,3);
  mat_print(N);

  // Copy matrix
  matrix* P = mat_copy(N);
  mat_print(P);

  // Set element value
  mat_set(P,1,4,14.0);
  mat_set(P,3,2,32.0);
  mat_print(P);

  // Get element value
  double val;
  val = mat_get(P,1,4);
  printf( "Element value: %f\n", val );
  val = mat_get(P,3,2);
  printf( "Element value: %f\n", val );

  // Get matrix row
  mat_print(mat_getr(M22,2));
  mat_print(mat_getr(M32,1));
  mat_print(mat_getr(M33b,3));
  mat_print(mat_getr(M44,4));

  // Get matrix row
  mat_print(mat_getc(M22,2));
  mat_print(mat_getc(M32,1));
  mat_print(mat_getc(M33b,3));
  mat_print(mat_getc(M44,4));

  // Set matrix row
  mat_setr(M23,1,mat_trans(V3a));  mat_print(M23);
  mat_setr(M44,4,mat_trans(V4));   mat_print(M44);

  // Set matrix column
  mat_setc(M32,2,V3a);  mat_print(M32);
  mat_setc(M44,4,V4);   mat_print(M44);

  // Ones matrix
  matrix* Q = mat_ones(5,2);
  mat_print(Q);

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
  mat_swapc(M43,3,2);
  mat_print(M43);
  mat_swapc(M43,3,2);

  // Append rows
  mat_print( mat_appr(M33a,M33b) );
  mat_print( mat_appr(mat_trans(V3a),M33a) );
  mat_print( mat_appr(M44,mat_trans(V4)) );

  // Append columns
  mat_print( mat_appc(mat_trans(M32),M22) );
  mat_print( mat_appc(M33a,M33b) );
  mat_print( mat_appc(M44,V4) );

  // Remove tiny
  matrix* R = mat_init(2,2);
  mat_set(R,1,1, 0.1000 );  mat_set(R,1,2, 0.0100 );
  mat_set(R,2,1, 0.0010 );  mat_set(R,2,2, 0.0001 );
  mat_print(R);
  R = mat_rmtiny(R,0.0020);
  mat_print(R);

  // Clear completed matrices 
  mat_clear(M); 
  mat_clear(N); 
  mat_clear(P); 
  mat_clear(Q);
  mat_clear(R);

  printf("\n");
}




// Matrix Vector
void MatVec() {
  printf("Matrix Vector Operations \n");

  //  Skew Symmetric
  matrix* skew = mat_skew(V3a);
  mat_print(skew);  mat_clear(skew);

  //  Double Skew Symmetric
  matrix* sskew = mat_sskew(V3a);
  mat_print(sskew);  mat_clear(sskew);

  //  Cross product
  matrix* cross;
  cross = mat_cross(V3a,V3b);
  mat_print(cross);
  cross = mat_cross(V3a,V3a);
  mat_print(cross);  
  mat_clear(cross);

  //  Dot product
  double dot;
  dot = mat_dot(V3a,V3b);
  printf("dot: %f \n", dot);
  dot = mat_dot(V3a,V3a);
  printf("dot: %f \n", dot);

  // Norm
  mat_print(V4);
  double NI = mat_norm(V4,0);
  double N1 = mat_norm(V4,1);
  double N2 = mat_norm(V4,2);
  double N3 = mat_norm(V4,3);
  printf("NormI: %f \n", NI);
  printf("Norm1: %f \n", N1);
  printf("Norm2: %f \n", N2);
  printf("Norm3: %f \n", N3);

  // Magnitude
  printf("Mag: %f \n", mat_mag(V3a));
  matrix* unity = mat_init(4,1);
  mat_set(unity,1,1,1);
  mat_set(unity,2,1,1);
  mat_set(unity,3,1,0);
  mat_set(unity,4,1,0);
  printf("Mag: %f \n", mat_mag(unity));

  // Unit vector
  printf("Unit vector: ");
  matrix* quat = mat_init(4,1);
  mat_set(quat,1,1,1);
  mat_set(quat,2,1,0);
  mat_set(quat,3,1,1);
  mat_set(quat,4,1,0);
  mat_print(mat_uvec(V3b));
  mat_print(mat_uvec(V4));
  mat_print(mat_uvec(quat));

  // Projection
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
}




// Matrix Arithmetic
void MatArith() {
  printf("Matrix Arithmetic \n");

  //  Addition
  matrix* Vadd = mat_add(V3a,V3b);
  mat_print(Vadd);  mat_clear(Vadd);
  matrix* Madd = mat_add(M33a,M33b);
  mat_print(Madd);  mat_clear(Madd);

  //  Subtraction
  matrix* Vsub = mat_sub(V3a,V3b);
  mat_print(Vsub);  mat_clear(Vsub);
  matrix* Msub = mat_sub(M33a,M33b);
  mat_print(Msub);  mat_clear(Msub);

  //  Multiplication
  matrix* Mmul33 = mat_mul(M33a,M33b);
  mat_print(Mmul33);  mat_clear(Mmul33);
  matrix* Mmul23 = mat_mul(M23,M33a);
  mat_print(Mmul23);  mat_clear(Mmul23);
  matrix* Mmul4 = mat_mul(M44,V4);
  mat_print(Mmul4);  mat_clear(Mmul4);

  //  Power
  matrix* Mpow;
  for ( int i=0; i<4; i++ ) {
    Mpow= mat_pow(M33a,i);
    mat_print(Mpow);
  }
  mat_clear(Mpow);

  // Absolute value
  mat_print( mat_abs(M32) );
  mat_print( mat_abs(M44) );
  mat_print( mat_abs(mat_trans(V4)) );

  //  Transpose
  matrix* T1 = mat_trans(V4);
  mat_print(T1);  mat_clear(T1);
  matrix* T2 = mat_trans(M23);
  mat_print(T2);  mat_clear(T2);
  matrix* T3 = mat_trans(M43);
  mat_print(T3);  mat_clear(T3);
  matrix* T4 = mat_trans(M33a);
  mat_print(T4);  mat_clear(T4);

  printf("\n");
}




// Matrix Properties
void MatProp() {
  printf("Matrix properties \n");
  /*
  // Trace
  double T33 = mat_trace(M33a);  printf( "Trace of M33a: %f \n", T33 );
  double T34 = mat_trace(M34);   printf( "Trace of M34:  %f \n", T34 );
  double T43 = mat_trace(M43);   printf( "Trace of M43:  %f \n", T43 );

  // Rank
  int rank = mat_rank(M44);
  printf( "Rank: %d \n", rank );
  */

  // Test eigenvalues
  double tol  = 0.0000001;
  int    iter = 10;
  /*
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
  */
  // Third eigenvalue test
  matrix* A3 = mat_init(3,3);
  mat_set(A3,1,1, 0 );  mat_set(A3,1,2, 1 );  mat_set(A3,1,3, 0 );
  mat_set(A3,2,1, 0 );  mat_set(A3,2,2, 0 );  mat_set(A3,2,3, 1 );
  mat_set(A3,3,1, 1 );  mat_set(A3,3,2, 0 );  mat_set(A3,3,3, 0 );
  printf("A3: ");  mat_print(A3);
  mat_eigval(A3,tol,iter);
  mat_clear(A3);
  /*
  // Fourth eigenvalue test
  matrix* A4 = mat_init(3,3);
  mat_set(A4,1,1, 0 );  mat_set(A4,1,2, 1 );  mat_set(A4,1,3, 0 );
  mat_set(A4,2,1, 0 );  mat_set(A4,2,2, 0 );  mat_set(A4,2,3, 1 );
  mat_set(A4,3,1,-4 );  mat_set(A4,3,2,-6 );  mat_set(A4,3,3, -4 );
  printf("A4: ");  mat_print(A4);
  mat_eigval(A4,tol,iter);
  mat_clear(A4);
*/



  printf("\n");
}




// Matrix Decomposition
void MatDecomp() {
  printf("Matrix decomposition \n");

  // LU decomposition [3x3]
  matrix* L3 = NULL;
  matrix* U3 = NULL;
  mat_LU( M33a, &L3, &U3 );
  mat_print(L3);
  mat_print(U3);
  matrix* LU3 = mat_mul( L3, U3 );
  mat_print(LU3);
  mat_clear(LU3);
  mat_clear(L3);
  mat_clear(U3);

  // LU decomposition [4x4]
  matrix* L4 = NULL;
  matrix* U4 = NULL;
  mat_LU( M44, &L4, &U4 );
  mat_print(L4);
  mat_print(U4);
  matrix* LU4 = mat_mul( L4, U4 );
  mat_print(LU4);
  mat_clear(LU4);
  mat_clear(L4);
  mat_clear(U4);

  // QR Decomposition
  matrix* Q = NULL;
  matrix* R = NULL;
  matrix* A = mat_init(4,4);
  mat_set(A,1,1,1);  mat_set(A,1,2,0);  mat_set(A,1,3,-3);  mat_set(A,1,4,0);
  mat_set(A,2,1,0);  mat_set(A,2,2,2);  mat_set(A,2,3,-1);  mat_set(A,2,4,1);
  mat_set(A,3,1,1);  mat_set(A,3,2,0);  mat_set(A,3,3, 1);  mat_set(A,3,4,3);
  mat_set(A,4,1,1);  mat_set(A,4,2,3);  mat_set(A,4,3, 5);  mat_set(A,4,4,2);
  printf("A: ");  mat_print(A);
  mat_QR( A, &Q, &R );
  printf("Q: ");   mat_print(Q);
  printf("R: ");   mat_print(R);
  printf("QR: ");  mat_print(mat_mul(Q,R));
  mat_clear(A);
  mat_clear(Q);
  mat_clear(R);

  // Determinant
  double det3 = mat_det(M33a);
  printf( "det3: %f \n", det3 );
  double det4 = mat_det(M44);
  printf( "det4: %f \n", det4 );

  // Matrix inverse
  matrix* Minv3 = mat_inv(M33a);
  mat_print(Minv3);
  mat_print( mat_mul( Minv3, M33a ) );
  mat_print( mat_mul( M33a, Minv3 ) );
  mat_clear(Minv3);
  matrix* Minv4 = mat_inv(M44);
  mat_print(Minv4);
  mat_clear(Minv4);

  // Left division
  matrix* xL31 = mat_divL( M33a, V3a );
  mat_print(xL31);
  mat_print( mat_mul(M33a,xL31) );
  mat_clear(xL31);
  matrix* xL32 = mat_divL( M33a, M32 );
  mat_print(xL32);
  mat_print( mat_mul(M33a,xL32) );
  mat_clear(xL32);
  matrix* xL41 = mat_divL( M44, V4 );
  mat_print(xL41);
  mat_print( mat_mul(M44,xL41) );
  mat_clear(xL41);

  // Right division
  matrix* xR33 = mat_divR( M33b, M33a );
  mat_print(xR33);
  mat_print( mat_mul(xR33,M33a) );
  mat_clear(xR33);
  matrix* xR23 = mat_divR( M23, M33a );
  mat_print(xR23);
  mat_print( mat_mul(xR23,M33a) );
  mat_clear(xR23);
  matrix* xR14 = mat_divR( mat_trans(V4), M44 );
  mat_print(xR14);
  mat_print( mat_mul(xR14,M44) );
  mat_clear(xR14);

  printf("\n");
}



