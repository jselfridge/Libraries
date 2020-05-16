/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matDemo.c
* Demo program for testing and debugging the 'matLib' library functions.
*
*******************************************************************************/
// #include <matLib.h>
#include <stdio.h>


// // Function prototypes
// void  MatInit     ( void );
// void  MatPrint    ( void );
// void  MatClear    ( void );
// void  MatManip    ( void );
// void  MatComplex  ( void );
// void  MatVec      ( void );
// void  MatArith    ( void );
// void  MatRoot     ( void );
// void  MatProp     ( void );
// void  MatDecomp   ( void );


// // Global variables
// matrix* M13;
// matrix* M14;
// matrix* M31a;
// matrix* M31b;
// matrix* M41;
// matrix* M22;
// matrix* M23;
// matrix* M32;
// matrix* M33a;
// matrix* M33b;
// matrix* M34;
// matrix* M43;
// matrix* M44;




/*******************************************************************************
* int main ( void )
* Runs the main matLib debugging program.
*******************************************************************************/
int main ( void ) {

  printf("\n   --- MatLib Debugging --- \n\n");
//   MatInit();
//   MatPrint();
  // MatManip();
  // MatComplex();
  // MatVec();
  // MatArith();
  // MatRoot();
  // MatProp();
//   MatDecomp();
//   MatClear();
  printf("   --- MatLib Complete --- \n\n");

  return 0;
}




// /*******************************************************************************
// * void MatInit ( void )
// * Initializes the debugging matrices.
// *******************************************************************************/
// void MatInit ( void ) {

//   // Define 1x3 vector
//   M13 = mat_init( 1, 3 );
//   mat_set( M13, 1, 1, -0.1 );
//   mat_set( M13, 1, 2,  4.6 );
//   mat_set( M13, 1, 3,  7.3 );

//   // Define 1x4 vector
//   M14 = mat_init( 1, 4 );
//   mat_set( M14, 1, 1, 2.6 );
//   mat_set( M14, 1, 2, 5.9 );
//   mat_set( M14, 1, 3, 3.7 );
//   mat_set( M14, 1, 4, 1.4 );

//   // Define first 3x1 vector
//   M31a = mat_init( 3, 1 );
//   mat_set( M31a, 1, 1, 6.0 );
//   mat_set( M31a, 2, 1, 2.1 );
//   mat_set( M31a, 3, 1, 0.3 );

//   // Define second 3x1 vector
//   M31b = mat_init( 3, 1 );
//   mat_set( M31b, 1, 1, -4.2 );
//   mat_set( M31b, 2, 1,  8.7 );
//   mat_set( M31b, 3, 1, -3.9 );

//   // Define 4x1 vector
//   M41 = mat_init( 4, 1 );
//   mat_set( M41, 1, 1, -2.2 );
//   mat_set( M41, 2, 1,  7.4 );
//   mat_set( M41, 3, 1, -9.1 );
//   mat_set( M41, 4, 1,  5.8 );

//   // Define 2x2 matrix
//   M22 = mat_init( 2, 2 );
//   mat_set( M22, 1, 1,  3.4 );  mat_set( M22, 1, 2, -5.3 );
//   mat_set( M22, 2, 1, -7.2 );  mat_set( M22, 2, 2,  9.2 );

//   // Define 2x3 matrix
//   M23 = mat_init( 2, 3 );
//   mat_set( M23, 1, 1, 6.6 );  mat_set( M23, 1, 2,  1.9 );  mat_set( M23, 1, 3, -0.4 );
//   mat_set( M23, 2, 1, 9.4 );  mat_set( M23, 2, 2, -7.1 );  mat_set( M23, 2, 3,  0.8 );

//   // Define 3x2 matrix
//   M32 = mat_init( 3, 2 );
//   mat_set( M32, 1, 1,  6.8 );  mat_set( M32, 1, 2, -0.1 );
//   mat_set( M32, 2, 1,  0.4 );  mat_set( M32, 2, 2,  5.4 );
//   mat_set( M32, 3, 1, -9.3 );  mat_set( M32, 3, 2,  4.2 );

//   // Define first 3x3 matrix
//   M33a = mat_init( 3, 3 );
//   mat_set( M33a, 1, 1,  3.4 );  mat_set( M33a, 1, 2,  0.5 );  mat_set( M33a, 1, 3,  8.2 );
//   mat_set( M33a, 2, 1,  7.7 );  mat_set( M33a, 2, 2, -9.3 );  mat_set( M33a, 2, 3, -4.6 );
//   mat_set( M33a, 3, 1, -1.8 );  mat_set( M33a, 3, 2,  0.2 );  mat_set( M33a, 3, 3, -2.9 );

//   // Define second 3x3 matrix
//   M33b = mat_init( 3, 3 );
//   mat_set( M33b, 1, 1,  3.4 );  mat_set( M33b, 1, 2, -1.9 );  mat_set( M33b, 1, 3,  0.2 );
//   mat_set( M33b, 2, 1,  0.5 );  mat_set( M33b, 2, 2, -0.8 );  mat_set( M33b, 2, 3,  6.3 );
//   mat_set( M33b, 3, 1, -7.2 );  mat_set( M33b, 3, 2,  4.5 );  mat_set( M33b, 3, 3, -9.5 );

//   // Define 3x4 matrix
//   M34 = mat_init( 3, 4 );
//   mat_set( M34, 1, 1, -3.3 );  mat_set( M34, 1, 2,  7.6 );  mat_set( M34, 1, 3, -0.6 );  mat_set( M34, 1, 4, -7.3 );
//   mat_set( M34, 2, 1,  0.5 );  mat_set( M34, 2, 2,  4.2 );  mat_set( M34, 2, 3,  3.2 );  mat_set( M34, 2, 4,  3.4 );
//   mat_set( M34, 3, 1,  1.6 );  mat_set( M34, 3, 2, -0.8 );  mat_set( M34, 3, 3,  5.8 );  mat_set( M34, 3, 4, -9.1 );

