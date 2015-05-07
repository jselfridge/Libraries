
//============================================================
//  matVec.c
//  Justin M Selfridge
//============================================================
#include "matLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_skew
//  Returns skew symmetric matrix of a 3 element column vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_skew ( matrix* vec )  {

  mat_err( vec->rows!=3 || vec->cols!=1, "Error (mat_skew): Input vector must be [3x1]." );
  matrix*  skew = mat_init(3,3);

  double x = mat_get(vec,1,1);  mat_set(skew,3,2,x);  mat_set(skew,2,3,-x);
  double y = mat_get(vec,2,1);  mat_set(skew,1,3,y);  mat_set(skew,3,1,-y);
  double z = mat_get(vec,3,1);  mat_set(skew,2,1,z);  mat_set(skew,1,2,-z);

  return skew;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_sskew
//  Returns skew skew symmetric matrix of a 3 element column vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_sskew ( matrix* vec )  {

  mat_err( vec->rows!=3 || vec->cols!=1, "Error (mat_sskew): Input vector must be [3x1]." );
  matrix* sskew = mat_init(3,3);

  sskew = mat_skew(vec);
  sskew = mat_pow(sskew,2);

  return sskew;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_cross
//  Returns cross product of two three-element vectors.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_cross ( matrix* vecA, matrix* vecB )  {

  mat_err( vecA->rows!=3 || vecA->cols!=1, "Error (mat_cross): Vector A must be [3x1]."  );
  mat_err( vecB->rows!=3 || vecB->cols!=1, "Error (mat_cross): Vector B must be [3x1]."  );

  matrix* out = mat_init(3,1);
  out = mat_mul( mat_skew(vecA), vecB );

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_dot
//  Returns dot product of two arbitrary length vectors.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double mat_dot ( matrix* vecA, matrix* vecB )  {

  mat_err( vecA->cols!=1 || vecB->cols!=1, "Error (mat_dot): Requires column vector inputs."    );
  mat_err( vecA->rows != vecB->rows,       "Error (mat_dot): Vectors must be the same height."  );

  int i;
  double out = 0.0;
  for ( i=1; i<= vecA->rows; i++ )  out += mat_get(vecA,i,1) * mat_get(vecB,i,1);

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_norm
//  Returns the norm of a vector of a specified degree.  Returns
//  the infinity norm when p=0.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double mat_norm ( matrix* vec, int p )  {

  mat_err( p<0,          "Error (mat_norm): Degree of a norm must be positive."  );
  mat_err( vec->cols!=1, "Error (mat_norm): Input must be a column vector."      );

  int i;
  double  norm  = 0.0;
  double  val   = 0.0;
  int r = vec->rows;

  if ( p==0 ) {
    for ( i=1; i<=r; i++ ) {
      val = fabs( mat_get(vec,i,1) );
      if ( val > norm )  norm = val;
    }
  }

  else {
    for ( i=1; i<=r; i++ ) {
      val = fabs( mat_get(vec,i,1) );
      val = pow( val, p );
      norm += val;
    }
    double root = 1.0 / (double)p;
    norm = pow( norm, root );
  }

  return norm;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_mag
//  Returns the magnitude (Euclidean norm) of a column vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double mat_mag ( matrix* vec )  {
  mat_err( vec->cols!=1, "Error (mat_mag): Input must be a column vector." );
  return mat_norm(vec,2);
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_uvec
//  Returns an equivalent unit vector of a column vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_uvec ( matrix* vec )  {

  mat_err( vec->cols!=1, "Error (mat_uvec): Input must be a column vector." );

  int i, r; 
  double mag, val;

  r = vec->rows;
  mag = mat_mag(vec);

  matrix* uvec = mat_init(r,1);

  if ( mag==0 )  return uvec; 
  else {
    for ( i=1; i<=r; i++ ) {
      val = mat_get(vec,i,1);
      val /= mag;
      mat_set( uvec,i,1, val );
    }
  }

  return uvec;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_proj
//  Returns the projection of vector u onto vector v.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_proj ( matrix* u, matrix* v )  {

  mat_err( u->cols!=1 || v->cols!=1, "Error (mat_proj): Inputs must be column vectors."          );
  mat_err( u->rows != v->rows,       "Error (mat_proj): Input vectors must be the same height."  );

  matrix* proj;
  double  ratio;
  double  mag = mat_mag(v);

  if ( mag==0 )  proj = mat_init(u->rows,1);
  else {
    ratio = mat_dot(v,u) / pow(mag,2);
    proj = mat_scale(v,ratio);
  }

  return proj;
}



