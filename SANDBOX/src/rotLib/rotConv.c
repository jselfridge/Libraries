
//============================================================
//  rotConv.c
//  Justin M Selfridge
//============================================================
//#include "rotLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_d2r
//  Converts the angles of a matrix from degrees into radians.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
matrix* rot_d2r ( matrix* deg )  {
  return mat_scale( deg, PI/180.0 );
}
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_r2d
//  Converts the angles of matrix from radians into degrees.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
matrix* rot_r2d ( matrix* rad )  {
  return mat_scale( rad, 180.0/PI );
}
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_wrappi
//  Places the elements of a matrix within the range (-pi,pi].
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
void rot_wrappi ( matrix* rad )  {

  int i, j, r, c;
  double val;

  r = rad->rows;
  c = rad->cols;

  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ ) {
      val = mat_get(rad,i,j);
      while ( val >   PI )  val -= PI2;
      while ( val <= -PI )  val += PI2;
      mat_set( rad,i,j, val );
    }
  }

  return;
}
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_wrap2pi
//  Places the elements of a matrix within the range [0,2pi).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
void rot_wrap2pi ( matrix* rad )  {

  int i, j, r, c;
  double val;

  r = rad->rows;
  c = rad->cols;

  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ ) {
      val = mat_get(rad,i,j);
      while ( val >= PI2 )  val -= PI2;
      while ( val <   0  )  val += PI2;
      mat_set( rad,i,j, val );
    }
  }

  return;
}
*/


