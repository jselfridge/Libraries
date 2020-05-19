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
* void mat_LU ( matrix* mat, matrix** L, matrix** U )
* Solves for the LU decomposition of a matrix (if it exists).
*******************************************************************************/
void mat_LU ( matrix* mat, matrix** L, matrix** U ) {

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
}




/*******************************************************************************
* void mat_LDU ( matrix* mat, matrix** L, matrix** U )
* Solves for the LDU decomposition of a matrix (if it exists).
*******************************************************************************/
void mat_LDU ( matrix *mat, matrix **L, matrix **D, matrix **U ) {

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
}




/*******************************************************************************
* void mat_QR ( matrix* mat, matrix** Q, matrix** R )
* Solves for the QR decomposition of a matrix.
*******************************************************************************/
void mat_QR ( matrix* mat, matrix** Q, matrix** R ) {

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
}




/*******************************************************************************
* matrix* mat_tri2vec ( matrix* tri )
* Maps the lower triangular elements of a matrix into a vector array.
*******************************************************************************/
matrix* mat_tri2vec ( matrix* tri ) {

  mat_err( ( tri->rows != tri->cols ), "Error (mat_tri2vec): Matrix must be square." );

  matrix* vec = mat_init( ( tri->rows * (tri->rows+1) ) / 2, 1 );

  float* i = vec->data;
  for( uint r=0; r<tri->rows; r++ ) {
    for( uint c=0; c<=r; c++ ) {
      *(i++) = *( tri->data + r*tri->cols + c );
    }
  }

  return vec;
}




/*******************************************************************************
* matrix* mat_vec2tri ( matrix* vec )
* Maps a vector array into the lower triangular elements of a matrix.
*******************************************************************************/
matrix* mat_vec2tri ( matrix* vec ) {

  uint d = 0;
  uint n = 0;
  while( n<vec->rows ) {
    d++;
    n = ( d * (d+1) ) / 2;
    mat_err( ( n>vec->rows ), "Error (mat_vec2tri): Vector must satisfy n=(d*(d+1))/2 relationship." );
  }

  matrix* tri = mat_init( d, d );

  float* i = vec->data;
  for( uint r=0; r<d; r++ ) {
    for( uint c=0; c<=r; c++ ) {
      *( tri->data + r*d + c ) = *(i++);
    }
  }

  return tri;
}




/*******************************************************************************
* void mat_chol ( double a[], int n, int nn, double u[], int *nullty, int *ifault )
* Determines the cholesky decomposition for a positive definite symmetric matrix.
*******************************************************************************/
void mat_chol ( double a[], int n, int nn, double u[], int *nullty, int *ifault ) {

  mat_err( (n<=0), "Error (mat_chol): Matrix size must be positive." );

  const float eps = 6.0E-08;    // Based on float precision

  *ifault = 0;
  *nullty = 0;

  if( nn < ( n * ( n + 1 ) ) / 2 ) {
    *ifault = 3;
    return;
  }

  uint j  = 1;
  uint k  = 0;
  uint ii = 0;

  // Factorize column by column, ICOL = column number
  for( uint icol=1; icol<=n; icol++ ) {

    ii += icol;
    double x = eps * eps * a[ii-1];
    double w = 0.0;
    uint l = 0;
    uint kk = 0;

    // IROW = row number within column ICOL
    for( uint irow=1; irow<=icol; irow++ ) {

      kk += irow;
      k++;
      w = a[k-1];
      uint m = j;

      for( uint i=1; i<irow; i++ ) {
        l++;
        w -= u[l-1] * u[m-1];
        m++;
      }

      l++;

      if( irow == icol )  break;

      if( u[l-1] != 0.0 ) {  u[k-1] = w / u[l-1];  }
      else {
        u[k-1] = 0.0;
        if( fabs( x * a[k-1] ) < w * w ) {  *ifault = 2;  return;  }
      }
      
    }

    //End of row, estimate relative accuracy of diagonal element
    if( fabs(w) <= fabs( eps * a[k-1] ) ) {
      u[k-1] = 0.0;
      *nullty = *nullty +1;
    }
    else {
      if ( w<0.0 ) {  *ifault = 2;  return;  }
      u[k-1] = sqrt(w);
    }

    j += icol;

  }

  return;
}