//   // Define 4x3 matrix
//   M43 = mat_init( 4, 3 );
//   mat_set( M43, 1, 1, -0.8 );  mat_set( M43, 1, 2, -1.2 );  mat_set( M43, 1, 3,  5.9 );
//   mat_set( M43, 2, 1,  1.2 );  mat_set( M43, 2, 2,  0.3 );  mat_set( M43, 2, 3, -6.4 );
//   mat_set( M43, 3, 1,  4.9 );  mat_set( M43, 3, 2,  7.4 );  mat_set( M43, 3, 3,  0.8 );
//   mat_set( M43, 4, 1, -8.3 );  mat_set( M43, 4, 2,  9.3 );  mat_set( M43, 4, 3, -1.8 );

//   // Define 4x4 matrix
//   M44 = mat_init( 4, 4 );
//   mat_set( M44, 1, 1,  3.1 );  mat_set( M44, 1, 2, -0.1 );  mat_set( M44, 1, 3, -2.7);  mat_set( M44, 1, 4,  7.2 );
//   mat_set( M44, 2, 1,  5.4 );  mat_set( M44, 2, 2,  8.2 );  mat_set( M44, 2, 3, -6.4);  mat_set( M44, 2, 4,  3.2 );
//   mat_set( M44, 3, 1,  0.7 );  mat_set( M44, 3, 2,  4.7 );  mat_set( M44, 3, 3,  9.9);  mat_set( M44, 3, 4, -9.3 );
//   mat_set( M44, 4, 1, -4.5 );  mat_set( M44, 4, 2, -8.1 );  mat_set( M44, 4, 3,  0.1);  mat_set( M44, 4, 4,  2.7 );

//   return;
// }




// /*******************************************************************************
// * void MatPrint ( void )
// * Prints the debugging matrices.
// *******************************************************************************/
// void MatPrint ( void ) {

//   printf("General purpose debugging matrices \n");
//   // mat_print(M13);
//   // mat_print(M14);
//   // mat_print(M31a);
//   // mat_print(M31b);
//   // mat_print(M41);
//   // mat_print(M22);
//   // mat_print(M23);
//   // mat_print(M32);
//   // mat_print(M33a);
//   // mat_print(M33b);
//   // mat_print(M34);
//   // mat_print(M43);
//   // mat_print(M44);
//   printf("\n");

//   return;
// }




// /*******************************************************************************
// * void MatClear ( void )
// * Clears the debugging matrices.
// *******************************************************************************/
// void MatClear ( void ) {

//   mat_clear(M13);
//   mat_clear(M14);
//   mat_clear(M31a);
//   mat_clear(M31b);
//   mat_clear(M41);
//   mat_clear(M22);
//   mat_clear(M23);
//   mat_clear(M32);
//   mat_clear(M33a);
//   mat_clear(M33b);
//   mat_clear(M34);
//   mat_clear(M43);
//   mat_clear(M44);

//   return;
// }




// /*******************************************************************************
// * void MatManip ( void )
// * Debugs the MatManip file functions.
// *******************************************************************************/
// void MatManip ( void ) {

//   printf("Matrix manipulation functions \n");

//   // File operations
//   matrix* A = mat_init( 5, 2 );
//   printf( "Rows: %d \n", A->rows );
//   printf( "Cols: %d \n", A->cols );
//   mat_set( A, 3, 1, 1.2 );
//   mat_set( A, 5, 2, 2.1 );
//   mat_set( A, 1, 2, 0.0000012345 );
//   mat_set( A, 5, 1, 1234560000.0 );
//   mat_print(A);
//   mat_write( A, "sample" );
//   matrix* B = mat_read("sample");
//   mat_print(B);

//   // Identity matrix
//   matrix* M = mat_eye(4);
//   mat_print(M);

//   // Scale matrix
//   mat_set( M, 4, 1, 0.1  );
//   mat_set( M, 1, 4, 10.0 );
//   matrix* N = mat_scale( M, 3.2 );
//   mat_print(N);

//   // Copy matrix
//   mat_set( N, 3, 2, 0.1  );
//   mat_set( N, 2, 3, 10.0 );
//   matrix* P = mat_copy(N);
//   mat_print(P);

//   // Ones matrix
//   matrix* Q = mat_ones( 5, 3 );
//   mat_print(Q);

//   // Get matrix row
//   mat_print( mat_getr( M22,  2 ) );
//   mat_print( mat_getr( M32,  1 ) );
//   mat_print( mat_getr( M33b, 3 ) );
//   mat_print( mat_getr( M44,  4 ) );

//   // Get matrix column
//   mat_print( mat_getc( M22,  2 ) );
//   mat_print( mat_getc( M32,  1 ) );
//   mat_print( mat_getc( M33b, 3 ) );
//   mat_print( mat_getc( M44,  4 ) );

//   // Set matrix row
//   mat_setr( M23, 2, M13 );
//   mat_print(M23);
//   mat_setr( M44, 1, M14 );
//   mat_print(M44);

//   // Set matrix column
//   mat_setc( M32, 2, M31a );
//   mat_print(M32);
//   mat_setc( M44, 1, M41 );
//   mat_print(M44);

//   // Swap Rows [2x2]
//   mat_print(M22);
//   mat_swapr( M22, 1, 2 );
//   mat_print(M22);
//   mat_swapr( M22, 2, 1 );
//   mat_print(M22);

//   // Swap rows [3x2]
//   mat_print(M32);
//   mat_swapr( M32, 2, 3 );
//   mat_print(M32);
//   mat_swapr( M32, 3, 2 );
//   mat_print(M32);

//   // Swap rows [4x4]
//   mat_print(M44);
//   mat_swapr( M44, 1, 3 );
//   mat_print(M44);
//   mat_swapr( M44, 2, 4 );
//   mat_print(M44);
//   mat_swapr( M44, 4, 2 );
//   mat_swapr( M44, 3, 1 );
//   mat_print(M44);

//   // Swap cols [2x3]
//   mat_print(M23);
//   mat_swapc( M23, 1, 3 );
//   mat_print(M23);
//   mat_swapc( M23, 3, 1 );
//   mat_print(M23);

//   // Swap col [4x3]
//   mat_print(M43);
//   mat_swapc( M43, 1, 1 );
//   mat_print(M43);
//   mat_swapc( M43, 3, 2 );
//   mat_print(M43);
//   mat_swapc( M43, 2, 3 );
//   mat_print(M43);

