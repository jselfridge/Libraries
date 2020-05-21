/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matDecomp.c
* Source code for performing matrix decompositions within the 'matLib' library.
*
*******************************************************************************/
#include "../inc/matDecomp.h"




/*******************************************************************************
* matrix* mat_tri2vec ( matrix* tri )
* Maps the lower triangular elements of a matrix into a vector structure.
*******************************************************************************/
matrix* mat_tri2vec ( matrix* tri ) {

  mat_err( ( tri->r != tri->c ), "Error (mat_tri2vec): Matrix must be square." );

  matrix* vec = mat_init( ( tri->r * (tri->r+1) ) / 2, 1 );

  float* i = vec->e;
  for( uint r=0; r<tri->r; r++ ) {
    for( uint c=0; c<=r; c++ ) {
      *(i++) = *( tri->e + r*tri->c + c );
    }
  }

  return vec;
}




/*******************************************************************************
* float* mat_tri2arr ( matrix* tri )
* Maps the lower triangular elements of a matrix into a standard array.
*******************************************************************************/
float* mat_tri2arr ( matrix* tri ) {

  mat_err( ( tri->r != tri->c ), "Error (mat_tri2arr): Matrix must be square." );

  const uint d = ( tri->r * (tri->r+1) ) / 2;
  float* arr = (float*) malloc( d * sizeof(float) );

  float* p = arr;
  for( uint r=0; r<tri->r; r++ ) {
    for( uint c=0; c<=r; c++ ) {
      *(p++) = *( tri->e + r*tri->c + c );
    }
  }

  return arr;
}




/*******************************************************************************
* matrix* mat_vec2tri ( matrix* vec )
* Maps a vector structure into the lower triangular elements of a matrix.
*******************************************************************************/
matrix* mat_vec2tri ( matrix* vec ) {

  uint n = 0;
  uint d = 0;
  while( d<vec->r ) {
    n++;
    d = ( n * (n+1) ) / 2;
    mat_err( ( d>vec->r ), "Error (mat_vec2tri): Vector must satisfy d=(n*(n+1))/2 relationship." );
  }

  matrix* tri = mat_init( n, n );

  float* i = vec->e;
  for( uint r=0; r<n; r++ ) {
    for( uint c=0; c<=r; c++ ) {
      *( tri->e + r*n + c ) = *(i++);
    }
  }

  return tri;
}




/*******************************************************************************
* matrix* mat_arr2tri ( float* arr, unit n )
* Maps a standard array into the lower triangular elements of a matrix.
*******************************************************************************/
matrix* mat_arr2tri ( float* arr, uint n ) {

  matrix* tri = mat_init( n, n );

  float* p = arr;
  for( uint r=0; r<n; r++ ) {
    for( uint c=0; c<=r; c++ ) {
      *( tri->e + r*n + c ) = *(p++);
    }
  }

  return tri;
}




/*******************************************************************************
* void mat_LU ( matrix* A, matrix** L, matrix** U )
* Solves for the LU decomposition of a matrix (if it exists).
*******************************************************************************/
void mat_LU ( matrix* A, matrix** L, matrix** U ) {

  *U = mat_copy(A);
  *L = mat_init( A->r, A->r );

  matrix* row = mat_init( 1, A->c );

  uint n = A->r < A->c ? A->r : A->c;

  const float eps = 1.0E-30;

  uint i = 0;
  uint j = 0;
  uint m = 0;

  for( uint p=0; p<n; p++ ) {

    float pivot = *( (*U)->e + i*(*U)->c + j );

    if( fabsf(pivot) < eps ) {

      for( uint k=i; k<A->r-1; k++ ) {
        float val = *( (*U)->e + k*(*U)->c + j );
        mat_err( ( val != 0 ), "Error (mat_LU): The LU decomposition does not exist." );
      }

      j++;
      m++;
      p--;

    }

    else {

      for( uint k=i; k<A->r; k++ ) {
        float val = *( (*U)->e + k*(*U)->c + j ) / pivot;
        *( (*L)->e + k*(*L)->c + j-m ) = val;
      }

      for( uint k=i+1; k<A->r; k++ ) {
        float scale = - *( (*U)->e + k*(*U)->c + j ) / pivot;
        row = mat_getr( *U, i+1 );
        row = mat_scale( row, scale );
        row = mat_add( row, mat_getr( *U, k+1 ) );
        mat_setr( *U, k+1, row );
      }

      i++;
      j++;

    }

  }

  for( uint p=0; p<A->r; p++ )  *( (*L)->e + p*(*L)->c + p ) = 1.0;

  mat_clear(row);

  return;
}




