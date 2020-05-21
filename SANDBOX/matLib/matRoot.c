// /*******************************************************************************
// *
// * Justin M Selfridge, PhD
// * Gradient Consulting, LLC
// * jselfridge@gmail.com
// *
// * matRoot.c
// * Source code to find the roots of a polynomial stored as a vector.
// *
// *******************************************************************************/
// #include "../inc/matRoot.h"




// /*******************************************************************************
// * Local internal function declarations.
// *******************************************************************************/
// double          B  ( matrix*  coef );
// void            Z  ( matrixz* zero, double b );
// void            L  ( matrixz* zero, matrix* coef, double tol, uint max );
// double complex  N  ( matrixz* zero, matrix* coef, uint j );
// double complex  D  ( matrixz* zero, uint j );




// /*******************************************************************************
// * matrixz* mat_root ( matrix* poly, double tol, uint max )
// * Returns complex roots of a polynomial using Durand-Kerner method.
// *******************************************************************************/
// matrixz* mat_root ( matrix* poly, double tol, uint max ) {

//   mat_err( ( poly->r != 1 ), "Error (mat_root): Polynomial must be a row vector." );

//   matrix*  coef = mat_init(  poly->c,   1 );
//   matrixz* zero = mat_initz( poly->c-1, 1 );

//   double m = *(poly->e);
//   if( m != 1.0 )  poly = mat_scale( poly, 1.0/m );

//   for( uint i=0; i<poly->c; i++ ) {
//     uint j = poly->c - 1 - i;
//     *(coef->e+j) = *(poly->e+i);
//   }

//   double b = B(coef);
//   Z( zero, b );
//   L( zero, coef, tol, max );

//   mat_clear(coef);

//   return zero;
// }




// /*******************************************************************************
// * Auxilliary function that bounds the coefficients.
// *******************************************************************************/
// double B ( matrix* coef ) {

//   double b = 0.0;
//   for( uint i=0; i<coef->r; i++ ) {
//     double val = fabs( *(coef->e+i) );
//     if( val > b )  b = val;
//   }

//   return b + 1.0;
// }




// /*******************************************************************************
// * Auxilliary function initializes values of the complex zeros.
// *******************************************************************************/
// void Z ( matrixz* zero, double b ) {

//   for( uint i=0; i<zero->r; i++ ) {
//     double ratio = (float)i / (float)zero->r;
//     *(zero->e+i) = cos( ratio * M_PI ) + sin( ratio * M_PI ) * b *I;
//   }

//   return;
// }




// /*******************************************************************************
// * Auxilliary function loops through the numerical routine.
// *******************************************************************************/
// void L ( matrixz* zero, matrix* coef, double tol, uint max ) {

//   for( uint k=0; k<max; k++ ) {
//     double qmax = 0.0;
//     for( uint j=0; j<zero->r; j++ ) {
// //      float complex n = ;
// //      float complex d = ;
//       double complex Q = - N( zero, coef, j ) / D( zero, j );
//       double q = cabs(Q);
//       double complex Z = *(zero->e+j);
//       Z += Q;
//       *(zero->e+j) = creal(Z) + cimag(Z) *I;
//       if( q > qmax )  qmax = q;
//     }
//     if( qmax <= tol )  return;
//   }

//   mat_err( (true), "Error (mat_root): Exceeded maximum iterations." );

//   return;
// }




// /*******************************************************************************
// * Auxilliary function generates the iterative numerator.
// *******************************************************************************/
// double complex N ( matrixz* zero, matrix* coef, uint j ) {

//   double complex n = *( coef->e + coef->r-1 );

//   for( uint i=0; i<zero->r; i++ ) {
//     n *= *(zero->e+j);
//     n += *( coef->e + zero->r-1 - i );
// //     float complex c = *( coef->e + zero->r-1 - i );
// //     float complex z = *( zero->e + j );
// //     n = z * n + c;
//   }

//   return n;
// }




// /*******************************************************************************
// * Auxilliary function generates the iterative denominator.
// *******************************************************************************/
// double complex D ( matrixz* zero, uint j ) {

//   double complex d = 1.0;

//   for( uint i=0; i<zero->r; i++ ) {
//     if( i != j )  d *= *(zero->e+j) - *(zero->e+i);
// //     float complex zi = *(zero->e+i);
// //     float complex zj = *(zero->e+j);
// //     if( i != j )  d *= zj - zi;
//   }

//   return d;
// }