//   // Append rows
//   mat_print( mat_appr( M33a, M33b ) );
//   mat_print( mat_appr( M13,  M33a ) );
//   mat_print( mat_appr( M44,  M14  ) );

//   // Append columns
//   mat_print( mat_appc( M31b, M32  ) );
//   mat_print( mat_appc( M33a, M33b ) );
//   mat_print( mat_appc( M44,  M41  ) );

//   // Remove tiny entries
//   matrix* R = mat_init( 2, 2 );
//   mat_set( R, 1, 1, -0.1000 );  mat_set( R, 1, 2,  0.0100 );
//   mat_set( R, 2, 1,  0.0010 );  mat_set( R, 2, 2, -0.0001 );
//   mat_print(R);
//   mat_rmtiny( R, 1e-2 );
//   mat_print(R);

//   // Clear completed matrices
//   mat_clear(A);
//   mat_clear(B);
//   mat_clear(M);
//   mat_clear(N);
//   mat_clear(P);
//   mat_clear(Q);
//   mat_clear(R);

//   // Exit MatManip debugging
//   printf("\n");

//   return;
// }




// /*******************************************************************************
// * void MatComplex ( void )
// * Debugs the MatComplex file functions.
// *******************************************************************************/
// void MatComplex ( void ) {

//   printf("Matrix complex manipulation functions \n");

//   // Declare complex column vector
//   matrixz* Cz = mat_initz( 4, 1 );
//   mat_setz( Cz, 1, 1,  1.0,  2.0 );
//   mat_setz( Cz, 2, 1,  0.3, -4.0 );
//   mat_setz( Cz, 3, 1, -1.4,  0.6 );
//   mat_setz( Cz, 4, 1, -3.1, -2.7 );
//   mat_printz(Cz);

//   // Declare complex row vector
//   matrixz* Rz = mat_initz( 1, 2 );
//   mat_setz( Rz, 1, 1, 4.2,  1.5 );
//   mat_setz( Rz, 1, 2, 0.9, -3.7 );
//   mat_printz(Rz);

//   // Get element values
//   printf( "%f \n", mat_getre( Cz, 1, 1 ) );
//   printf( "%f \n", mat_getre( Cz, 3, 1 ) );
//   printf( "%f \n", mat_getim( Cz, 1, 1 ) );
//   printf( "%f \n", mat_getim( Cz, 4, 1 ) );
//   printf( "%f \n", mat_getre( Rz, 1, 2 ) );
//   printf( "%f \n", mat_getim( Rz, 1, 2 ) );

//   // Initialize complex matrix
//   matrixz* Mz = mat_initz( 4, 2 );
//   printf( "Rows: %d \n", Mz->rows );
//   printf( "Cols: %d \n", Mz->cols );

//   // Set and get columns and rows
//   mat_setrz( Mz, 1, Rz );
//   mat_setcz( Mz, 2, Cz );
//   mat_printz(Mz);
//   mat_printz( mat_getrz( Mz, 1 ) );
//   mat_printz( mat_getcz( Mz, 2 ) );

//   // Write and read complex matrix
//   mat_writez( Mz, "samplez" );
//   matrixz* Tz = mat_readz("samplez");
//   mat_printz(Tz);

//   // Clear complex matrices
//   mat_clearz(Cz); 
//   mat_clearz(Rz); 
//   mat_clearz(Mz);
//   mat_clearz(Tz);

//   // Exit MatComplex debugging
//   printf("\n");

//   return;
// }




// /*******************************************************************************
// * void MatVec ( void )
// * Debugs the MatVec file functions.
// *******************************************************************************/
// void MatVec ( void ) {

//   printf("Matrix vector functions \n");

//   // Skew symmetric
//   matrix* skew = mat_skew(M31a);
//   mat_print(skew);
//   mat_clear(skew);

//   // Double skew symmetric
//   matrix* sskew = mat_sskew(M31a);
//   mat_print(sskew);
//   mat_clear(sskew);

//   // Cross product
//   matrix* cross;
//   cross = mat_cross( M31a, M31b );
//   mat_print(cross);
//   cross = mat_cross( M31b, M31a );
//   mat_print(cross);
//   cross = mat_cross( M31b, M31b );
//   mat_print(cross);
//   mat_clear(cross);

//   // Dot product
//   float dot;
//   dot = mat_dot( M31a, M31b );
//   printf( "dot: %f \n", dot );
//   dot = mat_dot( M31b, M31a );
//   printf( "dot: %f \n", dot );
//   dot = mat_dot(  M41,  M41 );
//   printf( "dot: %f \n", dot );

//   // Magnitude
//   mat_print(M41);
//   printf( "Mag: %f \n", mat_mag(M41) );
//   matrix* unity = mat_init( 4, 1 );
//   mat_set( unity, 1, 1, 1.0 );
//   mat_set( unity, 2, 1, 0.0 );
//   mat_set( unity, 3, 1, 0.0 );
//   mat_set( unity, 4, 1, 0.0 );
//   printf( "Mag: %f \n", mat_mag(unity) );
//   mat_clear(unity);

//   // Norm
//   mat_print(M41);
//   double NI = mat_norm( M41, 0 );
//   double N1 = mat_norm( M41, 1 );
//   double N2 = mat_norm( M41, 2 );
//   double N3 = mat_norm( M41, 3 );
//   printf( "NormI: %f \n", NI );
//   printf( "Norm1: %f \n", N1 );
//   printf( "Norm2: %f \n", N2 );
//   printf( "Norm3: %f \n", N3 );

//   // Unit vector
//   printf("Unit vector: \n");
//   matrix* quat = mat_init( 4, 1 );
//   mat_set( quat, 1, 1, 3.0 );
//   mat_set( quat, 2, 1, 0.0 );
//   mat_set( quat, 3, 1, 0.0 );
//   mat_set( quat, 4, 1,-4.0 );
//   mat_print( mat_uvec(M31b) );
//   mat_print( mat_uvec(M41) );
//   mat_print( mat_uvec(quat) );
//   mat_clear(quat);

