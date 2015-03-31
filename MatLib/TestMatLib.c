
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  TestMatLib.c
//  Justin M Selfridge
//  Script to test the MatLib Library
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


// Function prototypes
void InitMat();
void MatIO();
void MatManip();
void MatArith();
void MatProp();
void MatDecomp();
void ClearMat();


// Global variables
matrix* V3a;
matrix* V3b;
matrix* V4;
matrix* M22;
matrix* M23;
matrix* M32;
matrix* M33a;
matrix* M33b;
matrix* M34;
matrix* M43;
matrix* M44;




// Main program 
int main() {
  printf("\nRunning Matlib demo \n\n\n");
  InitMat();
  MatIO();
  MatManip();
  MatArith();
  MatProp();
  MatDecomp();
  ClearMat();
  printf("Program complete\n\n");
  return 0 ;
}




// InitMat (initialize the matrices for demo)
void InitMat() {

  //  Define first 3x1 vector
  V3a = mat_init(3,1);
  mat_set(V3a,1,1,6);
  mat_set(V3a,2,1,2);
  mat_set(V3a,3,1,9);

  //  Define second 3x1 vector
  V3b = mat_init(3,1);
  mat_set(V3b,1,1,4);
  mat_set(V3b,2,1,8);
  mat_set(V3b,3,1,3);
  
  //  Define 4x1 vector
  V4 = mat_init(4,1);
  mat_set(V4,1,1,5);
  mat_set(V4,2,1,2);
  mat_set(V4,3,1,7);
  mat_set(V4,4,1,1);
  
  //  Define 2x2 matrix
  M22 = mat_init(2,2);
  mat_set(M22,1,1,3);  mat_set(M22,1,2,5);
  mat_set(M22,2,1,7);  mat_set(M22,2,2,9);

  //  Define 2x3 matrix
  M23 = mat_init(2,3);
  mat_set(M23,1,1,6);  mat_set(M23,1,2,1);  mat_set(M23,1,3,2);
  mat_set(M23,2,1,9);  mat_set(M23,2,2,7);  mat_set(M23,2,3,4);

  //  Define 3x2 matrix
  M32 = mat_init(3,2);
  mat_set(M32,1,1,6);  mat_set(M32,1,2,7);
  mat_set(M32,2,1,2);  mat_set(M32,2,2,5);
  mat_set(M32,3,1,9);  mat_set(M32,3,2,4);
  
  // Define first 3x3 matrix
  M33a = mat_init(3,3);
  mat_set(M33a,1,1,3);  mat_set(M33a,1,2,5);  mat_set(M33a,1,3,8);
  mat_set(M33a,2,1,7);  mat_set(M33a,2,2,9);  mat_set(M33a,2,3,4);
  mat_set(M33a,3,1,1);  mat_set(M33a,3,2,6);  mat_set(M33a,3,3,2);

  // Define second 3x3 matrix
  M33b = mat_init(3,3);
  mat_set(M33b,1,1,3);  mat_set(M33b,1,2,1);  mat_set(M33b,1,3,2);
  mat_set(M33b,2,1,5);  mat_set(M33b,2,2,8);  mat_set(M33b,2,3,6);
  mat_set(M33b,3,1,7);  mat_set(M33b,3,2,4);  mat_set(M33b,3,3,9);

  // Define 3x4 matrix
  M34 = mat_init(3,4);
  mat_set(M34,1,1,3);  mat_set(M34,1,2,7);  mat_set(M34,1,3,6);  mat_set(M34,1,4,7);
  mat_set(M34,2,1,5);  mat_set(M34,2,2,4);  mat_set(M34,2,3,2);  mat_set(M34,2,4,3);
  mat_set(M34,3,1,1);  mat_set(M34,3,2,8);  mat_set(M34,3,3,5);  mat_set(M34,3,4,9);

  // Define 4x3 matrix
  M43 = mat_init(4,3);
  mat_set(M43,1,1,8);  mat_set(M43,1,2,1);  mat_set(M43,1,3,5);
  mat_set(M43,2,1,2);  mat_set(M43,2,2,3);  mat_set(M43,2,3,6);
  mat_set(M43,3,1,4);  mat_set(M43,3,2,7);  mat_set(M43,3,3,8);
  mat_set(M43,4,1,8);  mat_set(M43,4,2,9);  mat_set(M43,4,3,1);

  // Define 4x4 matrix
  M44 = mat_init(4,4);
  mat_set(M44,1,1,3);  mat_set(M44,1,2,1);  mat_set(M44,1,3,2);  mat_set(M44,1,4,7);
  mat_set(M44,2,1,5);  mat_set(M44,2,2,8);  mat_set(M44,2,3,6);  mat_set(M44,2,4,3);
  mat_set(M44,3,1,7);  mat_set(M44,3,2,4);  mat_set(M44,3,3,9);  mat_set(M44,3,4,9);
  mat_set(M44,4,1,4);  mat_set(M44,4,2,8);  mat_set(M44,4,3,1);  mat_set(M44,4,4,2);

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
  mat_write(M,"matM");
  matrix* N = mat_read("matM");
  mat_print(N);
  mat_clear(M); 
  mat_clear(N);
  printf("\n\n");
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

  // Clear completed matrices 
  mat_clear(M); 
  mat_clear(N); 
  mat_clear(P); 
  mat_clear(Q);

  printf("\n\n");
}




// Matrix Arithmetic
void MatArith() {
  printf("Matrix Arithmetic \n");

  // Display matrices
  mat_print(V3a);
  mat_print(V3b);
  mat_print(M33a);
  mat_print(M33b);

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
  for ( int i=0; i<=2; i++ ) {
    Mpow= mat_pow(M33a,i);
    mat_print(Mpow);
  }
  mat_clear(Mpow);

  //  Transpose
  matrix* T1 = mat_trans(V4);
  mat_print(T1);  mat_clear(T1);
  matrix* T2 = mat_trans(M23);
  mat_print(T2);  mat_clear(T2);
  matrix* T3 = mat_trans(M43);
  mat_print(T3);  mat_clear(T3);
  matrix* T4 = mat_trans(M33a);
  mat_print(T4);  mat_clear(T4);

  //  Skew Symmetric
  matrix* skew = mat_skew(V3a);
  mat_print(skew);  mat_clear(skew);
  
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

  printf("\n\n");
}




// Matrix Properties
void MatProp() {
  printf("Matrix properties \n");

  // Trace
  double T33 = mat_trace(M33a);  printf( "Trace of M33a: %f \n", T33 );
  double T34 = mat_trace(M34);   printf( "Trace of M34:  %f \n", T34 );
  double T43 = mat_trace(M43);   printf( "Trace of M43:  %f \n", T43 );

  printf("\n\n");
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

  printf("\n\n");
}



