/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* rotEul.c
* Source code for Euler attitude operations within the 'rotLib' library.
*
*******************************************************************************/
#include "../inc/rotEul.h"




/*******************************************************************************
* matrix* rot_xaxis ( float angle ) {
* Generates a rotation matrix around the X-axis.
*******************************************************************************/
matrix* rot_xaxis ( float angle ) {

  matrix* R = mat_init(3,3);
  double  S = sin(angle);
  double  C = cos(angle);

  mat_set( R,1,1, 1.0 );  mat_set( R,1,2, 0.0 );  mat_set( R,1,3, 0.0 );
  mat_set( R,2,1, 0.0 );  mat_set( R,2,2,  C  );  mat_set( R,2,3, -S  );
  mat_set( R,3,1, 0.0 );  mat_set( R,3,2,  S  );  mat_set( R,3,3,  C  );

  return R;
}




/*******************************************************************************
* matrix* rot_yaxis ( float angle ) {
* Generates a rotation matrix around the Y-axis.
*******************************************************************************/
matrix* rot_yaxis ( float angle ) {

  matrix* R = mat_init(3,3);
  double  S = sin(angle);
  double  C = cos(angle);

  mat_set( R,1,1,  C  );  mat_set( R,1,2, 0.0 );  mat_set( R,1,3,  S );
  mat_set( R,2,1, 0.0 );  mat_set( R,2,2, 1.0 );  mat_set( R,2,3, 0.0 );
  mat_set( R,3,1, -S  );  mat_set( R,3,2, 0.0 );  mat_set( R,3,3,  C  );

  return R;
}




/*******************************************************************************
* matrix* rot_zaxis ( float angle ) {
* Generates a rotation matrix around the Z-axis.
*******************************************************************************/
matrix* rot_zaxis ( float angle ) {

  matrix* R = mat_init(3,3);
  double  S = sin(angle);
  double  C = cos(angle);

  mat_set( R,1,1,  C  );  mat_set( R,1,2, -S  );  mat_set( R,1,3, 0.0 );
  mat_set( R,2,1,  S  );  mat_set( R,2,2,  C  );  mat_set( R,2,3, 0.0 );
  mat_set( R,3,1, 0.0 );  mat_set( R,3,2, 0.0 );  mat_set( R,3,3, 1.0 );

  return R;
}




/*******************************************************************************
* matrix* rot_eul ( matrix* att ) {
* Rotation matrix that transforms from local (body) frame to 
* global (inertial) frame.  The transpose of this matrix 
* reverses the relationship.
* Xi = R * Xb , Xb = R' * Xi
*******************************************************************************/
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



