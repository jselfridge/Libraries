
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Rot.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "RotLib.h"




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  RotConv
//  Rotation functions that perform some type of conversion.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_d2r
//  Converts the angles of a matrix from degrees into radians.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_d2r ( matrix* deg ) {

  int r = deg->rows;
  int c = deg->cols;
  int n = r*c;

  matrix* rad   = mat_init(r,c);
  double* ddata = deg->data;
  double* rdata = rad->data;

  for ( int i=0; i<n; i++ ) {
    *rdata = *ddata * (PI/180.0);
    ddata++;
    rdata++;
  }

  return rad;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_r2d
//  Converts the angles of matrix from radians into degrees.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_r2d ( matrix* rad ) {

  int r = rad->rows;
  int c = rad->cols;
  int n = r*c;

  matrix* deg   = mat_init(r,c);
  double* ddata = deg->data;
  double* rdata = rad->data;

  for ( int i=0; i<n; i++ ) {
    *ddata = *rdata * (180.0/PI);
    ddata++;
    rdata++;
  }

  return deg;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_wrappi
//  Places the elements of a matrix within the range (-pi,pi].
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_wrappi ( matrix* rad ) {

  int r = rad->rows;
  int c = rad->cols;
  int n = r*c;

  matrix* wrap  = mat_init(r,c);
  double* rdata = rad->data;
  double* wdata = wrap->data;

  for ( int i=0; i<n; i++ ) {
    double elem = *rdata;
    while ( elem >   PI ) { elem -= PI2; }
    while ( elem <= -PI ) { elem += PI2; }
    *wdata = elem;
    rdata++;
    wdata++;
  }

  return wrap;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_wrap2pi
//  Places the elements of a matrix within the range [0,2pi).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_wrap2pi ( matrix* rad ) {

  int r = rad->rows;
  int c = rad->cols;
  int n = r*c;

  matrix* wrap  = mat_init(r,c);
  double* rdata = rad->data;
  double* wdata = wrap->data;

  for ( int i=0; i<n; i++ ) {
    double elem = *rdata;
    while ( elem >= PI2 ) { elem -= PI2; }
    while ( elem <   0  ) { elem += PI2; }
    *wdata = elem;
    rdata++;
    wdata++;
  }

  return wrap;
}




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  RotEuler
//  Functions that perform Euler rotations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_xaxis
//  Generates a rotation matrix around the X-axis.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_xaxis ( double angle ) {

  matrix* R = mat_init(3,3);
  double  S = sin(angle);
  double  C = cos(angle);

  mat_set( R,1,1, 1.0 );  mat_set( R,1,2, 0.0 );  mat_set( R,1,3, 0.0 );
  mat_set( R,2,1, 0.0 );  mat_set( R,2,2,  C  );  mat_set( R,2,3, -S  );
  mat_set( R,3,1, 0.0 );  mat_set( R,3,2,  S  );  mat_set( R,3,3,  C  );

  return R;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_yaxis
//  Generates a rotation matrix around the Y-axis.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_yaxis ( double angle ) {

  matrix* R = mat_init(3,3);
  double  S = sin(angle);
  double  C = cos(angle);

  mat_set( R,1,1,  C  );  mat_set( R,1,2, 0.0 );  mat_set( R,1,3,  S );
  mat_set( R,2,1, 0.0 );  mat_set( R,2,2, 1.0 );  mat_set( R,2,3, 0.0 );
  mat_set( R,3,1, -S  );  mat_set( R,3,2, 0.0 );  mat_set( R,3,3,  C  );

  return R;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_zaxis
//  Generates a rotation matrix around the Z-axis.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_zaxis ( double angle ) {

  matrix* R = mat_init(3,3);
  double  S = sin(angle);
  double  C = cos(angle);

  mat_set( R,1,1,  C  );  mat_set( R,1,2, -S  );  mat_set( R,1,3, 0.0 );
  mat_set( R,2,1,  S  );  mat_set( R,2,2,  C  );  mat_set( R,2,3, 0.0 );
  mat_set( R,3,1, 0.0 );  mat_set( R,3,2, 0.0 );  mat_set( R,3,3, 1.0 );

  return R;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_eul
//  Rotation matrix that transforms from local (body) frame to 
//  global (inertial) frame.  The transpose of this matrix 
//  reverses the relationship.
//  Xi = R * Xb , Xb = R' * Xi
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_eul ( matrix* att ) {

  mat_err( att->rows!=3 || att->cols!=1, "Error (rot_eul): Attitude must be a 3 element column vector." );

  matrix* R = mat_init(3,3);
  double  X = mat_get(att,1,1);
  double  Y = mat_get(att,2,1);
  double  Z = mat_get(att,3,1);

  R =  mat_mul( rot_zaxis(Z), rot_yaxis(Y) ); 
  R =  mat_mul( R, rot_xaxis(X) ); 

  return R;
}




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  RotQuat
//  Functions that perform quaternion manipulations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_e2q
//  Converts an Euler attitude vector to a quaternion vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_e2q ( matrix* att ) {

  mat_err( att->rows!=3 || att->cols!=1, "Error (rot_e2q): Attitude is a 3 element column vector." );

  matrix* Q = mat_init(4,1);

  double X = 0.5 * mat_get(att,1,1);
  double Y = 0.5 * mat_get(att,2,1);
  double Z = 0.5 * mat_get(att,3,1);

  double Q1 = cos(X) * cos(Y) * cos(Z) + sin(X) * sin(Y) * sin(Z);
  double Q2 = sin(X) * cos(Y) * cos(Z) - cos(X) * sin(Y) * sin(Z);
  double Q3 = cos(X) * sin(Y) * cos(Z) + sin(X) * cos(Y) * sin(Z);
  double Q4 = cos(X) * cos(Y) * sin(Z) - sin(X) * sin(Y) * cos(Z);

  mat_set(Q,1,1,Q1);
  mat_set(Q,2,1,Q2);
  mat_set(Q,3,1,Q3);
  mat_set(Q,4,1,Q4);

  return mat_uvec(Q);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_q2e
