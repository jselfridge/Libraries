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






// /**
// *  mat_chol
// *  Computes the Cholesky factorization of a PDS matrix.  For matrix A, 
// *  the Cholesky factor U is an upper triangular matrix such that A = U' * U.
// */
// /*
// void mat_chol ( double a[], uint n, uint nn, double u[], uint *nullty, uint *ifault )  {

//   double eta = 1.0E-09;
//   uint i;
//   uint icol;
//   uint ii;
//   uint irow;
//   uint j;
//   uint k;
//   uint kk;
//   uint l;
//   uint m;
//   double w;
//   double x;

//   *ifault = 0;
//   *nullty = 0;

//   if ( n <= 0 )  {
//     *ifault = 1;
//     return;
//   }

//   if ( nn < ( n * ( n + 1 ) ) / 2 )  {
//     *ifault = 3;
//     return;
//   }

//   j = 1;
//   k = 0;
//   ii = 0;

//   // Factorize column by column, ICOL = column number.
//   for ( icol = 1; icol <= n; icol++ )  {

//     ii = ii + icol;
//     x = eta * eta * a[ii-1];
//     l = 0;
//     kk = 0;

//     // IROW = row number within column ICOL.
//     for ( irow = 1; irow <= icol; irow++ )  {

//       kk = kk + irow;
//       k = k + 1;
//       w = a[k-1];
//       m = j;

//       for ( i = 1; i < irow; i++ )  {
//         l = l + 1;
//         w = w - u[l-1] * u[m-1];
//         m = m + 1;
//       }

//       l = l + 1;

//       if ( irow == icol )  {  break;  }

//       if ( u[l-1] != 0.0 )  {
//         u[k-1] = w / u[l-1];
//       }
//       else  {
//         u[k-1] = 0.0;
//         if ( fabs ( x * a[k-1] ) < w * w )  {
//           *ifault = 2;
//           return;
//         }
//       }

//     }

//     // End of row, estimate relative accuracy of diagonal element.
//     if ( fabs ( w ) <= fabs ( eta * a[k-1] ) )  {
//       u[k-1] = 0.0;
//       *nullty = *nullty + 1;
//     }

//     else  {
//       if ( w < 0.0 )  {
//         *ifault = 2;
//         return;
//       }
//       u[k-1] = sqrt ( w );
//     }

//     j = j + icol;

//   }

//   return;
// }
// */

// /**
// *  mat_syminv
// *  Computes the inverse of a symmetric PSD matrix.
// */
// /*
// void mat_syminv ( double a[], uint n, double c[], double w[], uint *nullty, uint *ifault )  {

//   uint i;
//   uint icol;
//   uint irow;
//   uint j;
//   uint jcol;
//   uint k;
//   uint l;
//   uint mdiag;
//   uint ndiag;
//   uint nn;
//   uint nrow;
//   double x;

//   *ifault = 0;

//   if ( n <= 0 )  {
//     *ifault = 1;
//     return;
//   }

//   nrow = n;

//   // Compute the Cholesky factorization of A.
//   // The result is stored in C.
//   nn = ( n * ( n + 1 ) ) / 2;
//   mat_chol( a, n, nn, c, nullty, ifault );

//   if ( *ifault != 0 )  return;

//   // Invert C and form the product (Cinv)' * Cinv, where Cinv is the inverse
//   // of C, row by row starting with the last row.
//   // IROW = the row number,
//   // NDIAG = location of last element in the row.
//   irow = nrow;
//   ndiag = nn;

//   // Special case, zero diagonal element.
//   for ( ; ; )  {

//     if ( c[ndiag-1] == 0.0 )  {
//       l = ndiag;
//       for ( j = irow; j <= nrow; j++ )  {
//         c[l-1] = 0.0;
//         l = l + j;
//       }
//     }

//     else  {
//       l = ndiag;
//       for ( i = irow; i <= nrow; i++ )  {
//         w[i-1] = c[l-1];
//         l = l + i;
//       }
//       icol = nrow;
//       jcol = nn;
//       mdiag = nn;

//       for ( ; ; )  {
//         l = jcol; 

//         if ( icol == irow )  {
//           x = 1.0 / w[irow-1];
//         }
//         else  {
//           x = 0.0;
//         }

//         k = nrow;

//         while ( irow < k )  {

//           x = x - w[k-1] * c[l-1];
//           k = k - 1;
//           l = l - 1;

//           if ( mdiag < l )  {
//             l = l - k + 1;
//           }

//         }

//         c[l-1] = x / w[irow-1];

//         if ( icol <= irow )  {  break;  }

//         mdiag = mdiag - icol;
//         icol = icol - 1;
//         jcol = jcol - 1;

//       }

//     }

//     ndiag = ndiag - irow;
//     irow = irow - 1;

//     if ( irow <= 0 )  {  break;  }

//   }

//   return;
// }
// */



// /**
// *  mat_vec2tri
// *  Maps the elements of a vector array into a lower triangular matrix.
// */
// matrix* mat_vec2tri ( matrix *vec )  {

//   uint r, c, i;
//   uint n, d = 1;

//   for ( ; ; )  {
//     n = ( d * ( d + 1 ) ) / 2;
//     if ( n <  vec->rows )  d++;
//     if ( n == vec->rows )  break;
//     mat_err( n > vec->rows, "Error (mat_vec2tri): Vector must satisfy n=(d*(d+1))/2 relationship." );
//   }

//   matrix *tri; 
//   tri = mat_init( d, d );

//   r = 1;  c = 1;
//   for ( i=1; i<=n; i++ )  {
//     mat_set( tri, r, c, mat_get( vec, i, 1 ) );
//     if (r==c)  {  r++;  c = 1;  }
//     else c++;
//   }
  
//   return tri;
// }



