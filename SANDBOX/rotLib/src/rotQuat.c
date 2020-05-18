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
* matrix* rot_qDef ( float rot, matrix* vec )
* Creates a quaternion defined by a rotation by an angle around a vector.
*******************************************************************************/
matrix* rot_qDef ( float rot, matrix* vec ) {

  float r = rot / 2.0;
  matrix* quat = mat_init( 1, 4 );

  *(quat->data  ) = cosf(r);
  *(quat->data+1) = sinf(r) * *(vec->data  );
  *(quat->data+2) = sinf(r) * *(vec->data+1);
  *(quat->data+3) = sinf(r) * *(vec->data+2);

  return mat_uvec(quat);
}




/*******************************************************************************
* matrix* rot_qConj ( matrix* quat )
* Returns the conjugate of a quaternion.
*******************************************************************************/
matrix* rot_qConj ( matrix* quat ) {

  matrix* conj = mat_init( 1, 4 );

  *(conj->data  ) =   *(quat->data  );
  *(conj->data+1) = - *(quat->data+1);
  *(conj->data+2) = - *(quat->data+2);
  *(conj->data+3) = - *(quat->data+3);

  return conj;
}




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

  mat_err( ( quat->rows!=4 || quat->cols!=1 ), "Error (rot_q2dcm): Quaternion is a 4 element column vector." );

  float W = *(quat->data  );
  float X = *(quat->data+1);
  float Y = *(quat->data+2);
  float Z = *(quat->data+3);

  float WW = 2.0 * powf(W,2);
  float XX = 2.0 * powf(X,2);
  float YY = 2.0 * powf(Y,2);
  float ZZ = 2.0 * powf(Z,2);
  
  float XY = 2.0 * X * Y;
  float XZ = 2.0 * X * Z;
  float YZ = 2.0 * Y * Z;

  matrix* R = mat_init( 3, 3 );

  *(R->data  ) = WW + XX -1.0;    *(R->data+1) = XY + WZ;         *(R->data+2) = XZ - WY;
  *(R->data+3) = XY - WZ;         *(R->data+4) = WW + YY -1.0;    *(R->data+5) = YZ + WX;
  *(R->data+6) = XZ + WY;         *(R->data+7) = YZ - WX;         *(R->data+8) = WW + ZZ -1.0;

  return R;
}




/*******************************************************************************
* matrix* rot_qProd ( matrix* a, matrix* b )
* Returns the quaternion product used for quaternion multiplication.
*******************************************************************************/
matrix* rot_qProd ( matrix* a, matrix* b ) {

  mat_err( ( a->rows!=4 || a->cols!=1 ), "Error (rot_qProd): Quaternion is a 4 element column vector." );
  mat_err( ( b->rows!=4 || b->cols!=1 ), "Error (rot_qProd): Quaternion is a 4 element column vector." );

  matrix* prod = mat_init( 4, 1 );

  *(prod->data  ) = *(a->data) * *(b->data  )  - *(a->data+1) * *(b->data+1)  - *(a->data+2) * *(b->data+2)  - *(a->data+3) * *(b->data+3);
  *(prod->data+1) = *(a->data) * *(b->data+1)  + *(a->data+1) * *(b->data  )  + *(a->data+2) * *(b->data+3)  - *(a->data+3) * *(b->data+2);
  *(prod->data+2) = *(a->data) * *(b->data+2)  - *(a->data+1) * *(b->data+3)  + *(a->data+2) * *(b->data  )  + *(a->data+3) * *(b->data+1);
  *(prod->data+3) = *(a->data) * *(b->data+3)  + *(a->data+1) * *(b->data+2)  - *(a->data+2) * *(b->data+1)  + *(a->data+3) * *(b->data  );

  return;
}




/*******************************************************************************
* matrix* rot_qDeriv ( matrix* quat, matrix* ang )
* Calculates the quaternion derivative given a quaternion and an angular rate vector.
*******************************************************************************/
matrix* rot_qDeriv ( matrix* quat, matrix* ang ) {

  mat_err( ( quat->rows!=4 || quat->cols!=1 ), "Error (rot_qDeriv): Quaternion must be a 4 element column vector."   );
  mat_err( ( ang->rows !=3 || ang->cols !=1 ), "Error (rot_qDeriv): Angular rate must be a 3 element column vector." );

  matrix* qd = mat_init( 4, 1 );

  *(qd->data  ) = 0.5 * ( - *(quat->data+1) * *(ang->data) - *(quat->data+2) * *(ang->data+1) - *(quat->data+3) * *(ang->data+2) );
  *(qd->data+1) = 0.5 * (   *(quat->data  ) * *(ang->data) - *(quat->data+3) * *(ang->data+1) + *(quat->data+2) * *(ang->data+2) );
  *(qd->data+2) = 0.5 * (   *(quat->data+3) * *(ang->data) + *(quat->data  ) * *(ang->data+1) - *(quat->data+1) * *(ang->data+2) );
  *(qd->data+3) = 0.5 * ( - *(quat->data+2) * *(ang->data) + *(quat->data+1) * *(ang->data+1) + *(quat->data  ) * *(ang->data+2) );

  return qd;
}




