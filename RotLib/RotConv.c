
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  RotConv.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "RotLib.h"




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



