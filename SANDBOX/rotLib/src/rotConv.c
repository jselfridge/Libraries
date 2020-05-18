/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* rotConv.c
* Source code for rotation conversions within the 'rotLib' library.
*
*******************************************************************************/
#include "../inc/rotConv.h"




/*******************************************************************************
* matrix* rot_d2r ( matrix* deg )
* Converts the angles of a matrix from degrees into radians.
*******************************************************************************/
matrix* rot_d2r ( matrix* deg ) {
  return mat_scale( deg, DEG2RAD );
}




/*******************************************************************************
* matrix* rot_r2d ( matrix* rad )  {
* Converts the angles of matrix from radians into degrees.
*******************************************************************************/
matrix* rot_r2d ( matrix* rad ) {
  return mat_scale( rad, RAD2DEG );
}




/*******************************************************************************
* void rot_wrappi ( matrix* rad )
* Places the elements of a matrix within the range (-pi,pi].
*******************************************************************************/
void rot_wrappi ( matrix* rad ) {

  for( uint i=0; i < sizeof rad / sizeof *rad; i++ ) {
    while ( *(rad->data+i) >   M_PI )  *(rad->data+i) -= 2.0 * M_PI;
    while ( *(rad->data+i) <= -M_PI )  *(rad->data+i) += 2.0 * M_PI;
  }

  return;
}




/*******************************************************************************
* void rot_wrap2pi ( matrix* rad )
* Places the elements of a matrix within the range [0,2pi).
*******************************************************************************/
void rot_wrap2pi ( matrix* rad ) {

  for( uint i=0; i < sizeof rad / sizeof *rad; i++ ) {
    while ( *(rad->data+i) >= 2.0 * M_PI )  *(rad->data+i) -= 2.0 * M_PI;
    while ( *(rad->data+i) <  0.0        )  *(rad->data+i) += 2.0 * M_PI;
  }

  return;
}



