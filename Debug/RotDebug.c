
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  RotDebug.c
//  Justin M Selfridge
//  Script to debug the RotLib Library
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "RotDebug.h"




// Debugging function 
void DebugRotLib() {
  printf("\n   --- RotLib Debugging --- \n\n");

  //RotConv();
  //RotEuler();

  // Euler to Quaternion
  matrix* quat = mat_init(4,1);
  matrix* att = mat_init(3,1);
  mat_set( att,1,1, PIQ );
  mat_set( att,2,1, PIE );
  mat_set( att,3,1, PIS );
  quat = rot_e2q(att);
  mat_print(quat);

  // Quaternion to Euler
  mat_print(rot_q2e(quat));

  // Quaternion to DCM
  mat_print(rot_eul(att));
  mat_print(rot_q2dcm(quat));

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
}



