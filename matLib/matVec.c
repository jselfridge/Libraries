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
* matrix* mat_skew ( matrix* vec )
* Returns the cross product skew symmetric matrix of a 3 element column vector.
*******************************************************************************/
matrix* mat_skew ( matrix* vec ) {

  mat_err( ( vec->rows != 3 || vec->cols != 1 ), "Error (mat_skew): Input vector must be [3x1]." );
  matrix* skew = mat_init( 3, 3 );

  float* data = vec->data;
  *( skew->data+7 ) = (*data);
  *( skew->data+5 ) = (*data) * (-1.0);
  data++;
  *( skew->data+2 ) = (*data);
  *( skew->data+6 ) = (*data) * (-1.0);
  data++;
  *( skew->data+3 ) = (*data);
  *( skew->data+1 ) = (*data) * (-1.0);

  return skew;
}




/*******************************************************************************
* matrix* mat_sskew ( matrix* vec )
* Returns the double cross product skew symmetric matrix of a 3 element column vector.
*******************************************************************************/
matrix* mat_sskew ( matrix* vec ) {

  mat_err( ( vec->rows != 3 || vec->cols != 1 ), "Error (mat_sskew): Input vector must be [3x1]." );
  matrix* sskew = mat_init( 3, 3 );

  float x2 = *(vec->data  ) * *(vec->data  );
  float y2 = *(vec->data+1) * *(vec->data+1);
  float z2 = *(vec->data+2) * *(vec->data+2);

  float xy = *(vec->data  ) * *(vec->data+1);
  float xz = *(vec->data  ) * *(vec->data+2);
  float yz = *(vec->data+1) * *(vec->data+2);

  *(sskew->data  ) = -y2-z2;  *(sskew->data+1) =     xy;  *(sskew->data+2) =     xz;
  *(sskew->data+3) =     xy;  *(sskew->data+4) = -x2-z2;  *(sskew->data+5) =     yz;
  *(sskew->data+6) =     xz;  *(sskew->data+7) =     yz;  *(sskew->data+8) = -x2-y2;

  return sskew;
}




/*******************************************************************************
* matrix* mat_cross ( matrix* vecA, matrix* vecB )
* Returns the cross product of two three-element vectors.
*******************************************************************************/
// matrix* mat_cross ( matrix* vecA, matrix* vecB ) {

//   mat_err( vecA->rows != 3 || vecA->cols != 1, "Error (mat_cross): Vector A must be [3x1]." );
//   mat_err( vecB->rows != 3 || vecB->cols != 1, "Error (mat_cross): Vector B must be [3x1]." );

//   float ax, ay, az;
//   float bx, by, bz;
//   float cx, cy, cz;
//   matrix* out;

//   ax = mat_get( vecA, 1, 1 );
//   ay = mat_get( vecA, 2, 1 );
//   az = mat_get( vecA, 3, 1 );

//   bx = mat_get( vecB, 1, 1 );
//   by = mat_get( vecB, 2, 1 );
//   bz = mat_get( vecB, 3, 1 );

//   cx = ay * bz - az * by;
//   cy = az * bx - ax * bz;
//   cz = ax * by - ay * bx;

//   out = mat_init(3,1);
//   mat_set( out, 1, 1, cx );
//   mat_set( out, 2, 1, cy );
//   mat_set( out, 3, 1, cz );

//   return out;
// }




/*******************************************************************************
* float mat_dot ( matrix* vecA, matrix* vecB )
* Returns the dot product of two arbitrary length vectors.
*******************************************************************************/
// float mat_dot ( matrix* vecA, matrix* vecB ) {

//   mat_err( vecA->cols != 1 || vecB->cols != 1, "Error (mat_dot): Requires column vector inputs."   );
//   mat_err( vecA->rows != vecB->rows,           "Error (mat_dot): Vectors must be the same height." );

//   ushort i;
//   float out = 0.0f;
//   for( i=1; i <= vecA->rows; i++ )  out += mat_get( vecA, i, 1 ) * mat_get( vecB, i, 1 );

//   return out;
// }




/*******************************************************************************
* float mat_norm ( matrix* vec, ushort p )
* Returns the norm of a vector of a specified degree (infinity norm when p=0).
*******************************************************************************/
// float mat_norm ( matrix* vec, ushort p ) {

//   mat_err( p < 0,          "Error (mat_norm): Degree of a norm must be positive." );
//   mat_err( vec->cols != 1, "Error (mat_norm): Input must be a column vector."     );

//   ushort i, r;
//   float norm, val, root;

//   r = vec->rows;
//   norm = 0.0f;
//   val = 0.0f;

//   if( p==0 ) {
//     for( i=1; i<=r; i++ ) {
//       val = fabs( mat_get( vec, i, 1 ) );
//       if( val > norm )  norm = val;
//     }
//   }

//   else {
//     for( i=1; i<=r; i++ ) {
//       val = fabs( mat_get( vec, i, 1 ) );
//       val = pow( val, p );
//       norm += val;
//     }
//     root = 1.0f / (float) p;
//     norm = pow( norm, root );
//   }

//   return norm;
// }




/*******************************************************************************
* float mat_mag ( matrix* vec )
* Returns the magnitude (Euclidean norm) of a column vector.
*******************************************************************************/
// float mat_mag ( matrix* vec ) {
//   mat_err( vec->cols != 1, "Error (mat_mag): Input must be a column vector." );
//   return mat_norm( vec, 2 );
// }




/*******************************************************************************
* matrix* mat_uvec ( matrix* vec )
* Returns an equivalent unit vector.
*******************************************************************************/
// matrix* mat_uvec ( matrix* vec ) {

//   mat_err( vec->cols != 1, "Error (mat_uvec): Input must be a column vector." );

//   ushort i, r;
//   float mag, val;
//   matrix* uvec;

//   r = vec->rows;
//   mag = mat_mag(vec);
//   uvec = mat_init(r,1);

//   if( mag==0 )  return uvec;
//   else {
//     for( i=1; i<=r; i++ ) {
//       val = mat_get( vec, i, 1 );
//       val /= mag;
//       mat_set( uvec, i, 1, val );
//     }
//   }

//   return uvec;
// }




/*******************************************************************************
* matrix* mat_proj ( matrix* u, matrix* v )
* Returns the projection of vector u onto vector v.
*******************************************************************************/
// matrix* mat_proj ( matrix* u, matrix* v ) {

//   mat_err( u->cols != 1 || v->cols != 1, "Error (mat_proj): Inputs must be column vectors."         );
//   mat_err( u->rows != v->rows,           "Error (mat_proj): Input vectors must be the same height." );

//   matrix* proj;
//   float mag, ratio;

//   mag = mat_mag(v);

//   if( mag==0 )  proj = mat_init( u->rows, 1 );
//   else {
//     ratio = mat_dot( u, v ) / mat_dot( v, v );
//     proj = mat_scale( v, ratio );
//   }

//   return proj;
// }



