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
matrix* mat_cross ( matrix* vecA, matrix* vecB ) {

  mat_err( ( vecA->rows != 3 || vecA->cols != 1 ), "Error (mat_cross): Vector A must be [3x1]." );
  mat_err( ( vecB->rows != 3 || vecB->cols != 1 ), "Error (mat_cross): Vector B must be [3x1]." );

  matrix* out = mat_init( 3, 1 );
  *(out->data  ) = *(vecA->data+1) * *(vecB->data+2) - *(vecA->data+2) * *(vecB->data+1);
  *(out->data+1) = *(vecA->data+2) * *(vecB->data  ) - *(vecA->data  ) * *(vecB->data+2);
  *(out->data+2) = *(vecA->data  ) * *(vecB->data+1) - *(vecA->data+1) * *(vecB->data  );

  return out;
}




/*******************************************************************************
* float mat_dot ( matrix* vecA, matrix* vecB )
* Returns the dot product of two arbitrary length vectors.
*******************************************************************************/
float mat_dot ( matrix* vecA, matrix* vecB ) {

  mat_err( ( vecA->cols != 1 || vecB->cols != 1 ), "Error (mat_dot): Requires column vector inputs."   );
  mat_err( ( vecA->rows != vecB->rows ),           "Error (mat_dot): Vectors must be the same height." );

  float out = 0.0;
  for( ushort i=0; i<vecA->rows; i++ )  out += *(vecA->data+i) * *(vecB->data+i);

  return out;
}




/*******************************************************************************
* float mat_norm ( matrix* vec, uint p )
* Returns the norm of a vector of a specified degree (infinity norm when p=0).
*******************************************************************************/
float mat_norm ( matrix* vec, uint p ) {

  mat_err( ( vec->cols != 1 ), "Error (mat_norm): Input must be a column vector."     );

  if( p==0 ) {
    float norm = 0.0;
    for( ushort i=0; i<vec->rows; i++ ) {
      float val = fabs( *(vec->data+i) );
      if( val > norm )  norm = val;
    }
    return norm;
  }

  float norm = 0.0;
  for( ushort i=0; i<vec->rows; i++ ) {
    norm += pow( fabs( *(vec->data+i) ), p );
  }
  norm = pow( norm, ( 1.0 / (float)p ) );

  return norm;
}




/*******************************************************************************
* matrix* mat_uvec ( matrix* vec )
* Returns an equivalent unit vector.
*******************************************************************************/
matrix* mat_uvec ( matrix* vec ) {

  mat_err( ( vec->cols != 1 ), "Error (mat_uvec): Input must be a column vector." );

  float mag = mat_mag(vec);

  if(!mag)  return vec;

  matrix* uvec = mat_init( vec->rows, 1 );
  memcpy( uvec->data, vec->data, vec->rows * sizeof(float) );
  for( ushort i=0; i<vec->rows; i++ )  *(uvec->data+i) /= mag;

  return uvec;
}




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




/*******************************************************************************
* !!! REPLACED !!!   float mat_mag ( matrix* vec )
* Returns the magnitude (Euclidean norm) of a column vector.
*******************************************************************************/
// float mat_mag ( matrix* vec ) {
//   mat_err( vec->cols != 1, "Error (mat_mag): Input must be a column vector." );
//   return mat_norm( vec, 2 );
// }