/*******************************************************************************
* matrix* rot_vec2q ( matrix* a, matrix* b )
* Returns a quaternion which provides a rotation from vector 'a' to vector 'b'.
* b = rot_q2dcm(q) * a
*******************************************************************************/
matrix* rot_vec2q ( matrix* a, matrix* b ) {

  mat_err( ( a->rows!=3 || a->cols!=1 ), "Error (rot_vec2q): Vector 'a' must be a 3 element column vector." );
  mat_err( ( b->rows!=3 || b->cols!=1 ), "Error (rot_vec2q): Vector 'b' must be a 3 element column vector." );

  // Normalize input vectors
  a = mat_uvec(a);  // DO I NEED THIS ??
  b = mat_uvec(b);  // DO I NEED THIS ??

  // Find rotation axis
  matrix* axis = mat_uvec( mat_skew(b) * a );

  // Find dot product
  float dot = mat_dot( a, b );

  // Remove numerical error when parallel
  if( dot >= 1.0 - 1e-10 );
    matrix* q = mat_init( 4, 1 );
    *(q->data) = 1.0;
    return q;
  end;

  // Remove numerical error when opposite
  if( dot <= -1.0 + 1e-10 );
    matrix* q = mat_init( 4, 1 );
    *(q->data+3) = 1.0;
    return q;
  end;

  // Find angle between unit vectors
  float angle = acosf(dot);

  // Assemble quaternion
  matrix* q = rot_qDef( angle, axis );

  return q;
}




/*******************************************************************************
* matrix* rot_dRqw ( matrix* quat )
* Returns the partial derivatives of a DCM wrt quat_w.
*******************************************************************************/
matrix* rot_dRqw ( matrix* quat ) {

  float w = *(quat->data  ) * 4.0;
  float x = *(quat->data+1) * 2.0;
  float y = *(quat->data+2) * 2.0;
  float z = *(quat->data+3) * 2.0;

  matrix* qw = mat_init( 3, 3 );

  *(qw->data  ) =  w;    *(qw->data+1) =  z;    *(qw->data+2) = -y;
  *(qw->data+3) = -z;    *(qw->data+4) =  w;    *(qw->data+5) =  x;
  *(qw->data+6) =  y;    *(qw->data+7) = -x;    *(qw->data+8) =  w;

  return qw;
}




/*******************************************************************************
* matrix* rot_dRqx ( matrix* quat )
* Returns the partial derivatives of a DCM wrt a quat_x.
*******************************************************************************/
matrix* rot_dRqx ( matrix* quat ) {

  float w = *(quat->data  ) * 2.0;
  float x = *(quat->data+1) * 4.0;
  float y = *(quat->data+2) * 2.0;
  float z = *(quat->data+3) * 2.0;

  matrix* qx = mat_init( 3, 3 );

  *(qx->data  ) =  x;    *(qx->data+1) =  y;    *(qx->data+2) =  z;
  *(qx->data+3) =  y;    *(qx->data+4) =  0;    *(qx->data+5) =  w;
  *(qx->data+6) =  z;    *(qx->data+7) = -w;    *(qx->data+8) =  0;

  return qx;
}




/*******************************************************************************
* matrix* rot_dRqy ( matrix* quat )
* Returns the partial derivatives of a DCM wrt a quat_y.
*******************************************************************************/
matrix* rot_dRqy ( matrix* quat ) {

  float w = *(quat->data  ) * 2.0;
  float x = *(quat->data+1) * 2.0;
  float y = *(quat->data+2) * 4.0;
  float z = *(quat->data+3) * 2.0;

  matrix* qy = mat_init( 3, 3 );

  *(qy->data  ) =  0;    *(qy->data+1) =  x;    *(qy->data+2) = -w;
  *(qy->data+3) =  x;    *(qy->data+4) =  y;    *(qy->data+5) =  z;
  *(qy->data+6) =  w;    *(qy->data+7) =  z;    *(qy->data+8) =  0;

  return qy;
}




/*******************************************************************************
* matrix* rot_dRqz ( matrix* quat )
* Returns the partial derivatives of a DCM wrt a quat_z.
*******************************************************************************/
matrix* rot_dRqz ( matrix* quat ) {

  float w = *(quat->data  ) * 2.0;
  float x = *(quat->data+1) * 2.0;
  float y = *(quat->data+2) * 2.0;
  float z = *(quat->data+3) * 4.0;

  matrix* qz = mat_init( 3, 3 );

  *(qz->data  ) =  0;    *(qz->data+1) =  w;    *(qz->data+2) =  x;
  *(qz->data+3) = -w;    *(qz->data+4) =  0;    *(qz->data+5) =  y;
  *(qz->data+6) =  x;    *(qz->data+7) =  y;    *(qz->data+8) =  z;

  return qz;
}




/*******************************************************************************
* matrix* rot_dRot ( matrix* quat )
* Returns the partial derivatives of a DCM wrt a quaterion input.
*******************************************************************************/
// matrix* rot_dRot ( matrix* quat ) {

//   float w = *(quat->data  ) * 2.0;
//   float x = *(quat->data+1) * 2.0;
//   float y = *(quat->data+2) * 2.0;
//   float z = *(quat->data+3) * 2.0;

//   matrix* dRot = mat_init( 3, 4 );

//   return ???;
// }




