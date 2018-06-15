/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matVec.h
* Source code for matrix vector functions within the 'matLib' library.
*
*******************************************************************************/
#include "matLib.h"




/*******************************************************************************
* matrix* mat_skew ( matrix *vec )
* Returns a skew symmetric matrix of a 3 element column vector.
*******************************************************************************/
matrix* mat_skew ( matrix *vec ) {

  mat_err( vec->rows != 3 || vec->cols != 1, "Error (mat_skew): Input vector must be [3x1]." );
  matrix *skew = mat_init(3,3);

  float x = mat_get( vec, 1, 1 );  mat_set( skew, 3, 2, x );  mat_set( skew, 2, 3, -x );
  float y = mat_get( vec, 2, 1 );  mat_set( skew, 1, 3, y );  mat_set( skew, 3, 1, -y );
  float z = mat_get( vec, 3, 1 );  mat_set( skew, 2, 1, z );  mat_set( skew, 1, 2, -z );

  return skew;
}




/*******************************************************************************
* matrix* mat_sskew ( matrix *vec )
* Returns a skew skew symmetric matrix of a 3 element column vector.
*******************************************************************************/
matrix* mat_sskew ( matrix *vec ) {

  mat_err( vec->rows != 3 || vec->cols != 1, "Error (mat_sskew): Input vector must be [3x1]." );
  matrix *sskew = mat_init(3,3);

  float x = mat_get( vec, 1, 1 );
  float y = mat_get( vec, 2, 1 );
  float z = mat_get( vec, 3, 1 );

  float x2 = x * x;
  float y2 = y * y;
  float z2 = z * z;

  float xy = x * y;
  float xz = x * z;
  float yz = y * z;

  mat_set( sskew, 1, 1, -y2-z2 );  mat_set( sskew, 1, 2,     xy );  mat_set( sskew, 1, 3,     xz );
  mat_set( sskew, 2, 1,     xy );  mat_set( sskew, 2, 2, -x2-z2 );  mat_set( sskew, 2, 3,     yz );
  mat_set( sskew, 3, 1,     xz );  mat_set( sskew, 3, 2,     yz );  mat_set( sskew, 3, 3, -x2-y2 );

  return sskew;
}




/*******************************************************************************
* matrix* mat_cross ( matrix *vecA, matrix *vecB )
* Returns the cross product of two three-element vectors.
*******************************************************************************/
matrix* mat_cross ( matrix *vecA, matrix *vecB ) {

  mat_err( vecA->rows != 3 || vecA->cols != 1, "Error (mat_cross): Vector A must be [3x1]." );
  mat_err( vecB->rows != 3 || vecB->cols != 1, "Error (mat_cross): Vector B must be [3x1]." );

  float ax, ay, az;
  float bx, by, bz;
  float cx, cy, cz;
  matrix *out;

  ax = mat_get( vecA, 1, 1 );
  ay = mat_get( vecA, 2, 1 );
  az = mat_get( vecA, 3, 1 );

  bx = mat_get( vecB, 1, 1 );
  by = mat_get( vecB, 2, 1 );
  bz = mat_get( vecB, 3, 1 );

  cx = ay * bz - az * by;
  cy = az * bx - ax * bz;
  cz = ax * by - ay * bx;

  out = mat_init(3,1);
  mat_set( out, 1, 1, cx );
  mat_set( out, 2, 1, cy );
  mat_set( out, 3, 1, cz );

  return out;
}




/*******************************************************************************
* float mat_dot ( matrix *vecA, matrix *vecB )
* Returns the dot product of two arbitrary length vectors.
*******************************************************************************/
float mat_dot ( matrix *vecA, matrix *vecB ) {

  mat_err( vecA->cols != 1 || vecB->cols != 1, "Error (mat_dot): Requires column vector inputs."   );
  mat_err( vecA->rows != vecB->rows,           "Error (mat_dot): Vectors must be the same height." );

  uint i;
  float out = 0.0f;
  for( i=1; i <= vecA->rows; i++ )  out += mat_get( vecA, i, 1 ) * mat_get( vecB, i, 1 );

  return out;
}




/*******************************************************************************
* float mat_norm ( matrix *vec, uint p )
* Returns the norm of a vector of a specified degree (infinity norm when p=0).
*******************************************************************************/
float mat_norm ( matrix *vec, uint p ) {

  mat_err( p < 0,          "Error (mat_norm): Degree of a norm must be positive." );
  mat_err( vec->cols != 1, "Error (mat_norm): Input must be a column vector."     );

  uint i, r;
  float norm, val, root;

  r = vec->rows;
  norm = 0.0f;
  val = 0.0f;

  if( p==0 ) {
    for( i=1; i<=r; i++ ) {
      val = fabs( mat_get( vec, i, 1 ) );
      if( val > norm )  norm = val;
    }
  }

  else {
    for( i=1; i<=r; i++ ) {
      val = fabs( mat_get( vec, i, 1 ) );
      val = pow( val, p );
      norm += val;
    }
    root = 1.0f / (float) p;
    norm = pow( norm, root );
  }

  return norm;
}




/*******************************************************************************
* float mat_mag ( matrix *vec )
* Returns the magnitude (Euclidean norm) of a column vector.
*******************************************************************************/
float mat_mag ( matrix *vec ) {
  mat_err( vec->cols != 1, "Error (mat_mag): Input must be a column vector." );
  return mat_norm( vec, 2 );
}




/*******************************************************************************
* matrix* mat_uvec ( matrix *vec )
* Returns an equivalent unit vector.
*******************************************************************************/
matrix* mat_uvec ( matrix *vec ) {

  mat_err( vec->cols != 1, "Error (mat_uvec): Input must be a column vector." );

  uint i, r;
  float mag, val;
  matrix *uvec;

  r = vec->rows;
  mag = mat_mag(vec);
  uvec = mat_init(r,1);

  if( mag==0 )  return uvec;
  else {
    for( i=1; i<=r; i++ ) {
      val = mat_get( vec, i, 1 );
      val /= mag;
      mat_set( uvec, i, 1, val );
    }
  }

  return uvec;
}




/*******************************************************************************
* matrix* mat_proj ( matrix *u, matrix *v )
* Returns the projection of vector u onto vector v.
*******************************************************************************/
matrix* mat_proj ( matrix *u, matrix *v ) {

  mat_err( u->cols != 1 || v->cols != 1, "Error (mat_proj): Inputs must be column vectors."         );
  mat_err( u->rows != v->rows,           "Error (mat_proj): Input vectors must be the same height." );

  matrix *proj;
  float mag, ratio;

  mag = mat_mag(v);

  if( mag==0 )  proj = mat_init( u->rows, 1 );
  else {
    ratio = mat_dot( u, v ) / mat_dot( v, v );
    proj = mat_scale( v, ratio );
  }

  return proj;
}



