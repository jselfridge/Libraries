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
* void mat_LU ( matrix* mat, matrix** L, matrix** U )
* Solves for the LU decomposition of a matrix (if it exists).
*******************************************************************************/
/*void mat_LU ( matrix* mat, matrix** L, matrix** U ) {

  *U = mat_copy(mat);
  *L = mat_init( mat->rows, mat->rows );

  matrix* row = mat_init( 1, mat->cols );

  uint n = mat->rows < mat->cols ? mat->rows : mat->cols;

  uint i = 1;
  uint j = 1;
  uint m = 0;

  for( uint p=1; p<=n; p++ ) {

    float pivot = mat_get( *U, i, j );

    if(!pivot) {

      for( uint k=i+1; k<=mat->rows; k++ ) {
        float val = mat_get( *U, k, j );
        mat_err( ( val != 0 ), "Error (mat_LU): The LU decomposition does not exist." );
      }

      j++;
      m++;
      p--;

    }

    else {

      for( uint k=i; k<=mat->rows; k++ ) {
        float val = mat_get( *U, k, j ) / pivot;
        mat_set( *L, k, j-m, val );
      }

      for( uint k=i+1; k<=mat->rows; k++ ) {
        float scale = -mat_get( *U, k, j) / pivot;
        row = mat_getr( *U, i );
        row = mat_scale( row, scale );
        row = mat_add( row, mat_getr( *U, k ) );
        mat_setr( *U, k, row );
      }

      i++;
      j++;

    }

  }

  for( uint p=1; p<=mat->rows; p++ )  mat_set( *L, p, p, 1.0 );

  mat_clear(row);

  return;
}*/




/*******************************************************************************
* void mat_LDU ( matrix* mat, matrix** L, matrix** U )
* Solves for the LDU decomposition of a matrix (if it exists).
*******************************************************************************/
/*void mat_LDU ( matrix *mat, matrix **L, matrix **D, matrix **U ) {

  mat_LU( mat, &*L, &*U );
  *D = mat_init( mat->rows, mat->rows );

  matrix* row = mat_init( 1, mat->cols );

  uint i = 1;
  uint j = 1;

  for( uint k=1; k<=mat->rows; k++ ) {

    if( k>mat->cols ) {
      while( k<=mat->rows ) {  mat_set( *D, k, k, 1.0 );  k++;  }
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
}*/




/*******************************************************************************
* void mat_QR ( matrix* mat, matrix** Q, matrix** R )
* Solves for the QR decomposition of a matrix.
*******************************************************************************/
/*void mat_QR ( matrix* mat, matrix** Q, matrix** R ) {

  mat_err( ( mat->rows < mat->cols ), "Error (mat_QR): Input matrix must be square or tall." );

  *Q = mat_init( mat->rows, mat->cols );
  *R = mat_init( mat->cols, mat->cols );

  matrix* A    = mat_copy(mat);
  matrix* Acol = mat_init( mat->rows, 1 );
  matrix* Qcol = mat_init( mat->rows, 1 );

  for( uint i=1; i<=mat->cols; i++ ) {

    Acol = mat_getc( A, i );
    Qcol = mat_copy(Acol);

    for( uint j=1; j<i; j++ )  Qcol = mat_sub( Qcol, mat_proj( Acol, mat_getc( *Q, j ) ) );

    mat_setc( *Q, i, mat_uvec(Qcol) );

  }

  *R = mat_mul( mat_trans(*Q), A );

  mat_clear(A);
  mat_clear(Acol);
  mat_clear(Qcol);

  return;
}*/




/*******************************************************************************
* void mat_chol ( matrix* A, uint n, matrix** U, uint *nullty, uint *ifault )
* Determines the cholesky decomposition for a positive definite symmetric matrix.
*******************************************************************************/
/*void mat_chol ( matrix* A, uint n, matrix** U, uint *nullty, uint *ifault ) {

  mat_err( (!n),                       "Error (mat_chol): Matrix size must be positive." );
  mat_err( ( A->rows != (n*(n+1))/2 ), "Error (mat_chol): Inconsistent dimensions."      );

  *ifault = 0;
  *nullty = 0;

  const float eps = 6.0E-08;

  uint i = 0;
  uint j = 0;

  // Loop through each row
  for( uint r=0; r<n; r++ ) {

    j += r;
    float tol = eps * eps * *(A->data+j);
    float w = 0.0;
    uint l = 0;

    // Loop through each column within row
    for( uint c=0; c<=r; c++ ) {

      uint m = j;
      w = *(A->data+i);
      i++;

      // Iterate through each element within row
      for( uint k=0; k<c; k++ ) {

        w -= *((*U)->data+l) * *((*U)->data+m);
        l++;
        m++;

      }

      if( r == c )  break;

      if( *((*U)->data+l) != 0.0 ) {  *((*U)->data+i-1) = w / *((*U)->data+l);  }
      else {
        *((*U)->data+i-1) = 0.0;
        if( fabs( tol * *(A->data+i-1) ) < w*w ) {  *ifault = 2;  return;  }
      }

      l++;

    }

    //End of row, estimate relative accuracy of diagonal element
    if( fabs(w) <= fabs( eps * *(A->data+i-1) ) ) {
      *((*U)->data+i-1) = 0.0;
      (*nullty)++;
    }
    else {
      if ( w<0.0 ) {  *ifault = 2;  return;  }
      *((*U)->data+i-1) = sqrtf(w);
    }

  }

  return;
}*/



