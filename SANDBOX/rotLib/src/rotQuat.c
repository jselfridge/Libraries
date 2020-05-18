/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* rotQuat.c
* Source code for quaternion operations within the 'rotLib' library.
*
*******************************************************************************/
#include "../inc/rotQuat.h"




/*******************************************************************************
* matrix* rot_e2q ( matrix* att )
* Converts an Euler attitude vector into a quaternion vector.
*******************************************************************************/
matrix* rot_e2q ( matrix* att ) {

  mat_err( ( att->rows!=3 || att->cols!=1 ), "Error (rot_e2q): Attitude is a 3 element column vector." );

  float cx = cosf( *(att->data  ) * 0.5 );
  float cy = cosf( *(att->data+1) * 0.5 );
  float cz = cosf( *(att->data+2) * 0.5 );

  float sx = sinf( *(att->data  ) * 0.5 );
  float sy = sinf( *(att->data+1) * 0.5 );
  float sz = sinf( *(att->data+2) * 0.5 );

  matrix* Q = mat_init( 4, 1 );

  *(Q->data  ) =  cx * cy * cz  +  sx * sy * sz;
  *(Q->data+1) =  sx * cy * cz  -  cx * sy * sz;
  *(Q->data+2) =  cx * sy * cz  +  sx * cy * sz;
  *(Q->data+3) =  cx * cy * sz  -  sx * sy * cz;

  return mat_uvec(Q);
}




/*******************************************************************************
* matrix* rot_q2e ( matrix* quat )
* Converts a quaternion vector into an Euler attitude vector.
*******************************************************************************/
matrix* rot_q2e ( matrix* quat ) {

  mat_err( ( quat->rows!=4 || quat->cols!=1 ), "Error (rot_q2e): Quaternion is a 4 element column vector." );

  float W = *(quat->data  );
  float X = *(quat->data+1);
  float Y = *(quat->data+2);
  float Z = *(quat->data+3);

  matrix* eul = mat_init( 3, 1 );

  *(eul->data  ) = atan2f( ( 2.0* (Y*Z+W*X) ), ( 2.0* ( powf(W,2) + powf(Z,2) ) -1.0 ) );
  *(eul->data+1) = -asinf  ( 2.0* (Z*X-W*Y) );
  *(eul->data+2) = atan2f( ( 2.0* (X*Y+W*Z) ), ( 2.0* ( powf(W,2) + powf(X,2) ) -1.0 ) );

  return eul;
}




/*******************************************************************************
* matrix* rot_q2dcm ( matrix* quat )
* Converts a quaternion vector into a Direction Cosine Matrix (DCM).
*******************************************************************************/
matrix* rot_q2dcm ( matrix* quat ) {

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




/*******************************************************************************
* matrix* rot_vec2q ( matrix* vecA, matrix* vecB )
* Returns a quaternion which provides a rotation from VecA to VecB.
*******************************************************************************/
matrix* rot_vec2q ( matrix* vecA, matrix* vecB ) {

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




/*******************************************************************************
* matrix* rot_vec2e ( matrix* vecA, matrix* vecB )
* Returns Euler angles to rotate from VecA to VecB.
*******************************************************************************/
matrix* rot_vec2e ( matrix* vecA, matrix* vecB ) {

  mat_err( vecA->rows!=3 || vecA->cols!=1, "Error (rot_vec2e): VecA must be a 3 element column vector." );
  mat_err( vecB->rows!=3 || vecB->cols!=1, "Error (rot_vec2e): VecB must be a 3 element column vector." );

  matrix* Q = rot_vec2q( vecA, vecB );
  matrix* E = rot_q2e(Q);

  rot_wrappi(E);

  mat_clear(Q);
  return E;
}




/*******************************************************************************
* matrix* rot_qskew ( matrix* quat )
* Takes a quaternion and returns a matrix used for quat multiplication.
*******************************************************************************/
matrix* rot_qskew ( matrix* quat ) {

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




/*******************************************************************************
* matrix* rot_qmul ( matrix* quatA, matrix* quatB )
* Performs quaternion multiplication.
*******************************************************************************/
matrix* rot_qmul ( matrix* quatA, matrix* quatB ) {

  mat_err( quatA->rows!=4 || quatA->cols!=1, "Error (rot_qmul): QuatA must be a 4 element column vector." );
  mat_err( quatB->rows!=4 || quatB->cols!=1, "Error (rot_qmul): QuatB must be a 4 element column vector." );

  matrix* Q = mat_init(4,1);
  Q = mat_mul( rot_qskew(quatA), quatB );

  return Q;
}




/*******************************************************************************
* matrix* rot_qderiv ( matrix* quat )
* Matrix to determine quaternion derivatives for a given angular rate.
*******************************************************************************/
matrix* rot_qderiv ( matrix* quat ) {

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



