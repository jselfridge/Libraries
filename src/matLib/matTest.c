
//============================================================
//  matTest.c
//  Justin M Selfridge
//============================================================
#include "matLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_LU
//  Solves for the LU decomposition of a matrix (if it exists).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_LU ( matrix* mat, matrix** L, matrix** U )  {

  int i, j, k, p, q, r, c;
  float pivot, scale, val;
  matrix* row;

  r = mat->rows;
  c = mat->cols;
  row = mat_init(1,c);

  *U = mat_copy(mat);
  *L = mat_init(r,r);

  p = 1;  q = 1;  k = 0;

  // Loop through all columns
  for ( j=1; j<=c; j++ ) {

    // Check row completion
    if ( p>r )  break;

    // Obtain current pivot value
    pivot = mat_get(*U,p,q);

    // Test for zero column entries
    if(!pivot) {
      for ( i=p+1; i<=r; i++ ) {
        val = mat_get(*U,i,q);
        mat_err( val!=0, "Error (mat_LU): The LU decomposition does not exist." );
      }
      q++; k++;
    }

    // Otherwise fill in matrices
    else {

      // Populate L column
      for ( i=p; i<=r; i++ ) {
        val = mat_get(*U,i,q)/pivot;
        mat_set(*L,i,q-k,val);
      }

      // Manipulate U
      for ( i=p+1; i<=r; i++ ) {
        scale = -mat_get(*U,i,q)/pivot;
        row = mat_getr(*U,p);
        row = mat_scale(row,scale);
        row = mat_add( row, mat_getr(*U,i) );
        mat_setr(*U,i,row);
      }

      // New pivot position
      p++;  q++;

    }
  }

  // Check column completion
  if ( q>c )  while ( q<=r ) {  mat_set(*L,q,q,1.0);  q++;  }

  mat_clear(row);
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_LDU
//  Solves for the LDU decomposition of a matrix (if it exists).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_LDU ( matrix* mat, matrix** L, matrix** D, matrix** U )  {

  int i, p, q, r, c;
  float pivot;
  matrix* row;

  r = mat->rows;
  c = mat->cols;
  row = mat_init(1,c);

  mat_LU( mat, &*L, &*U );
  *D = mat_init(r,r);

  p = 1;  q = 1;
  for ( i=1; i<=r; i++ ) {

    if ( i>c ) {
      while ( i<=r ) {  mat_set(*D,i,i,1);  i++;  }
      break;
    }

    pivot = mat_get(*U,p,q);
    while (!pivot) {
      q++;
      pivot = mat_get(*U,p,q);
    }
    row = mat_getr(*U,p);
    row = mat_scale( row, 1/pivot );
    mat_setr(*U,p,row);
    mat_set(*D,i,i,pivot);
    p++; q++;
  }

  mat_clear(row);
  return;
}