//   // Vector projection
//   printf("Vector projection: \n");
//   matrix* u = mat_init( 3, 1 );
//   mat_set( u, 1, 1,  7 );
//   mat_set( u, 2, 1, 14 );
//   mat_set( u, 3, 1,  4 );
//   printf("u: ");
//   mat_print(u);
//   matrix* v = mat_init( 3, 1 );
//   mat_set( v, 1, 1, -2 );
//   mat_set( v, 2, 1,  5 );
//   mat_set( v, 3, 1,  1 );
//   printf("v: ");
//   mat_print(v);
//   matrix* proj = mat_proj( u, v );
//   printf("proj: ");
//   mat_print(proj);
//   mat_clear(u);
//   mat_clear(v);
//   mat_clear(proj);

//   // Exit MatVec debugging
//   printf("\n");

//   return;
// }




// /*******************************************************************************
// * void MatArith ( void )
// * Debugs the MatArith file functions.
// *******************************************************************************/
// void MatArith ( void ) {

//   printf("Matrix arithmetic functions \n");

//   // Addition
//   matrix* Vadd = mat_add( M31a, M31b );
//   mat_print(Vadd);
//   mat_clear(Vadd);
//   matrix* Madd = mat_add( M33a, M33b );
//   mat_print(Madd);
//   mat_clear(Madd);

//   // Subtraction
//   matrix* Vsub = mat_sub( M31a, M31b );
//   mat_print(Vsub);
//   mat_clear(Vsub);
//   matrix* Msub = mat_sub( M33a, M33b );
//   mat_print(Msub);
//   mat_clear(Msub);

//   // Element-wise multiplication
//   matrix* Vemul = mat_emul( M31a, M31b );
//   mat_print(Vemul);
//   mat_clear(Vemul);
//   matrix* Memul = mat_emul( M33a, M33b );
//   mat_print(Memul);
//   mat_clear(Memul);

//   // Element-wise division
//   matrix* Vediv = mat_ediv( M31a, M31b );
//   mat_print(Vediv);
//   mat_clear(Vediv);
//   matrix* Mediv = mat_ediv( M33a, M33b );
//   mat_print(Mediv);
//   mat_clear(Mediv);

//   // Multiplication
//   matrix* Mmul33 = mat_mul( M33a, M33b );
//   mat_print(Mmul33);
//   mat_clear(Mmul33);
//   matrix* Mmul23 = mat_mul( M23, M33a );
//   mat_print(Mmul23);
//   mat_clear(Mmul23);
//   matrix* Mmul4 = mat_mul( M44, M41 );
//   mat_print(Mmul4);
//   mat_clear(Mmul4);

// //   // Left division
// //   matrix* XL  = mat_divL( M33a, M32 );
// //   matrix* AXL = mat_mul( M33a, XL );
// //   mat_print(M33a);  mat_print(M32);
// //   mat_print(XL);    mat_clear(XL);
// //   mat_print(AXL);   mat_clear(AXL);

// //   // Matrix inverse
// //   matrix* INV = mat_inv( M44 );
// //   matrix* MIM = mat_mul( INV, M44 );
// //   mat_print(INV);  mat_clear(INV);
// //   mat_print(MIM);  mat_clear(MIM);

// //   // Right division
// //   matrix* XR  = mat_divR( M44, M14 );
// //   matrix* XRA = mat_mul( XR, M44 );
// //   mat_print(M44);  mat_print(M14);
// //   mat_print(XR);   mat_clear(XR);
// //   mat_print(XRA);  mat_clear(XRA);

//   // Matrix element-wise power
//   matrix* Mepow;
//   for( ushort i=0; i<=4; i++ ) {
//     Mepow = mat_epow( M33a, i );
//     mat_print(Mepow);
//   }
//   mat_clear(Mepow);

//   // Matrix power
//   matrix* Mpow;
//   for( ushort i=0; i<=4; i++ ) {
//     Mpow = mat_pow( M33a, i );
//     mat_print(Mpow);
//   }
//   mat_clear(Mpow);

//   // Absolute value
//   mat_print(M32);
//   mat_print( mat_abs(M32) );
//   mat_print(M44);
//   mat_print( mat_abs(M44) );
//   mat_print(M41);
//   mat_print( mat_abs(M41) );

//   // Transpose
//   mat_print(M41);
//   mat_print( mat_trans(M41) );
//   mat_print(M14);
//   mat_print( mat_trans(M14) );
//   mat_print(M23);
//   mat_print( mat_trans(M23) );
//   mat_print(M32);
//   mat_print( mat_trans(M32) );
//   mat_print(M44);
//   mat_print( mat_trans(M44) );

//   // Reshape
//   mat_print(M41);
//   mat_print( mat_reshape( M41, 2, 2 ) );
//   mat_print(M14);
//   mat_print( mat_reshape( M14, 2, 2 ) );
//   mat_print(M23);
//   mat_print( mat_reshape( M23, 3, 2 ) );
//   mat_print(M44);
//   mat_print( mat_reshape( M44, 8, 2 ) );

//   // Exit MatArith degugging
//   printf("\n");

//   return;
// }




// /*******************************************************************************
// * void MatRoot ( void )
// * Debugs the MatRoot file functions.
// *******************************************************************************/
// void MatRoot ( void ) {

//   printf("Matrix polynomial root function \n");

//   // Routine values
//   float tol = 0.001;
//   uint max = 50000;

//   // First polynomial matrix
//   matrix* poly1 = mat_init( 1, 4 );
//   mat_set( poly1, 1, 1,  1 );
//   mat_set( poly1, 1, 2, 10 );
//   mat_set( poly1, 1, 3, 31 );
//   mat_set( poly1, 1, 4, 30 );
//   printf("poly1: ");
//   mat_print(poly1);
//   matrixz* zero1 = mat_root( poly1, tol, max );
//   printf("zero1: ");
//   mat_printz(zero1);

//   // Second polynomial matrix
//   matrix* poly2 = mat_init( 1, 4 );
//   mat_set( poly2, 1, 1, 1 );
//   mat_set( poly2, 1, 2, 4 );
//   mat_set( poly2, 1, 3, 6 );
//   mat_set( poly2, 1, 4, 4 );
//   printf("poly2: ");
//   mat_print(poly2);
//   matrixz* zero2 = mat_root( poly2, tol, max );
//   printf("zero2: ");
//   mat_printz(zero2);

