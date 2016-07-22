

#include "matLib.h"


/**
 *  mat_LU
 *  Solves for the LU decomposition of a matrix (if it exists).
 */
void mat_LU ( matrix *mat, matrix **L, matrix **U )  {

  uint i, j, k, n, m, p, r, c;
  double pivot, val, scale;
  matrix *row;

  r = mat->rows;
  c = mat->cols;

  n = r<c ? r : c;
  row = mat_init( 1, c );

  i = 1;
  j = 1;
  m = 0;

  *U = mat_copy(mat);
  *L = mat_init( r, r );

  for ( p=1; p<=n; p++ )  {

    pivot = mat_get( *U, i, j );

    if(!pivot) {

      for ( k=i+1; k<=r; k++ )  {
        val = mat_get( *U, k, j );
        mat_err( val != 0, "Error (mat_LU): The LU decomposition does not exist." );
      }

      j++;
      m++;
      p--;

    }

    else {

      for ( k=i; k<=r; k++ )  {
        val = mat_get( *U, k, j ) / pivot;
        mat_set( *L, k, j-m, val );
      }

      for ( k=i+1; k<=r; k++ )  {
        scale = -mat_get( *U, k, j) / pivot;
        row = mat_getr( *U, i );
        row = mat_scale( row, scale );
        row = mat_add( row, mat_getr( *U, k ) );
        mat_setr( *U, k, row );
      }

      i++;
      j++;

    }
  }

  while ( p<=r ) {  mat_set( *L, p, p, 1.0 );  p++;  }

  mat_clear(row);

  return;
}


/**
 *  mat_LDU
 *  Solves for the LDU decomposition of a matrix (if it exists).
 */
void mat_LDU ( matrix *mat, matrix **L, matrix **D, matrix **U )  {

  uint i, j, k, r, c;
  double pivot;
  matrix *row;

  r = mat->rows;
  c = mat->cols;
  row = mat_init( 1, c );

  mat_LU( mat, &*L, &*U );
  *D = mat_init( r, r );

  i = 1;
  j = 1;

  for ( k=1; k<=r; k++ )  {

    if ( k>c )  {
      while ( k<=r ) {  mat_set( *D, k, k, 1 );  k++;  }
      break;
    }

    pivot = mat_get( *U, i, j );

    while (!pivot)  {
      j++;
      pivot = mat_get( *U, i, j );
    }

    row = mat_getr( *U, i );
    row = mat_scale( row, 1/pivot );

    mat_setr( *U, i, row );
    mat_set( *D, k, k, pivot );

    i++;
    j++;

  }

  mat_clear(row);

  return;
}


/**
 *  mat_QR
 *  Solves for the QR decomposition of a matrix.
 */
void mat_QR ( matrix *mat, matrix **Q, matrix **R )  {

  //mat_err( *Q != NULL || *R != NULL, "Error (mat_QR): Q and R matrices must be initialized as NULL." );

  uint i, j, r, c;
  matrix *A, *Acol, *Qcol;

  if ( mat->rows < mat->cols )  mat = mat_trans(mat); 

  r = mat->rows;
  c = mat->cols;
  A    = mat_copy(mat);
  Acol = mat_init(r,1);
  Qcol = mat_init(r,1);

  *Q = mat_init(r,c);
  *R = mat_init(c,c);

  for ( i=1; i<=c; i++ )  {

    Acol = mat_getc(A,i);
    Qcol = mat_copy(Acol);

    for ( j=1; j<i; j++ )  {  Qcol = mat_sub( Qcol, mat_proj( Acol, mat_getc(*Q,j) ) );  }

    mat_setc( *Q, i, mat_uvec(Qcol) );

  }

  *R = mat_mul( mat_trans(*Q), A );

  mat_clear(A);
  mat_clear(Acol);
  mat_clear(Qcol);

  return;
}


/**
 *  mat_chol
 *  Computes the Cholesky factorization of a PDS matrix.  For matrix A, 
 *  the Cholesky factor U is an upper triangular matrix such that A = U' * U.
 */
