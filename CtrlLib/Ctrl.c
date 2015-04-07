
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Ctrl.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "CtrlLib.h"




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ctrl_lin
//  Linearizes a plant into state space form.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ctrl_lin( matrix* f ( matrix*, matrix* ), matrix* x, matrix* u, matrix** A, matrix** B, double d ) {

  int n = x->rows;
  int m = u->rows;

  mat_err( x->cols!=1, "Error (ctrl_lin): States (x) must be a column vector." );
  mat_err( u->cols!=1, "Error (ctrl_lin): Inputs (u) must be a column vector." );
  mat_err( (*A)->rows!=n || (*A)->cols!=n, "Error (ctrl_lin): State matrix (A) must be [nxn]." );
  mat_err( (*B)->rows!=n || (*B)->cols!=m, "Error (ctrl_lin): Input matrix (B) must be [nxm]." );

  matrix* xp = mat_init(n,1);  matrix* xn = mat_init(n,1);
  matrix* up = mat_init(m,1);  matrix* un = mat_init(m,1);
  matrix* fp = mat_init(n,1);  matrix* fn = mat_init(n,1);

  matrix* C  = mat_init(n,1);

  for ( int i=1; i<=n; i++ ) {
    xp = mat_copy(x);  mat_set( xp,i,1, mat_get(x,i,1)+d );
    xn = mat_copy(x);  mat_set( xn,i,1, mat_get(x,i,1)-d );
    fp = f(xp,u);  fn = f(xn,u);
    C = mat_scale( mat_sub(fp,fn), 1/(2*d));
    for ( int j=1; j<=n; j++ ) {  mat_set( *A,j,i, mat_get(C,j,1) );  }
  }

  for ( int i=1; i<=m; i++ ) {
    up = mat_copy(u);  mat_set( up,i,1, mat_get(u,i,1)+d );
    un = mat_copy(u);  mat_set( un,i,1, mat_get(u,i,1)-d );
    fp = f(x,up);  fn = f(x,un);
    C = mat_scale( mat_sub(fp,fn), 1/(2*d));
    for ( int j=1; j<=n; j++ ) {  mat_set( *B,j,i, mat_get(C,j,1) );  }
  }

  mat_clear(xp);  mat_clear(xn);
  mat_clear(up);  mat_clear(un);
  mat_clear(fp);  mat_clear(fn);
  mat_clear(C);

}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ctrl_ctrb
//  Returns the controllability matrix of a state space system.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* ctrl_ctrb ( matrix* A, matrix* B ) {

  mat_err( A->rows != A->cols, "Error (ctrl_ctrb): State matrix (A) must be square." );
  mat_err( A->rows != B->rows, "Error (ctrl_ctrb): State (A) and input (B) matrices must be same height." );

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
//  ctrl_obsv
//  Returns the observability matrix of a state space system.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* ctrl_obsv ( matrix* A, matrix* C ) {

  mat_err( A->rows != A->cols, "Error (ctrl_obsv): State matrix (A) must be square." );
  mat_err( A->cols != C->cols, "Error (ctrl_obsv): State (A) and measurement (C) matrices must be same width." );

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



