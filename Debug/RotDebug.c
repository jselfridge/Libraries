
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  RotDebug.c
//  Justin M Selfridge
//  Script to debug the RotLib Library
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "RotDebug.h"




// Debugging function 
void DebugRotLib() {
  printf("\n   --- RotLib Debugging --- \n\n");

  /*
  printf("PI2: %f \n", PI2 );
  printf("PI:  %f \n", PI  );
  printf("PIH: %f \n", PIH );
  printf("PIQ: %f \n", PIQ );
  printf("PIE: %f \n", PIE );
  printf("PIS: %f \n", PIS );
  */
  
  //RotConv();
  //RotEuler();

  /*
  InitMat(); 
  ClearMat();
  */

  // Euler to Quaternion
  matrix* quat = mat_init(4,1);
  matrix* att = mat_init(3,1);
  mat_set( att,1,1, PIE );
  mat_set( att,2,1, PIE );
  mat_set( att,3,1, PIE );
  quat = rot_e2q(att);
  mat_print(quat);

  printf("   --- RotLib Complete --- \n\n");
  return;
}




// RotConv (Rotation conversions)
void RotConv() {
  printf("Rotation Conversions \n");

  matrix* deg  = mat_init(1,1);
  matrix* rad  = mat_init(1,1);
  matrix* degv = mat_init(1,4);
  matrix* radv = mat_init(1,4);

  // Degree to radian
  mat_set(deg,1,1,0); 
  rad = rot_d2r(deg);
  mat_print(rad);
  mat_set(deg,1,1,90); 
  rad = rot_d2r(deg);
  mat_print(rad);
  mat_set(deg,1,1,60); 
  rad = rot_d2r(deg);
  mat_print(rad);
  mat_set(degv,1,1,360); 
  mat_set(degv,1,2,180); 
  mat_set(degv,1,3,45); 
  mat_set(degv,1,4,22.5); 
  radv = rot_d2r(degv);
  mat_print(radv);

  // Radian to degree
  mat_set(rad,1,1,0.0); 
  deg = rot_r2d(rad);
  mat_print(deg);
  mat_set(rad,1,1,PI); 
  deg = rot_r2d(rad);
  mat_print(deg);
  mat_set(rad,1,1,2.5); 
  deg = rot_r2d(rad);
  mat_print(deg);
  mat_set(radv,1,1,PI2); 
  mat_set(radv,1,2,PIH); 
  mat_set(radv,1,3,PIQ); 
  mat_set(radv,1,4,PIE); 
  degv = rot_r2d(radv);
  mat_print(degv);

  // Wrap pi
  mat_set(radv,1,1, -3.5 );
  mat_set(radv,1,2, -PI  );
  mat_set(radv,1,3, -2.5 );
  mat_set(radv,1,4,  0.0 );
  radv = rot_wrappi(radv);
  mat_print(radv);
  mat_set(radv,1,1, 0.0 );
  mat_set(radv,1,2, 2.5 );
  mat_set(radv,1,3, PI  );
  mat_set(radv,1,4, 3.5 );
  radv = rot_wrappi(radv);
  mat_print(radv);

  // Wrap 2pi
  mat_set(radv,1,1, -7.0 );
  mat_set(radv,1,2, -PI2 );
  mat_set(radv,1,3, -5.0 );
  mat_set(radv,1,4,  0.0 );
  radv = rot_wrap2pi(radv);
  mat_print(radv);
  mat_set(radv,1,1, 0.0 );
  mat_set(radv,1,2, 5.0 );
  mat_set(radv,1,3, PI2 );
  mat_set(radv,1,4, 7.0 );
  radv = rot_wrap2pi(radv);
  mat_print(radv);

  // Clear matrices
  mat_clear(deg);
  mat_clear(rad);
  mat_clear(degv);
  mat_clear(radv);

  printf("\n");
}




//  RotEuler (Euler type rotations)
void RotEuler() {
  printf("Euler type rotations \n");

  // Define matrices
  matrix* R = mat_init(3,3);
  matrix* att = mat_init(3,1);
  mat_set(att,1,1, PIQ );
  mat_set(att,2,1, PIE );
  mat_set(att,3,1, PIS );

  // X axis rotaions
  R = rot_xaxis(PIE);
  mat_print(R);
  R = rot_xaxis(PIH);
  mat_print(R);

  // Y axis rotations
  R = rot_yaxis(PIE);
  mat_print(R);
  R = rot_yaxis(PIH);
  mat_print(R);

  // Z axis rotations
  R = rot_zaxis(PIE);
  mat_print(R);
  R = rot_zaxis(PIH);
  mat_print(R);

  // Euler rotation
  R = rot_eul(att);
  mat_print(R);

  // Clear matrices
  mat_clear(R);
  mat_clear(att);

  printf("\n");
}










/*(
// InitMat (initialize the matrices)
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
  mat_set(V4,1,1,-2);
  mat_set(V4,2,1, 7);
  mat_set(V4,3,1,-9);
  mat_set(V4,4,1, 5);
  
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
*/


/*
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
*/


/*
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
*/



