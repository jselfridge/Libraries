
//============================================================
//  RotQuat.c
//  Justin M Selfridge
//============================================================
#include "RotLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_e2q
//  Converts an Euler attitude vector to a quaternion vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_e2q ( matrix* att )  {

  mat_err( att->rows!=3 || att->cols!=1, "Error (rot_e2q): Attitude is a 3 element column vector." );

  double  X, Y, Z;
  double  Q1, Q2, Q3, Q4;
  matrix* Q;

  X = 0.5 * mat_get(att,1,1);
  Y = 0.5 * mat_get(att,2,1);
  Z = 0.5 * mat_get(att,3,1);

  Q1 = cos(X) * cos(Y) * cos(Z) + sin(X) * sin(Y) * sin(Z);
  Q2 = sin(X) * cos(Y) * cos(Z) - cos(X) * sin(Y) * sin(Z);
  Q3 = cos(X) * sin(Y) * cos(Z) + sin(X) * cos(Y) * sin(Z);
  Q4 = cos(X) * cos(Y) * sin(Z) - sin(X) * sin(Y) * cos(Z);

  Q = mat_init(4,1);
  mat_set(Q,1,1,Q1);
  mat_set(Q,2,1,Q2);
  mat_set(Q,3,1,Q3);
  mat_set(Q,4,1,Q4);

  return mat_uvec(Q);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_q2e
//  Converts a quaternion vector to an Euler attitude vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_q2e ( matrix* quat )  {

  mat_err( quat->rows!=4 || quat->cols!=1, "Error (rot_q2e): Quaternion is a 4 element column vector." );

  double  W, X, Y, Z;
  double  E1, E2, E3;
  matrix* E;

  W = mat_get(quat,1,1);
  X = mat_get(quat,2,1);
  Y = mat_get(quat,3,1);
  Z = mat_get(quat,4,1);

  E1 = atan2( ( 2*(W*X+Y*Z) ), ( 1-2*(pow(X,2)+pow(Y,2)) ) );
  E2 = asin ( 2*(W*Y-Z*X) );
  E3 = atan2( ( 2*(W*Z+X*Y) ), ( 1-2*(pow(Y,2)+pow(Z,2)) ) );

  E = mat_init(3,1);
  mat_set(E,1,1,E1);
  mat_set(E,2,1,E2);
  mat_set(E,3,1,E3);

  return E;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_q2dcm
//  Converts quaternion vector into Direction Cosine Matrix (DCM).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_q2dcm ( matrix* quat )  {

  mat_err( quat->rows!=4 || quat->cols!=1, "Error (rot_q2dcm): Quaternion is a 4 element column vector." );

  double  r;
  double  W,  X,  Y,  Z;
  double  W2, X2, Y2, Z2;
  matrix* R = mat_init(3,3);

  W = mat_get(quat,1,1);
  X = mat_get(quat,2,1);
  Y = mat_get(quat,3,1);
  Z = mat_get(quat,4,1);

  W2 = pow(W,2);
  X2 = pow(X,2);
  Y2 = pow(Y,2);
  Z2 = pow(Z,2);

  r = W2 + X2 - Y2 - Z2;  mat_set(R,1,1,r);
  r = 2 * ( X*Y - Z*W );  mat_set(R,1,2,r);
  r = 2 * ( X*Z + Y*W );  mat_set(R,1,3,r);

  r = 2 * ( Y*X + Z*W );  mat_set(R,2,1,r);
  r = W2 - X2 + Y2 - Z2;  mat_set(R,2,2,r);
  r = 2 * ( Y*Z - X*W );  mat_set(R,2,3,r);

  r = 2 * ( Z*X - Y*W );  mat_set(R,3,1,r);
  r = 2 * ( Z*Y + X*W );  mat_set(R,3,2,r);
  r = W2 - X2 - Y2 + Z2;  mat_set(R,3,3,r);

  return R;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_vec2q
//  Returns quaternion to rotate from VecA to VecB.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_vec2q ( matrix* vecA, matrix* vecB )  {

  mat_err( vecA->rows!=3 || vecA->cols!=1, "Error (rot_vec2q): VecA must be a 3 element column vector." );
  mat_err( vecB->rows!=3 || vecB->cols!=1, "Error (rot_vec2q): VecB must be a 3 element column vector." );

  double angle;
  matrix* Q; 
  matrix* axis;

  vecA = mat_uvec(vecA);
  vecB = mat_uvec(vecB);

  axis = mat_mul( mat_skew(vecA), vecB );
  angle = 1.0 + mat_dot( vecA, vecB );

  Q = mat_init(4,1);
  mat_set( Q,1,1, angle );
  mat_set( Q,2,1, mat_get(axis,1,1) );
  mat_set( Q,3,1, mat_get(axis,2,1) );
  mat_set( Q,4,1, mat_get(axis,3,1) );

  mat_clear(axis);
  return mat_uvec(Q);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_qskew
//  Takes a quaternion and returns a matrix for quat multiplication.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_qskew ( matrix* quat )  {

  mat_err( quat->rows!=4 || quat->cols!=1, "Error (rot_qskew): Quaternion must be a 4 element column vector." );

  double W, X, Y, Z;
  matrix* qskew;

  W = mat_get(quat,1,1);
  X = mat_get(quat,2,1);
  Y = mat_get(quat,3,1);
  Z = mat_get(quat,4,1);

  qskew = mat_init(4,4);
  mat_set( qskew,1,1, W );  mat_set( qskew,1,2, -X );  mat_set( qskew,1,3, -Y );  mat_set( qskew,1,4, -Z );
  mat_set( qskew,2,1, X );  mat_set( qskew,2,2,  W );  mat_set( qskew,2,3, -Z );  mat_set( qskew,2,4,  Y );
  mat_set( qskew,3,1, Y );  mat_set( qskew,3,2,  Z );  mat_set( qskew,3,3,  W );  mat_set( qskew,3,4, -X );
  mat_set( qskew,4,1, Z );  mat_set( qskew,4,2, -Y );  mat_set( qskew,4,3,  X );  mat_set( qskew,4,4,  W );

  return qskew;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_qmul
//  Performs quaternion multiplication.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_qmul ( matrix* quatA, matrix* quatB )  {

  mat_err( quatA->rows!=4 || quatA->cols!=1, "Error (rot_qmul): QuatA must be a 4 element column vector." );
  mat_err( quatB->rows!=4 || quatB->cols!=1, "Error (rot_qmul): QuatB must be a 4 element column vector." );

  matrix* Q = mat_init(4,1);
  Q = mat_mul( rot_qskew(quatA), quatB );

  return Q;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_qderiv
//  Matrix to determine quat derivatives given angular rate.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_qderiv ( matrix* quat )  {

  mat_err( quat->rows!=4 || quat->cols!=1, "Error (rot_qderiv): Quaternion must be a 4 element column vector." );

  double W, X, Y, Z;
  matrix* mat;

  W = mat_get(quat,1,1);
  X = mat_get(quat,2,1);
  Y = mat_get(quat,3,1);
  Z = mat_get(quat,4,1);

  mat = mat_init(4,3);
  mat_set( mat,1,1, -X );  mat_set( mat,1,2, -Y );  mat_set( mat,1,3, -Z );
  mat_set( mat,2,1,  W );  mat_set( mat,2,2,  Z );  mat_set( mat,2,3, -Y );
  mat_set( mat,3,1, -Z );  mat_set( mat,3,2,  W );  mat_set( mat,3,3,  X );
  mat_set( mat,4,1,  Y );  mat_set( mat,4,2, -X );  mat_set( mat,4,3,  W );

  return mat_scale(mat,0.5);
}



