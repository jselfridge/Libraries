
//============================================================
//  Ctrl.c
//  Justin M Selfridge
//============================================================
#include "CtrlLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ctrl_lin
//  Linearizes a plant into state space form.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ctrl_lin( matrix* f ( matrix*, matrix* ), matrix* x, matrix* u, matrix* A, matrix* B, double d )  {

  mat_err( x->cols!=1,                               "Error (ctrl_lin): States (x) must be a column vector."  );
  mat_err( u->cols!=1,                               "Error (ctrl_lin): Inputs (u) must be a column vector."  );
  mat_err( A->rows != x->rows || A->cols != x->rows, "Error (ctrl_lin): State matrix (A) must be [nxn]."      );
  mat_err( B->rows != x->rows || B->cols != u->rows, "Error (ctrl_lin): Input matrix (B) must be [nxm]."      );

  int i, j, n, m;
  matrix *C, *xp, *xn, *up, *un, *fp, *fn;

  n = x->rows;
  m = u->rows;

  //matrix* xp = mat_init(n,1);  matrix* xn = mat_init(n,1);
  //matrix* up = mat_init(m,1);  matrix* un = mat_init(m,1);
  //matrix* fp = mat_init(n,1);  matrix* fn = mat_init(n,1);
  //matrix* C  = mat_init(n,1);

  C = mat_init(n,1);

  xp = mat_init(n,1);  xn = mat_init(n,1);
  up = mat_init(m,1);  un = mat_init(m,1);
  fp = mat_init(n,1);  fn = mat_init(n,1);

  for ( i=1; i<=n; i++ ) {
    xp = mat_copy(x);  mat_set( xp,i,1, mat_get(x,i,1)+d );
    xn = mat_copy(x);  mat_set( xn,i,1, mat_get(x,i,1)-d );
    fp = f(xp,u);  fn = f(xn,u);
    C = mat_scale( mat_sub(fp,fn), 1/(2*d));
    for ( j=1; j<=n; j++ )  mat_set( A,j,i, mat_get(C,j,1) );
  }

  for ( i=1; i<=m; i++ ) {
    up = mat_copy(u);  mat_set( up,i,1, mat_get(u,i,1)+d );
    un = mat_copy(u);  mat_set( un,i,1, mat_get(u,i,1)-d );
    fp = f(x,up);  fn = f(x,un);
    C = mat_scale( mat_sub(fp,fn), 1/(2*d));
    for ( j=1; j<=n; j++ )  mat_set( B,j,i, mat_get(C,j,1) );
  }

  mat_clear(xp);  mat_clear(xn);
  mat_clear(up);  mat_clear(un);
  mat_clear(fp);  mat_clear(fn);
  mat_clear(C);

  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ctrl_ctrb
//  Returns the controllability matrix of a state space system.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* ctrl_ctrb ( matrix* A, matrix* B )  {

  mat_err( A->rows != A->cols, "Error (ctrl_ctrb): State matrix (A) must be square."                       );
  mat_err( A->rows != B->rows, "Error (ctrl_ctrb): State (A) and input (B) matrices must be same height."  );

  int i, j, n, m;
  matrix *AB, *ctrb;

  n = A->rows;
  m = B->cols;

  AB = mat_init(n,m);
  ctrb = mat_init(n,n*m);

  for ( i=0; i<n; i++ ) {
    AB = mat_mul( mat_pow(A,i), B );
    for ( j=1; j<=m; j++ ) {
      mat_setc( ctrb, j+i*m, mat_getc(AB,j) );
    }
  }

  mat_clear(AB);
  return ctrb;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  ctrl_obsv
//  Returns the observability matrix of a state space system.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* ctrl_obsv ( matrix* A, matrix* C )  {

  mat_err( A->rows != A->cols, "Error (ctrl_obsv): State matrix (A) must be square."                            );
  mat_err( A->cols != C->cols, "Error (ctrl_obsv): State (A) and measurement (C) matrices must be same width."  );

  int i, j, n, m;
  matrix *CA, *obsv;

  n = A->rows;
  m = C->rows;
 
  CA = mat_init(m,n);
  obsv = mat_init(n*m,n);

  for ( i=0; i<n; i++ ) {
    CA = mat_mul( C, mat_pow(A,i) ); 
    for ( j=1; j<=m; j++ ) {
	mat_setr( obsv, j+i*m, mat_getr(CA,j) );
    }
  }

  mat_clear(CA);
  return obsv;
}



