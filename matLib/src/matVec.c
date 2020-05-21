/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matVec.c
* Source code for matrix vector functions within the 'matLib' library.
*
*******************************************************************************/
#include "../inc/matVec.h"




/*******************************************************************************
* matrix* mat_skew ( matrix* V )
* Returns the cross product skew symmetric matrix of a 3 element column vector.
*******************************************************************************/
matrix* mat_skew ( matrix* V ) {

  mat_err( ( V->r != 3 || V->c != 1 ), "Error (mat_skew): Input vector must be [3x1]." );

  matrix* W = mat_init( 3, 3 );

  float* i = V->e;
  *(W->e+7) = (*i);
  *(W->e+5) = (*i) * (-1.0);
  i++;
  *(W->e+2) = (*i);
  *(W->e+6) = (*i) * (-1.0);
  i++;
  *(W->e+3) = (*i);
  *(W->e+1) = (*i) * (-1.0);

  return W;
}




/*******************************************************************************
* matrix* mat_sskew ( matrix* V )
* Returns the double cross product skew symmetric matrix of a 3 element column vector.
*******************************************************************************/
matrix* mat_sskew ( matrix* V ) {

  mat_err( ( V->r != 3 || V->c != 1 ), "Error (mat_sskew): Input vector must be [3x1]." );

  matrix* W = mat_init( 3, 3 );

  float x2 = *(V->e  ) * *(V->e  );
  float y2 = *(V->e+1) * *(V->e+1);
  float z2 = *(V->e+2) * *(V->e+2);

  float xy = *(V->e  ) * *(V->e+1);
  float xz = *(V->e  ) * *(V->e+2);
  float yz = *(V->e+1) * *(V->e+2);

  *(W->e  ) = -y2-z2;  *(W->e+1) =     xy;  *(W->e+2) =     xz;
  *(W->e+3) =     xy;  *(W->e+4) = -x2-z2;  *(W->e+5) =     yz;
  *(W->e+6) =     xz;  *(W->e+7) =     yz;  *(W->e+8) = -x2-y2;

  return W;
}




/*******************************************************************************
* matrix* mat_cross ( matrix* A, matrix* B )
* Returns the cross product of two three-element vectors.
*******************************************************************************/
matrix* mat_cross ( matrix* A, matrix* B ) {

  mat_err( ( A->r != 3 || A->c != 1 ), "Error (mat_cross): Vector A must be [3x1]." );
  mat_err( ( B->r != 3 || B->c != 1 ), "Error (mat_cross): Vector B must be [3x1]." );

  matrix* W = mat_init( 3, 1 );

  *(W->e  ) = *(A->e+1) * *(B->e+2) - *(A->e+2) * *(B->e+1);
  *(W->e+1) = *(A->e+2) * *(B->e  ) - *(A->e  ) * *(B->e+2);
  *(W->e+2) = *(A->e  ) * *(B->e+1) - *(A->e+1) * *(B->e  );

  return W;
}




/*******************************************************************************
* float mat_dot ( matrix* A, matrix* B )
* Returns the dot product of two arbitrary length vectors.
*******************************************************************************/
float mat_dot ( matrix* A, matrix* B ) {

  mat_err( ( A->c != 1 || B->c != 1 ), "Error (mat_dot): Requires column vector inputs."   );
  mat_err( ( A->r != B->r ),           "Error (mat_dot): Vectors must be the same height." );

  float dot = 0.0;
  for( uint i=0; i<A->r; i++ )  dot += *(A->e+i) * *(B->e+i);

  return dot;
}




/*******************************************************************************
* float mat_mag ( matrix* V )
* Returns the magnitude (Euclidean norm) of a column vector.
*******************************************************************************/
float mat_mag ( matrix* V ) {

  mat_err( ( V->c != 1 ), "Error (mat_mag): Input must be a column vector." );

  float mag = 0.0;
  for( uint i=0; i<V->r; i++ )  mag += *(V->e+i) * *(V->e+i);

  return sqrtf(mag);
}




/*******************************************************************************
* float mat_norm ( matrix* V, uint p )
* Returns the norm of a vector of a specified degree (infinity norm when p=0).
*******************************************************************************/
float mat_norm ( matrix* V, uint p ) {

  mat_err( ( V->c != 1 ), "Error (mat_norm): Input must be a column vector."     );

  switch(p) {

    case 0 : {
      float norm = 0.0;
      for( uint i=0; i<V->r; i++ ) {
        float val = fabsf( *(V->e+i) );
        if( val > norm )  norm = val;
      }
      return norm;
    }

    case 1 : {
      float norm = 0.0;
      for( uint i=0; i<V->r; i++ )  norm += fabsf( *(V->e+i) );
      return norm;
    }

    case 2 : {
      return mat_mag(V);
    }

    default : {
      float norm = 0.0;
      for( uint i=0; i<V->r; i++ ) {
        norm += powf( fabsf( *(V->e+i) ), (float)p );
      }
      return powf( norm, ( 1.0 / (float)p ) );
    }

  }

}




/*******************************************************************************
* matrix* mat_uvec ( matrix* V )
* Returns an equivalent unit vector.
*******************************************************************************/
matrix* mat_uvec ( matrix* V ) {

  mat_err( ( V->c != 1 ), "Error (mat_uvec): Input must be a column vector." );

  float mag = mat_mag(V);

  if(!mag)  return V;

  matrix* uvec = mat_init( V->r, 1 );

  memcpy( uvec->e, V->e, V->r * sizeof(float) );
  for( uint i=0; i<V->r; i++ )  *(uvec->e+i) /= mag;

  return uvec;
}




/*******************************************************************************
* matrix* mat_proj ( matrix* U, matrix* V )
* Returns the projection of vector U onto vector V.
*******************************************************************************/
matrix* mat_proj ( matrix* U, matrix* V ) {

  mat_err( ( U->c != 1 || V->c != 1 ), "Error (mat_proj): Inputs must be column vectors."         );
  mat_err( ( U->r != V->r ),           "Error (mat_proj): Input vectors must be the same height." );

  if( !mat_mag(V) )  return V;

  matrix* W = mat_init( V->r, 1 );
  W = mat_scale( V, ( mat_dot( U, V ) / mat_dot( V, V ) ) );

  return W;
}