//   // Third polynomial matrix
//   matrix* poly3 = mat_init( 1, 4 );
//   mat_set( poly3, 1, 1,  -3 );
//   mat_set( poly3, 1, 2, -12 );
//   mat_set( poly3, 1, 3, -18 );
//   mat_set( poly3, 1, 4, -12 );
//   printf("poly3: ");
//   mat_print(poly3);
//   matrixz* zero3 = mat_root( poly3, tol, max );
//   printf("zero3: ");
//   mat_printz(zero3);

//   // Fourth polynomial matrix
//   matrix* poly4 = mat_init( 1, 6 );
//   mat_set( poly4, 1,  1,      1 );
//   mat_set( poly4, 1,  2,      6 );
//   mat_set( poly4, 1,  3,    -19 );
//   mat_set( poly4, 1,  4,   -132 );
//   mat_set( poly4, 1,  5,    115 );
//   mat_set( poly4, 1,  6,    434 );
//   //mat_set( poly4, 1,  7,  -4449 );
//   // mat_set( poly4, 1,  8,  -8932 );
//   // mat_set( poly4, 1,  9,  34484 );
//   // mat_set( poly4, 1, 10, 164720 );
//   // mat_set( poly4, 1, 11, 296748 );
//   // mat_set( poly4, 1, 12, 268704 );
//   // mat_set( poly4, 1, 13, 112320 );
//   printf("poly4: ");
//   mat_print(poly4);
//   matrixz* zero4 = mat_root( poly4, tol, max );
//   printf("zero4: ");
//   mat_printz(zero4);

//   // Clear matrices
//   mat_clear(poly1);
//   mat_clear(poly2);
//   mat_clear(poly3);
//   mat_clear(poly4);
//   mat_clearz(zero1);
//   mat_clearz(zero2);
//   mat_clearz(zero3);
//   mat_clearz(zero4);

//   // Exit MatRoot debugging
//   printf("\n");

//   return;
// }




// /*******************************************************************************
// * void MatProp ( void )
// * Debugs the MatProp file functions.
// *******************************************************************************/
// void MatProp ( void ) {

// //   printf("Matrix properties functions \n");

// // //   // Determinant
// // //   double det3 = mat_det(M33a);
// // //   printf( "det3: %f \n", det3 );
// // //   double det4 = mat_det(M44);
// // //   printf( "det4: %f \n", det4 );

// // //   // Trace of a matrix
// // //   double trace3 = mat_trace(M33a);
// // //   printf( "trace3: %f \n", trace3 );
// // //   double trace4 = mat_trace(M44);
// // //   printf( "trace4: %f \n", trace4 );

// // //   // Symmetric matrix
// // //   printf("Symmetric matrix \n");
// // //   matrix* sym;
// // //   bool issym;
// // //   double tol = 0.011;
// // //   sym = mat_init( 3, 3 );
// // //   mat_set( sym, 1, 1, 4.00 );  mat_set( sym, 1, 2, 0.30 );  mat_set( sym, 1, 3, 0.00 );
// // //   mat_set( sym, 2, 1, 0.30 );  mat_set( sym, 2, 2, 3.00 );  mat_set( sym, 2, 3, 0.00 );
// // //   mat_set( sym, 3, 1, 0.01 );  mat_set( sym, 3, 2, 0.00 );  mat_set( sym, 3, 3, 2.00 );
// // //   printf("Sym:");
// // //   mat_print(sym);
// // //   issym = mat_sym( sym, tol );
// // //   printf("Is the matrix symmetric?  ");  issym ? printf("yes\n") : printf("no\n");
// // //   printf("Sym:");
// // //   mat_print(sym);
// // //   mat_clear(sym);

// //   // Exit MatProp debugging
// //   printf("\n");

//   return;
// }




// /*******************************************************************************
// * void MatDecomp ( void )
// * Debugs the MatDecomp file functions.
// *******************************************************************************/
// void MatDecomp ( void ) {

//   printf("Matrix decomposition functions \n");

//   // LDU 1
//   printf("LDU 1: \n");
//   matrix* A1 = mat_init( 3, 3 );
//   mat_set( A1, 1, 1, -3 );  mat_set( A1, 1, 2, 1 );  mat_set( A1, 1, 3,  2 );  
//   mat_set( A1, 2, 1,  6 );  mat_set( A1, 2, 2, 2 );  mat_set( A1, 2, 3, -5 );  
//   mat_set( A1, 3, 1,  9 );  mat_set( A1, 3, 2, 5 );  mat_set( A1, 3, 3, -6 );  
//   matrix* L1 = mat_init( A1->rows, A1->rows );
//   matrix* U1 = mat_init( A1->rows, A1->cols );
//   mat_LU( A1, L1, U1 );
//   matrix* LU1 = mat_mul( L1, U1 );
//   printf("A1: ");    mat_print(A1);    mat_clear(A1);
//   printf("L1: ");    mat_print(L1);    mat_clear(L1);
//   printf("U1: ");    mat_print(U1);    mat_clear(U1);
//   printf("LU1: ");   mat_print(LU1);   mat_clear(LU1);

//   //mat_LU( A1, &L1, &U1 );
// // //   mat_LDU( A1, &L1, &D1, &V1 );
// // //   matrix* LDU1 = mat_mul( mat_mul( L1, D1 ), V1 );
// // //   printf("D1: ");    mat_print(D1);    mat_clear(D1);
// // //   printf("V1: ");    mat_print(V1);    mat_clear(V1);
// // //   printf("LDU1: ");  mat_print(LDU1);  mat_clear(LDU1);
//   printf("\n");

