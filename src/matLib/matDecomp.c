
//============================================================
//  matDecomp.c
//  Justin M Selfridge
//============================================================
#include "matLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_LU
//  Solves for the LU decomposition of a matrix (if it exists).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_LU ( matrix* mat, matrix** L, matrix** U )  {

  int i, j, k, n, m, p, r, c;
  float pivot, val, scale;
  matrix* row;

  r = mat->rows;
  c = mat->cols;
  n = r<c ? r : c;
  row = mat_init(1,c);
  i = 1;  j = 1;  m = 0;

  *U = mat_copy(mat);
  *L = mat_init(r,r);

  for ( p=1; p<=n; p++ ) {

    pivot = mat_get(*U,i,j);

    if(!pivot) {
      for ( k=i+1; k<=r; k++ ) {
        val = mat_get(*U,k,j);
        mat_err( val!=0, "Error (mat_LU): The LU decomposition does not exist." );
      }
      j++; m++; p--;
    }

    else {

      for ( k=i; k<=r; k++ ) {
        val = mat_get(*U,k,j)/pivot;
        mat_set(*L,k,j-m,val);
      }

      for ( k=i+1; k<=r; k++ ) {
        scale = -mat_get(*U,k,j)/pivot;
        row = mat_getr(*U,i);
        row = mat_scale(row,scale);
        row = mat_add( row, mat_getr(*U,k) );
        mat_setr(*U,k,row);
      }

      i++;  j++;
    }
  }

  while ( p<=r ) {  mat_set(*L,p,p,1.0);  p++;  }

  mat_clear(row);
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_LDU
//  Solves for the LDU decomposition of a matrix (if it exists).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_LDU ( matrix* mat, matrix** L, matrix** D, matrix** U )  {

  int i, j, k, r, c;
  float pivot;
  matrix* row;

  r = mat->rows;
  c = mat->cols;
  row = mat_init(1,c);

  mat_LU( mat, &*L, &*U );
  *D = mat_init(r,r);

  i = 1;  j = 1;
  for ( k=1; k<=r; k++ ) {

    if ( k>c ) {
      while ( k<=r ) {  mat_set(*D,k,k,1);  k++;  }
      break;
    }

    pivot = mat_get(*U,i,j);
    while (!pivot) {
      j++;
      pivot = mat_get(*U,i,j);
    }
    row = mat_getr(*U,i);
    row = mat_scale( row, 1/pivot );
    mat_setr(*U,i,row);
    mat_set(*D,k,k,pivot);
    i++; j++;
  }

  mat_clear(row);
  return;
}



