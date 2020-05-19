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
* void mat_tri2vec ( matrix* tri )
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
* void mat_vec2tri ( matrix* vec )
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














// # include <math.h>
// # include <stdio.h>
// # include <stdlib.h>
// # include <time.h>

// # include "asa006.h"

// /******************************************************************************/

void cholesky ( double a[], int n, int nn, double u[], int *nullty, 
  int *ifault )

// /******************************************************************************/
/*

  Original source:
    Parent directory:    https://people.sc.fsu.edu/~jburkardt/c_src/c_src.html
    Full URL:            https://people.sc.fsu.edu/~jburkardt/c_src/asa006/cholesky.c

  Purpose:

    CHOLESKY computes the Cholesky factorization of a PDS matrix.

  Discussion:

    For a positive definite symmetric matrix A, the Cholesky factor U
    is an upper triangular matrix such that A = U' * U.

    This routine was originally named "CHOL", but that conflicted with
    a built in MATLAB routine name.

    The missing initialization "II = 0" has been added to the code.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    13 January 2017

  Author:

    Original FORTRAN77 version by Michael Healy.
    Modifications by AJ Miller.
    C version by John Burkardt.

  Reference:

    Michael Healy,
    Algorithm AS 6:
    Triangular decomposition of a symmetric matrix,
    Applied Statistics,
    Volume 17, Number 2, 1968, pages 195-197.

  Parameters:

    Input, double A((N*(N+1))/2), a positive definite matrix 
    stored by rows in lower triangular form as a one dimensional array, 
    in the sequence
    A(1,1),
    A(2,1), A(2,2),
    A(3,1), A(3,2), A(3,3), and so on.

    Input, int N, the order of A.

    Input, int NN, the dimension of the array used to store A, 
    which should be at least (N*(N+1))/2.

    Output, double U((N*(N+1))/2), an upper triangular matrix,
    stored by columns, which is the Cholesky factor of A.  The program is
    written in such a way that A and U can share storage.

    Output, int NULLTY, the rank deficiency of A.  If NULLTY is zero,
    the matrix is judged to have full rank.

    Output, int IFAULT, an error indicator.
    0, no error was detected;
    1, if N < 1;
    2, if A is not positive semi-definite.
    3, if NN < (N*(N+1))/2.

  Local Parameters:

    Local, double R8_EPSILON, should be set equal to the smallest positive
    value such that 1.0 + R8_EPSILON is calculated as being greater than 1.0 in the
    accuracy being used.
*/
{

  int i;
  int icol;
  int ii;
  int irow;
  int j;
  int k;
  int kk;
  int l;
  int m;
  const double r8_epsilon = 2.220446049250313E-016;
  double w;
  double x;

  *ifault = 0;
  *nullty = 0;

  if ( n <= 0 )
  {
    *ifault = 1;
    return;
  }

  if ( nn < ( n * ( n + 1 ) ) / 2 )
  {
    *ifault = 3;
    return;
  }

  j = 1;
  k = 0;
  ii = 0;
/*
  Factorize column by column, ICOL = column number.
*/
  for ( icol = 1; icol <= n; icol++ )
  {
    ii = ii + icol;
    x = r8_epsilon * r8_epsilon * a[ii-1];
    l = 0;
    kk = 0;
/*
  IROW = row number within column ICOL.
*/
    for ( irow = 1; irow <= icol; irow++ )
    {
      kk = kk + irow;
      k = k + 1;
      w = a[k-1];
      m = j;

      for ( i = 1; i < irow; i++ )
      {
        l = l + 1;
        w = w - u[l-1] * u[m-1];
        m = m + 1;
      }

      l = l + 1;

      if ( irow == icol ) 
      {
        break;
      }

      if ( u[l-1] != 0.0 )
      {
        u[k-1] = w / u[l-1];
      }
      else
      {
        u[k-1] = 0.0;

        if ( fabs ( x * a[k-1] ) < w * w )
        {
          *ifault = 2;
          return;
        }
      }
    }
/*
  End of row, estimate relative accuracy of diagonal element.
*/
    if ( fabs ( w ) <= fabs ( r8_epsilon * a[k-1] ) )
    {
      u[k-1] = 0.0;
      *nullty = *nullty + 1;
    }
    else
    {
      if ( w < 0.0 )
      {
        *ifault = 2;
        return;
      }
      u[k-1] = sqrt ( w );
    }
    j = j + icol;
  }
  return;
}