// // //   // LDU 2
// // //   printf("LDU 2: \n");
// // //   matrix* A2 = mat_init( 3, 3 );
// // //   mat_set( A2, 1, 1,  2 );  mat_set( A2, 1, 2,  8 );  mat_set( A2, 1, 3,   0 );  
// // //   mat_set( A2, 2, 1,  4 );  mat_set( A2, 2, 2, 18 );  mat_set( A2, 2, 3,  -4 );  
// // //   mat_set( A2, 3, 1, -2 );  mat_set( A2, 3, 2, -2 );  mat_set( A2, 3, 3, -13 );  
// // //   mat_LU( A2, &L2, &U2 );
// // //   LU2 = mat_mul( L2, U2 );
// // //   mat_LDU( A2, &L2, &D2, &V2 );
// // //   LDU2 = mat_mul( mat_mul( L2, D2 ), V2 );
// // //   printf("A2: ");    mat_print(A2);    mat_clear(A2);
// // //   printf("L2: ");    mat_print(L2);    mat_clear(L2);
// // //   printf("U2: ");    mat_print(U2);    mat_clear(U2);
// // //   printf("LU2: ");   mat_print(LU2);   mat_clear(LU2);
// // //   printf("D2: ");    mat_print(D2);    mat_clear(D2);
// // //   printf("V2: ");    mat_print(V2);    mat_clear(V2);
// // //   printf("LDU2: ");  mat_print(LDU2);  mat_clear(LDU2);
// // //   printf("\n");

// // //   // LDU 3
// // //   printf("LDU 3: \n");
// // //   matrix* A3 = mat_init( 4, 4 );
// // //   mat_set( A3, 1, 1,  2 );  mat_set( A3, 1, 2,  1 );  mat_set( A3, 1, 3,  0 );  mat_set( A3, 1, 4,   4 );  
// // //   mat_set( A3, 2, 1, -4 );  mat_set( A3, 2, 2, -3 );  mat_set( A3, 2, 3,  5 );  mat_set( A3, 2, 4, -10 );  
// // //   mat_set( A3, 3, 1,  6 );  mat_set( A3, 3, 2,  4 );  mat_set( A3, 3, 3, -8 );  mat_set( A3, 3, 4,  17 );  
// // //   mat_set( A3, 4, 1,  2 );  mat_set( A3, 4, 2, -3 );  mat_set( A3, 4, 3, 29 );  mat_set( A3, 4, 4,  -9 );  
// // //   mat_LU( A3, &L3, &U3 );
// // //   LU3 = mat_mul( L3, U3 );
// // //   mat_LDU( A3, &L3, &D3, &V3 );
// // //   LDU3 = mat_mul( mat_mul( L3, D3 ), V3 );
// // //   printf("A3: ");    mat_print(A3);    mat_clear(A3);
// // //   printf("L3: ");    mat_print(L3);    mat_clear(L3);
// // //   printf("U3: ");    mat_print(U3);    mat_clear(U3);
// // //   printf("LU3: ");   mat_print(LU3);   mat_clear(LU3);
// // //   printf("D3: ");    mat_print(D3);    mat_clear(D3);
// // //   printf("V3: ");    mat_print(V3);    mat_clear(V3);
// // //   printf("LDU3: ");  mat_print(LDU3);  mat_clear(LDU3);
// // //   printf("\n");

// // //   // LDU 4
// // //   printf("LDU 4: \n");
// // //   matrix* A4 = mat_init( 3, 5 );
// // //   mat_set( A4, 1, 1,   4 );  mat_set( A4, 1, 2,  -3 );  mat_set( A4, 1, 3,  -1 );  mat_set( A4, 1, 4,   5 );  mat_set( A4, 1, 5,  2 );
// // //   mat_set( A4, 2, 1, -16 );  mat_set( A4, 2, 2,  12 );  mat_set( A4, 2, 3,   2 );  mat_set( A4, 2, 4, -17 );  mat_set( A4, 2, 5, -7 );
// // //   mat_set( A4, 3, 1,   8 );  mat_set( A4, 3, 2,  -6 );  mat_set( A4, 3, 3, -12 );  mat_set( A4, 3, 4,  22 );  mat_set( A4, 3, 5, 10 );
// // //   mat_LU( A4, &L4, &U4 );
// // //   LU4 = mat_mul( L4, U4 );
// // //   mat_LDU( A4, &L4, &D4, &V4 );
// // //   LDU4 = mat_mul( mat_mul( L4, D4 ), V4 );
// // //   printf("A4: ");    mat_print(A4);    mat_clear(A4);
// // //   printf("L4: ");    mat_print(L4);    mat_clear(L4);
// // //   printf("U4: ");    mat_print(U4);    mat_clear(U4);
// // //   printf("LU4: ");   mat_print(LU4);   mat_clear(LU4);
// // //   printf("D4: ");    mat_print(D4);    mat_clear(D4);
// // //   printf("V4: ");    mat_print(V4);    mat_clear(V4);
// // //   printf("LDU4: ");  mat_print(LDU4);  mat_clear(LDU4);
// // //   printf("\n");