/*******************************************************************************
* void mat_LDU ( matrix* A, matrix** L, matrix** D, matrix** U )
* Solves for the LDU decomposition of a matrix (if it exists).
*******************************************************************************/
void mat_LDU ( matrix* A, matrix** L, matrix** D, matrix** U ) {

  mat_LU( A, &*L, &*U );
  *D = mat_init( A->r, A->r );

  matrix* row = mat_init( 1, A->c );

  uint i = 1;
  uint j = 1;

  for( uint k=1; k<=A->r; k++ ) {

    if( k>A->c ) {
      while( k<=A->r ) {  mat_set( *D, k, k, 1.0 );  k++;  }
      break;
    }

    float pivot = mat_get( *U, i, j );

    while(!pivot) {
      j++;
      pivot = mat_get( *U, i, j );
    }

    row = mat_getr( *U, i );
    row = mat_scale( row, 1.0/pivot );

    mat_setr( *U, i, row );
    mat_set( *D, k, k, pivot );

    i++;
    j++;

  }

  mat_clear(row);

  return;
}




/*******************************************************************************
* void mat_QR ( matrix* A, matrix** Q, matrix** R )
* Solves for the QR decomposition of a matrix.
*******************************************************************************/
void mat_QR ( matrix* A, matrix** Q, matrix** R ) {

  mat_err( ( A->r < A->c ), "Error (mat_QR): Input matrix must be square or tall." );

  *Q = mat_init( A->r, A->c );
  *R = mat_init( A->c, A->c );

  matrix* Acol = mat_init( A->r, 1 );
  matrix* Qcol = mat_init( A->r, 1 );

  for( uint i=1; i<=A->c; i++ ) {

    Acol = mat_getc( A, i );
    Qcol = mat_copy(Acol);

    for( uint j=1; j<i; j++ )  Qcol = mat_sub( Qcol, mat_proj( Acol, mat_getc( *Q, j ) ) );

    mat_setc( *Q, i, mat_uvec(Qcol) );

  }

  *R = mat_mul( mat_trans(*Q), A );

  mat_clear(Acol);
  mat_clear(Qcol);

  return;
}




/*******************************************************************************
* void mat_chol ( float a[], uint n, float u[], uint *nullity, uint *err )
* Determines the cholesky decomposition for a positive definite symmetric matrix.
*******************************************************************************/
void mat_chol ( float a[], uint n, float u[], uint *nullity, uint *err ) {

  mat_err( (!n), "Error (mat_chol): Matrix size must be positive." );

  *nullity = 0;
  *err = 0;

  const float eps = 6.0E-08;

  uint i = 0;
  uint j = 0;

  // Loop through each row
  for( uint r=0; r<n; r++ ) {

    j += r;
    float tol = eps * eps * a[j];
    float w = 0.0;
    uint l = 0;

    // Loop through each column within row
    for( uint c=0; c<=r; c++ ) {

      uint m = j;
      w = a[i];
      i++;

      // Iterate through each element within row
      for( uint k=0; k<c; k++ ) {

        w -= u[l] * u[m];
        l++;
        m++;

      }

      if( r == c )  break;

      if( u[l] != 0.0 ) {  u[i-1] = w / u[l];  }
      else {
        u[i-1] = 0.0;
        if( fabs( tol * a[i-1] ) < w*w ) {  *err = 2;  return;  }
      }

      l++;

    }

    //End of row, estimate relative accuracy of diagonal element
    if( fabs(w) <= fabs( eps * a[i-1] ) ) {
      u[i-1] = 0.0;
      (*nullity)++;
    }
    else {
      if ( w<0.0 ) {  *err = 2;  return;  }
      u[i-1] = sqrtf(w);
    }

  }

  return;
}



