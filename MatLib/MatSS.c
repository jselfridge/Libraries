
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatSS.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_ctrb
//  Returns the controllability matrix of a state space system.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_ctrb ( matrix* A, matrix* B ) {

  mat_err( A->rows != A->cols, "Error (mat_ctrb): State matrix (A) must be square." );
  mat_err( A->rows != B->rows, "Error (mat_ctrb): State (A) and input (B) matrices must be same height." );

  int n = A->rows;
  int m = B->cols;

  matrix* ctrb = mat_init(n,n*m);
  matrix* AB = mat_init(n,m);

  for ( int i=0; i<n; i++ ) {
    AB = mat_mul( mat_pow(A,i), B );
    for ( int j=1; j<=n; j++ ) {
      for ( int k=1; k<=m; k++ ) {
	mat_set( ctrb, j, k+i*m, mat_get(AB,j,k) );
      }
    }
  }

  mat_clear(AB);
  return ctrb;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_obsv
//  Returns the observability matrix of a state space system.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_obsv ( matrix* A, matrix* C ) {

  mat_err( A->rows != A->cols, "Error (mat_obsv): State matrix (A) must be square." );
  mat_err( A->cols != C->cols, "Error (mat_obsv): State (A) and measurement (C) matrices must be same width." );

  int n = A->rows;
  int m = C->rows;

  matrix* obsv = mat_init(n*m,n);
  matrix* CA = mat_init(m,n);

  for ( int i=0; i<n; i++ ) {
    CA = mat_mul( C, mat_pow(A,i) ); 
    for ( int j=1; j<=m; j++ ) {
      for ( int k=1; k<=n; k++ ) {
	mat_set( obsv, j+i*m, k, mat_get(CA,j,k) );
      }
    }
  }

  mat_clear(CA);
  return obsv;
}