// // //   // LDU 5
// // //   printf("LDU 5: \n");
// // //   matrix* A5 = mat_init( 5, 3 );
// // //   mat_set( A5, 1, 1,  3 );  mat_set( A5, 1, 2, -1 );  mat_set( A5, 1, 3,  4 );
// // //   mat_set( A5, 2, 1,  9 );  mat_set( A5, 2, 2, -5 );  mat_set( A5, 2, 3, 15 );
// // //   mat_set( A5, 3, 1, 15 );  mat_set( A5, 3, 2, -1 );  mat_set( A5, 3, 3, 10 );
// // //   mat_set( A5, 4, 1, -6 );  mat_set( A5, 4, 2,  2 );  mat_set( A5, 4, 3, -4 );
// // //   mat_set( A5, 5, 1, -3 );  mat_set( A5, 5, 2, -3 );  mat_set( A5, 5, 3, 10 );
// // //   mat_LU( A5, &L5, &U5 );
// // //   LU5 = mat_mul( L5, U5 );
// // //   mat_LDU( A5, &L5, &D5, &V5 );
// // //   LDU5 = mat_mul( mat_mul( L5, D5 ), V5 );
// // //   printf("A5: ");    mat_print(A5);    mat_clear(A5);
// // //   printf("L5: ");    mat_print(L5);    mat_clear(L5);
// // //   printf("U5: ");    mat_print(U5);    mat_clear(U5);
// // //   printf("LU5: ");   mat_print(LU5);   mat_clear(LU5);
// // //   printf("D5: ");    mat_print(D5);    mat_clear(D5);
// // //   printf("V5: ");    mat_print(V5);    mat_clear(V5);
// // //   printf("LDU5: ");  mat_print(LDU5);  mat_clear(LDU5);
// // //   printf("\n");
// // //   /*
// // //   // LDU 6: No solution
// // //   printf("LDU 6: \n");
// // //   matrix* A6 = mat_init( 3, 3 );
// // //   mat_set( A6, 1, 1,  2 );  mat_set( A6, 1, 2,  1 );  mat_set( A6, 1, 3, -1 );
// // //   mat_set( A6, 2, 1, -4 );  mat_set( A6, 2, 2, -2 );  mat_set( A6, 2, 3,  5 );
// // //   mat_set( A6, 3, 1,  6 );  mat_set( A6, 3, 2,  2 );  mat_set( A6, 3, 3, 11 );
// // //   mat_LU( A6, &L6, &U6 );
// // //   */
// // //   // QR 1
// // //   printf("QR 1: \n");
// // //   matrix* a1 = mat_init( 3, 3 );
// // //   mat_set( a1, 1, 1, -3 );  mat_set( a1, 1, 2, 1 );  mat_set( a1, 1, 3,  2 );  
// // //   mat_set( a1, 2, 1,  6 );  mat_set( a1, 2, 2, 2 );  mat_set( a1, 2, 3, -5 );  
// // //   mat_set( a1, 3, 1,  9 );  mat_set( a1, 3, 2, 5 );  mat_set( a1, 3, 3, -6 );  
// // //   mat_QR( a1, &Q1, &R1 );
// // //   QR1  = mat_mul( Q1, R1 );
// // //   QTQ1 = mat_mul( mat_trans(Q1), Q1 );
// // //   printf("a1: ");    mat_print(a1);    mat_clear(a1);
// // //   printf("Q1: ");    mat_print(Q1);    mat_clear(Q1);
// // //   printf("R1: ");    mat_print(R1);    mat_clear(R1);
// // //   printf("QR1: ");   mat_print(QR1);   mat_clear(QR1);
// // //   printf("QTQ1: ");  mat_print(QTQ1);  mat_clear(QTQ1);
// // //   printf("\n");

// // //   // QR 2
// // //   printf("QR 2: \n");
// // //   matrix* a2 = mat_init( 3, 3 );
// // //   mat_set( a2, 1, 1,  2 );  mat_set( a2, 1, 2,  8 );  mat_set( a2, 1, 3,   0 );  
// // //   mat_set( a2, 2, 1,  4 );  mat_set( a2, 2, 2, 18 );  mat_set( a2, 2, 3,  -4 );  
// // //   mat_set( a2, 3, 1, -2 );  mat_set( a2, 3, 2, -2 );  mat_set( a2, 3, 3, -13 );  
// // //   mat_QR( a2, &Q2, &R2 );
// // //   QR2  = mat_mul( Q2, R2 );
// // //   QTQ2 = mat_mul( mat_trans(Q2), Q2 );
// // //   printf("a2: ");    mat_print(a2);    mat_clear(a2);
// // //   printf("Q2: ");    mat_print(Q2);    mat_clear(Q2);
// // //   printf("R2: ");    mat_print(R2);    mat_clear(R2);
// // //   printf("QR2: ");   mat_print(QR2);   mat_clear(QR2);
// // //   printf("QTQ2: ");  mat_print(QTQ2);  mat_clear(QTQ2);
// // //   printf("\n");

// // //   // QR 3
// // //   printf("QR 3: \n");
// // //   matrix* a3 = mat_init( 4, 4 );
// // //   mat_set( a3, 1, 1,  2 );  mat_set( a3, 1, 2,  1 );  mat_set( a3, 1, 3,  0 );  mat_set( a3, 1, 4,   4 );  
// // //   mat_set( a3, 2, 1, -4 );  mat_set( a3, 2, 2, -3 );  mat_set( a3, 2, 3,  5 );  mat_set( a3, 2, 4, -10 );  
// // //   mat_set( a3, 3, 1,  6 );  mat_set( a3, 3, 2,  4 );  mat_set( a3, 3, 3, -8 );  mat_set( a3, 3, 4,  17 );  
// // //   mat_set( a3, 4, 1,  2 );  mat_set( a3, 4, 2, -3 );  mat_set( a3, 4, 3, 29 );  mat_set( a3, 4, 4,  -9 );  
// // //   mat_QR( a3, &Q3, &R3 );
// // //   QR3  = mat_mul( Q3, R3 );
// // //   QTQ3 = mat_mul( mat_trans(Q3), Q3 );
// // //   printf("a3: ");    mat_print(a3);    mat_clear(a3);
// // //   printf("Q3: ");    mat_print(Q3);    mat_clear(Q3);
// // //   printf("R3: ");    mat_print(R3);    mat_clear(R3);
// // //   printf("QR3: ");   mat_print(QR3);   mat_clear(QR3);
// // //   printf("QTQ3: ");  mat_print(QTQ3);  mat_clear(QTQ3);
// // //   printf("\n");

// // //   printf("QR 4: \n");
// // //   matrix* a4 = mat_init( 5, 3 );
// // //   mat_set( a4, 1, 1,  3 );  mat_set( a4, 1, 2, -1 );  mat_set( a4, 1, 3,  4 );
// // //   mat_set( a4, 2, 1,  9 );  mat_set( a4, 2, 2, -5 );  mat_set( a4, 2, 3, 15 );
// // //   mat_set( a4, 3, 1, 15 );  mat_set( a4, 3, 2, -1 );  mat_set( a4, 3, 3, 10 );
// // //   mat_set( a4, 4, 1, -6 );  mat_set( a4, 4, 2,  2 );  mat_set( a4, 4, 3, -4 );
// // //   mat_set( a4, 5, 1, -3 );  mat_set( a4, 5, 2, -3 );  mat_set( a4, 5, 3, 10 );
// // //   mat_QR( a4, &Q4, &R4 );
// // //   QR4  = mat_mul( Q4, R4 );
// // //   QTQ4 = mat_mul( mat_trans(Q4), Q4 );
// // //   printf("a4: ");    mat_print(a4);    mat_clear(a4);
// // //   printf("Q4: ");    mat_print(Q4);    mat_clear(Q4);
// // //   printf("R4: ");    mat_print(R4);    mat_clear(R4);
// // //   printf("QR4: ");   mat_print(QR4);   mat_clear(QR4);
// // //   printf("QTQ4: ");  mat_print(QTQ4);  mat_clear(QTQ4);
// // //   printf("\n");