//  Converts a quaternion vector to Euler attitude vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_q2e ( matrix* quat ) {

  mat_err( quat->rows!=4 || quat->cols!=1, "Error (rot_q2e): Quaternion is a 4 element column vector." );

  matrix* E = mat_init(3,1);

  double W = mat_get(quat,1,1);
  double X = mat_get(quat,2,1);
  double Y = mat_get(quat,3,1);
  double Z = mat_get(quat,4,1);

  double E1 = atan2( ( 2*(W*X+Y*Z) ), ( 1-2*(pow(X,2)+pow(Y,2)) ) );
  double E2 = asin ( 2*(W*Y-Z*X) );
  double E3 = atan2( ( 2*(W*Z+X*Y) ), ( 1-2*(pow(Y,2)+pow(Z,2)) ) );

  mat_set(E,1,1,E1);
  mat_set(E,2,1,E2);
  mat_set(E,3,1,E3);

  return E;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_q2dcm
//  Converts a quaternion vector into Direction Cosine Matrix (DCM).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_q2dcm ( matrix* quat ) {

  mat_err( quat->rows!=4 || quat->cols!=1, "Error (rot_q2dcm): Quaternion is a 4 element column vector." );

  matrix* R = mat_init(3,3);

  double W = mat_get(quat,1,1);
  double X = mat_get(quat,2,1);
  double Y = mat_get(quat,3,1);
  double Z = mat_get(quat,4,1);

  double W2 = pow(W,2);
  double X2 = pow(X,2);
  double Y2 = pow(Y,2);
  double Z2 = pow(Z,2);

  double R11 =  W2 + X2 - Y2 - Z2;  mat_set(R,1,1,R11);
  double R12 =  2 * ( X*Y - Z*W );  mat_set(R,1,2,R12);
  double R13 =  2 * ( X*Z + Y*W );  mat_set(R,1,3,R13);

  double R21 =  2 * ( Y*X + Z*W );  mat_set(R,2,1,R21);
  double R22 =  W2 - X2 + Y2 - Z2;  mat_set(R,2,2,R22);
  double R23 =  2 * ( Y*Z - X*W );  mat_set(R,2,3,R23);

  double R31 =  2 * ( Z*X - Y*W );  mat_set(R,3,1,R31);
  double R32 =  2 * ( Z*Y + X*W );  mat_set(R,3,2,R32);
  double R33 =  W2 - X2 - Y2 + Z2;  mat_set(R,3,3,R33);

  return R;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_vec2q
//  Returns quaternion to rotate from VecA to VecB.
//  VecB = rot_q2dcm(VecA)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_vec2q ( matrix* vecA, matrix* vecB ) {

  mat_err( vecA->rows!=3 || vecA->cols!=1, "Error (rot_vec2q): VecA is a 3 element column vector." );
  mat_err( vecB->rows!=3 || vecB->cols!=1, "Error (rot_vec2q): VecB is a 3 element column vector." );

  matrix* Q = mat_init(4,1);

  vecA = mat_uvec(vecA);
  vecB = mat_uvec(vecB);

  matrix* axis = mat_init(3,1);
  axis = mat_mul( mat_skew(vecA), vecB );

  double angle = 1.0 + mat_dot( vecA, vecB );

  mat_set( Q,1,1, angle );
  mat_set( Q,2,1, mat_get(axis,1,1) );
  mat_set( Q,3,1, mat_get(axis,2,1) );
  mat_set( Q,4,1, mat_get(axis,3,1) );

  return mat_uvec(Q);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_qskew
//  Takes a quaternion and returns a matrix for quat multiplication.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_qskew ( matrix* quat ) {

  mat_err( quat->rows!=4 || quat->cols!=1, "Error (rot_qskew): Quaternion must be a 4 element column vector." );
  matrix* qskew = mat_init(4,4);

  double W = mat_get(quat,1,1);
  double X = mat_get(quat,2,1);
  double Y = mat_get(quat,3,1);
  double Z = mat_get(quat,4,1);

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
matrix* rot_qmul ( matrix* quatA, matrix* quatB ) {

  mat_err( quatA->rows!=4 || quatA->cols!=1, "Error (rot_qmul): QuatA must be a 4 element column vector." );
  mat_err( quatB->rows!=4 || quatB->cols!=1, "Error (rot_qmul): QuatB must be a 4 element column vector." );
  matrix* Q = mat_init(4,1);
  Q = mat_mul( rot_qskew(quatA), quatB );

  return Q;
}




