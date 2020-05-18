/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* rotDemo.c
* Demo program for testing and debugging the 'rotLib' library functions.
*
*******************************************************************************/
#include <stdio.h>
#include "../inc/rotLib.h"


// Function prototypes
void  RotConv  ( void );
void  RotEul   ( void );
void  RotQuat  ( void );




/*******************************************************************************
* int main ( void )
* Runs the main rotLib debugging program.
*******************************************************************************/
int main ( void ) {

  printf("\n   --- RotLib Debugging --- \n\n");
  RotConv();
  RotEul();
  RotQuat();
  printf("   --- RotLib Complete --- \n\n");

  return 0;
}




/*******************************************************************************
* void RotConv ( void )
* Debugs the 'rotConv' file functions.
*******************************************************************************/
void RotConv ( void ) {
/*
  printf("Rotation conversions \n");

  matrix* deg  = mat_init( 1, 1 );
  matrix* rad  = mat_init( 1, 1 );
  matrix* degv = mat_init( 1, 4 );
  matrix* radv = mat_init( 1, 4 );

  // Degree to radian
  mat_set( deg, 1, 1, 0.0 );
  mat_print( rot_d2r(deg) );
  mat_set( deg, 1, 1, 90.0 );
  mat_print( rot_d2r(deg) );
  mat_set( deg, 1, 1, 60.0 );
  mat_print( rot_d2r(deg) );
  mat_set( degv, 1, 1, 360.0 );
  mat_set( degv, 1, 2, 180.0 );
  mat_set( degv, 1, 3, 45.0  );
  mat_set( degv, 1, 4, 22.5  );
  mat_print( rot_d2r(degv) );

  // Radian to degree
  mat_set( rad, 1, 1, 0.0 );
  mat_print( rot_r2d(rad) );
  mat_set( rad, 1, 1, M_PI );
  mat_print( rot_r2d(rad) );
  mat_set( rad, 1, 1, 2.5 );
  mat_print( rot_r2d(rad) );
  mat_set( radv, 1, 1, M_PI * 2.0 );
  mat_set( radv, 1, 2, M_PI / 2.0 );
  mat_set( radv, 1, 3, M_PI / 4.0 );
  mat_set( radv, 1, 4, M_PI / 8.0 );
  mat_print( rot_r2d(radv) );

  // Wrap pi
  mat_set( radv, 1, 1, -3.5  );
  mat_set( radv, 1, 2, -M_PI );
  mat_set( radv, 1, 3, -2.5  );
  mat_set( radv, 1, 4,  0.0  );
  mat_print( rot_wrappi(radv) );
  mat_set( radv, 1, 1, 0.0  );
  mat_set( radv, 1, 2, 2.5  );
  mat_set( radv, 1, 3, M_PI );
  mat_set( radv, 1, 4, 3.5  );
  mat_print( rot_wrappi(radv) );

  // Wrap 2pi
  mat_set( radv, 1, 1, -7.0      );
  mat_set( radv, 1, 2, -M_PI*2.0 );
  mat_set( radv, 1, 3, -5.0      );
  mat_set( radv, 1, 4,  0.0      );
  mat_print( rot_wrap2pi(radv) );
  mat_set( radv, 1, 1, 0.0      );
  mat_set( radv, 1, 2, 5.0      );
  mat_set( radv, 1, 3, M_PI*2.0 );
  mat_set( radv, 1, 4, 7.0      );
  mat_print( rot_wrap2pi(radv) );

  // Clear matrices
  mat_clear(deg);
  mat_clear(rad);
  mat_clear(degv);
  mat_clear(radv);

  printf("\n");
*/
  return;
}




/*******************************************************************************
* void RotEul ( void )
* Debugs the 'rotEul' file functions.
*******************************************************************************/
void RotEul ( void ) {
/*
  printf("Euler type rotations \n");

  // Define matrices
  matrix* att = mat_init( 3, 1 );
  mat_set( att, 1, 1, 0.0 );
  mat_set( att, 2, 1, 0.0 );
  mat_set( att, 3, 1, 0.0 );

  // Rotation matrices
  mat_print( rot_xaxis(0.0) );
  mat_print( rot_yaxis(0.0) );
  mat_print( rot_zaxis(0.0) );

  // Euler rotation
  matrix* R = rot_eul(att);
  mat_print(R);
  matrix* Rt = mat_trans(R);
  mat_print(Rt);
  matrix* Ri = mat_inv(R);
  mat_print(Ri);

  // Clear matrices
  mat_clear(att);
  mat_clear(R);
  mat_clear(Rt);
  mat_clear(Ri);

  printf("\n");
*/
  return;
}




/*******************************************************************************
* void RotQuat ( void )
* Debugs the 'rotQuat' file functions.
*******************************************************************************/
void RotQuat ( void ) {
/*
  printf("Quaternion functions \n");

  // Euler to quaternion
  matrix* att = mat_init( 3, 1 );
  mat_set( att, 1, 1, 0.0 );
  mat_set( att, 2, 1, 0.0 );
  mat_set( att, 3, 1, 0.0 );
  matrix* quat = rot_e2q(att);
  mat_print(quat);

  // Quaternion to Euler
  matrix* eul = rot_q2e(quat);
  mat_print(eul);

  // Quaternion to DCM
  mat_print( rot_eul(att) );
  mat_print( rot_q2dcm(quat) );

  // Define sample vectors
  matrix* vecA = mat_init( 3, 1 );
  mat_set( vecA, 1, 1,  1.2 );
  mat_set( vecA, 2, 1, -2.5 );
  mat_set( vecA, 3, 1,  0.4 );
  printf("vecA: ");
  mat_print(vecA);
  matrix* vecB = mat_init( 3, 1 );
  mat_set( vecB, 1, 1, -3.4 );
  mat_set( vecB, 2, 1,  2.1 );
  mat_set( vecB, 3, 1,  4.7 );
  printf("vecB: ");
  mat_print(vecB);

  // Vectors to quaternion
  matrix* VQ = rot_vec2q( vecA, vecB );
  printf("VQ: ");
  mat_print(VQ);
  matrix* vecQ = mat_mul( rot_q2dcm(VQ), vecA );
  printf("vecQ: ");
  mat_print(vecQ);
  printf("unit vecB: ");
  mat_print( mat_uvec(vecB) );
  printf("unit vecQ: ");
  mat_print( mat_uvec(vecQ) );

  // Vectors to Euler
  matrix* VE = rot_vec2e( vecA, vecB );
  printf("VE: ");
  mat_print(VE);
  matrix* vecE = mat_mul( rot_eul(VE), vecA );
  printf("vecE: ");
  mat_print(vecE);
  printf("unit vecB: ");
  mat_print( mat_uvec(vecB) );
  printf("unit vecE: ");
  mat_print( mat_uvec(vecE) );

  // Quaternion skew matrix
  mat_print( rot_qskew(quat) );

  // Quaternion multiplication
  mat_print(quat);
  mat_print(VQ);
  mat_print( rot_qmul( quat, VQ ) );

  // Quaternion derivative
  mat_print( rot_qderiv(quat) );

  // Clear matrices
  mat_clear(att);
  mat_clear(quat);
  mat_clear(eul);
  mat_clear(vecA);
  mat_clear(vecB);
  mat_clear(vecQ);
  mat_clear(vecE);
  mat_clear(VQ);
  mat_clear(VE);

  printf("\n");
*/
  return;
}