// // //   /*
// // //   // QR 5
// // //   printf("QR 5: \n");
// // //   matrix* a5 = mat_init( 3, 5 );
// // //   mat_set( a5, 1, 1,   4 );  mat_set( a5, 1, 2,  -3 );  mat_set( a5, 1, 3,  -1 );  mat_set( a5, 1, 4,   5 );  mat_set( a5, 1, 5,  2 );
// // //   mat_set( a5, 2, 1, -16 );  mat_set( a5, 2, 2,  12 );  mat_set( a5, 2, 3,   2 );  mat_set( a5, 2, 4, -17 );  mat_set( a5, 2, 5, -7 );
// // //   mat_set( a5, 3, 1,   8 );  mat_set( a5, 3, 2,  -6 );  mat_set( a5, 3, 3, -12 );  mat_set( a5, 3, 4,  22 );  mat_set( a5, 3, 5, 10 );
// // //   mat_QR( a5, &Q5, &R5 );
// // //   QR5  = mat_mul( Q5, R5 );
// // //   QTQ5 = mat_mul( mat_trans(Q5), Q5 );
// // //   printf("a5: ");    mat_print(a5);    mat_clear(a5);
// // //   printf("Q5: ");    mat_print(Q5);    mat_clear(Q5);
// // //   printf("R5: ");    mat_print(R5);    mat_clear(R5);
// // //   printf("QR5: ");   mat_print(QR5);   mat_clear(QR5);
// // //   printf("QTQ5: ");  mat_print(QTQ5);  mat_clear(QTQ5);
// // //   printf("\n");
// // //   */
// // //   /*
// // //   // Triangle to vector
// // //   printf("Triangle to vector: \n");
// // //   matrix* tri1 = mat_init( 3, 3 );
// // //   mat_set( tri1, 1, 1, 1.00 );  mat_set( tri1, 1, 2, 0.00 );  mat_set( tri1, 1, 3, 0.00 );
// // //   mat_set( tri1, 2, 1, 0.20 );  mat_set( tri1, 2, 2, 0.03 );  mat_set( tri1, 2, 3, 0.00 );
// // //   mat_set( tri1, 3, 1, 4.00 );  mat_set( tri1, 3, 2, 0.50 );  mat_set( tri1, 3, 3, 0.06 );
// // //   vec1 = mat_tri2vec(tri1);
// // //   printf("Tri:");  mat_print(tri1);  mat_clear(tri1);
// // //   printf("Vec:");  mat_print(vec1);  mat_clear(vec1);

// // //   // Vector to triangle
// // //   printf("Vector to triangle: \n");
// // //   matrix* vec2 = mat_init( 6, 1 );
// // //   mat_set( vec2, 1, 1, 0.01 );
// // //   mat_set( vec2, 2, 1, 0.20 );
// // //   mat_set( vec2, 3, 1, 3.00 );
// // //   mat_set( vec2, 4, 1, 0.04 );
// // //   mat_set( vec2, 5, 1, 0.50 );
// // //   mat_set( vec2, 6, 1, 6.00 );
// // //   tri2 = mat_vec2tri(vec2);
// // //   printf("Vec:");  mat_print(vec2);  mat_clear(vec2);
// // //   printf("Tri:");  mat_print(tri2);  mat_clear(tri2);
// // //   */
// // //   /*
// // //   // Symmetric PSD1
// // //   printf("Matrix Inverse 1: \n");
// // //   matrix *PSD1, *PSD1i, *I3;
// // //   double a[6], c[6], w[6];
// // //   uint nullity, ifault;
// // //   PSD1  = mat_init( 3, 3 );
// // //   PSD1i = mat_init( 3, 3 );
// // //   I3    = mat_init( 3, 3 );
// // //   mat_set( PSD1, 1, 1, 4 );  mat_set( PSD1, 1, 2, 0 );  mat_set( PSD1, 1, 3, 1 );
// // //   mat_set( PSD1, 2, 1, 0 );  mat_set( PSD1, 2, 2, 2 );  mat_set( PSD1, 2, 3, 1 );
// // //   mat_set( PSD1, 3, 1, 1 );  mat_set( PSD1, 3, 2, 1 );  mat_set( PSD1, 3, 3, 2 );
// // //   a[0] = mat_get( PSD1, 1, 1 );
// // //   a[1] = mat_get( PSD1, 2, 1 );
// // //   a[2] = mat_get( PSD1, 2, 2 );
// // //   a[3] = mat_get( PSD1, 3, 1 );
// // //   a[4] = mat_get( PSD1, 3, 2 );
// // //   a[5] = mat_get( PSD1, 3, 3 );
// // //   mat_syminv( a, 3, c, w, &nullity, &ifault );
// // //   mat_set( PSD1i, 1, 1, c[0] );  mat_set( PSD1i, 1, 2, c[1] );  mat_set( PSD1i, 1, 3, c[3] );
// // //   mat_set( PSD1i, 2, 1, c[1] );  mat_set( PSD1i, 2, 2, c[2] );  mat_set( PSD1i, 2, 3, c[4] );
// // //   mat_set( PSD1i, 3, 1, c[3] );  mat_set( PSD1i, 3, 2, c[4] );  mat_set( PSD1i, 3, 3, c[5] );
// // //   I3 = mat_mul( PSD1i, PSD1 );
// // //   printf("PSD1:");   mat_print(PSD1);   mat_clear(PSD1);
// // //   printf("PSD1i:");  mat_print(PSD1i);  mat_clear(PSD1i);
// // //   printf("I3");      mat_print(I3);     mat_clear(I3);
// // //   */

//   // Exit MatDecomp debugging
//   printf("\n");

//   return;
// }



