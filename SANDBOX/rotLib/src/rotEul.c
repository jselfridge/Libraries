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
* Xb = Rx(a) * Xi
*******************************************************************************/
matrix* rot_xaxis ( float angle ) {

  matrix* R = mat_init( 3, 3 );
  float S = sinf(angle);
  float C = cosf(angle);

  *(R->data  ) = 1.0;
  *(R->data+4) =   C;
  *(R->data+5) =   S;
  *(R->data+7) =  -S;
  *(R->data+8) =   C;

  return R;
}




/*******************************************************************************
* matrix* rot_yaxis ( float angle ) {
* Generates a rotation matrix around the Y-axis.
* Xb = Ry(a) * Xi
*******************************************************************************/
matrix* rot_yaxis ( float angle ) {

  matrix* R = mat_init( 3, 3 );
  float S = sinf(angle);
  float C = cosf(angle);

  *(R->data  ) =   C;
  *(R->data+2) =  -S;
  *(R->data+4) = 1.0;
  *(R->data+6) =   S;
  *(R->data+8) =   C;

  return R;
}




/*******************************************************************************
* matrix* rot_zaxis ( float angle ) {
* Generates a rotation matrix around the Z-axis.
* Xb = Rz(a) * Xi
*******************************************************************************/
matrix* rot_zaxis ( float angle ) {

  matrix* R = mat_init( 3, 3 );
  float S = sinf(angle);
  float C = cosf(angle);

  *(R->data  ) =   C;
  *(R->data+1) =   S;
  *(R->data+3) =  -S;
  *(R->data+4) =   C;
  *(R->data+8) = 1.0;

  return R;
}




/*******************************************************************************
* matrix* rot_eul ( matrix* att ) {
* Rotation matrix that transforms from local (body) frame to 
* global (inertial) frame.  The transpose of this matrix 
* reverses the relationship.
* Xb = R * Xi    Xi = R' * Xb
*******************************************************************************/
matrix* rot_eul ( matrix* att ) {

  mat_err( ( att->rows!=3 || att->cols!=1 ), "Error (rot_eul): Attitude must be a 3 element column vector." );

  return mat_mul( rot_xaxis( *(att->data) ), mat_mul( rot_yaxis( *(att->data+1) ), rot_zaxis( *(att->data+2) ) ) );
}