/*
void mat_chol ( double a[], uint n, uint nn, double u[], uint *nullty, uint *ifault )  {

  double eta = 1.0E-09;
  uint i;
  uint icol;
  uint ii;
  uint irow;
  uint j;
  uint k;
  uint kk;
  uint l;
  uint m;
  double w;
  double x;

  *ifault = 0;
  *nullty = 0;

  if ( n <= 0 )  {
    *ifault = 1;
    return;
  }

  if ( nn < ( n * ( n + 1 ) ) / 2 )  {
    *ifault = 3;
    return;
  }

  j = 1;
  k = 0;
  ii = 0;

  // Factorize column by column, ICOL = column number.
  for ( icol = 1; icol <= n; icol++ )  {

    ii = ii + icol;
    x = eta * eta * a[ii-1];
    l = 0;
    kk = 0;

    // IROW = row number within column ICOL.
    for ( irow = 1; irow <= icol; irow++ )  {

      kk = kk + irow;
      k = k + 1;
      w = a[k-1];
      m = j;

      for ( i = 1; i < irow; i++ )  {
        l = l + 1;
        w = w - u[l-1] * u[m-1];
        m = m + 1;
      }

      l = l + 1;

      if ( irow == icol )  {  break;  }

      if ( u[l-1] != 0.0 )  {
        u[k-1] = w / u[l-1];
      }
      else  {
        u[k-1] = 0.0;
        if ( fabs ( x * a[k-1] ) < w * w )  {
          *ifault = 2;
          return;
        }
      }

    }

    // End of row, estimate relative accuracy of diagonal element.
    if ( fabs ( w ) <= fabs ( eta * a[k-1] ) )  {
      u[k-1] = 0.0;
      *nullty = *nullty + 1;
    }

    else  {
      if ( w < 0.0 )  {
        *ifault = 2;
        return;
      }
      u[k-1] = sqrt ( w );
    }

    j = j + icol;

  }

  return;
}
*/

/**
 *  mat_syminv
 *  Computes the inverse of a symmetric PSD matrix.
 */
/*
void mat_syminv ( double a[], uint n, double c[], double w[], uint *nullty, uint *ifault )  {

  uint i;
  uint icol;
  uint irow;
  uint j;
  uint jcol;
  uint k;
  uint l;
  uint mdiag;
  uint ndiag;
  uint nn;
  uint nrow;
  double x;

  *ifault = 0;

  if ( n <= 0 )  {
    *ifault = 1;
    return;
  }

  nrow = n;

  // Compute the Cholesky factorization of A.
  // The result is stored in C.
  nn = ( n * ( n + 1 ) ) / 2;
  mat_chol( a, n, nn, c, nullty, ifault );

  if ( *ifault != 0 )  return;

  // Invert C and form the product (Cinv)' * Cinv, where Cinv is the inverse
  // of C, row by row starting with the last row.
  // IROW = the row number,
  // NDIAG = location of last element in the row.
  irow = nrow;
  ndiag = nn;

  // Special case, zero diagonal element.
  for ( ; ; )  {

    if ( c[ndiag-1] == 0.0 )  {
      l = ndiag;
      for ( j = irow; j <= nrow; j++ )  {
        c[l-1] = 0.0;
        l = l + j;
      }
    }

    else  {
      l = ndiag;
      for ( i = irow; i <= nrow; i++ )  {
        w[i-1] = c[l-1];
        l = l + i;
      }
      icol = nrow;
      jcol = nn;
      mdiag = nn;

      for ( ; ; )  {
        l = jcol; 

        if ( icol == irow )  {
          x = 1.0 / w[irow-1];
        }
        else  {
          x = 0.0;
        }

        k = nrow;

        while ( irow < k )  {

          x = x - w[k-1] * c[l-1];
          k = k - 1;
          l = l - 1;

          if ( mdiag < l )  {
            l = l - k + 1;
          }

        }

        c[l-1] = x / w[irow-1];

        if ( icol <= irow )  {  break;  }

        mdiag = mdiag - icol;
        icol = icol - 1;
        jcol = jcol - 1;

      }

    }

    ndiag = ndiag - irow;
    irow = irow - 1;

    if ( irow <= 0 )  {  break;  }

  }

  return;
}
*/

/**
 *  mat_tri2vec
 *  Maps the lower triangular elements of a matrix into a vector array. 
 */
matrix* mat_tri2vec ( matrix *tri )  {

  mat_err( tri->rows != tri->cols, "Error (mat_tri2vec): Matrix must be square." );

  uint d, n;
  uint r, c;
  uint i;
  matrix *vec;

  d = tri->rows;
  n = ( d * ( d + 1 ) ) / 2;

  vec = mat_init( n, 1 );

  i = 1;
  for ( r=1; r <= tri->rows; r++ )  {
    for ( c=1; c<=r; c++ )  {
      mat_set( vec, i, 1, mat_get( tri, r, c ) );
      i++;
    }
  }

  return vec;
}


/**
 *  mat_vec2tri
 *  Maps the elements of a vector array into a lower triangular matrix.
 */
matrix* mat_vec2tri ( matrix *vec )  {

  uint r, c, i;
  uint n, d = 1;

  for ( ; ; )  {
    n = ( d * ( d + 1 ) ) / 2;
    if ( n <  vec->rows )  d++;
    if ( n == vec->rows )  break;
    mat_err( n > vec->rows, "Error (mat_vec2tri): Vector must satisfy n=(d*(d+1))/2 relationship." );
  }

  matrix *tri; 
  tri = mat_init( d, d );

  r = 1;  c = 1;
  for ( i=1; i<=n; i++ )  {
    mat_set( tri, r, c, mat_get( vec, i, 1 ) );
    if (r==c)  {  r++;  c = 1;  }
    else c++;
  }
  
  return tri;
}



