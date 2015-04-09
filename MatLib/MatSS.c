
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


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_Tctrl
//  Yields a controller canonical transformation.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_Tctrl ( matrix* A, matrix* B, matrix** Tc, matrix** Ac ) {

  mat_err( A->rows != A->cols, "Error (mat_Tctrl): State matrix (A) must be a square." );
  mat_err( A->rows != B->rows, "Error (mat_Tctrl): State (A) and input (B) matrices must be same height." );
  mat_err( *Tc != NULL, "Error (mat_Tctrl): Transformation matrix (T) must be NULL." );
  mat_err( *Ac != NULL, "Error (mat_Tctrl): Canonical matrix (Ac) must be NULL." );

  int n = B->rows;
  //int m = B->cols;

  *Tc = mat_init(n,n);
  *Ac = mat_init(n,n);

  matrix* ctrb = mat_ctrb(A,B);
  printf("ctrb: ");  mat_print(ctrb);

  matrix* L = NULL;
  matrix* U = NULL;
  mat_LU(ctrb,&L,&U);
  printf("L: ");  mat_print(L);
  printf("U: ");  mat_print(U);
  printf("LU: ");  mat_print(mat_mul(L,U));

  matrix* divL = mat_divL( ctrb, mat_eye(3) );
  printf("divL: ");  mat_print(divL);

  matrix* inv = mat_inv( ctrb );
  printf("inv: ");  mat_print(inv);


}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_lin
//  Linearizes a plant into state space form.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_lin ( matrix* dx ( matrix*, matrix* ), matrix* x, matrix* u, matrix** A, matrix** B, double d ) {

  int n = x->rows;
  int m = u->rows;

  mat_err( x->cols!=1, "Error (mat_lin): States (x) must be a column vector." );
  mat_err( u->cols!=1, "Error (mat_lin): Inputs (u) must be a column vector." );
  mat_err( (*A)->rows!=n || (*A)->cols!=n, "Error (mat_lin): State matrix (A) must be [nxn]." );
  mat_err( (*B)->rows!=n || (*B)->cols!=m, "Error (mat_lin): Input matrix (B) must be [nxm]." );

  matrix* xp = mat_init(n,1);  matrix* xn = mat_init(n,1);
  matrix* up = mat_init(m,1);  matrix* un = mat_init(m,1);
  matrix* dp = mat_init(n,1);  matrix* dn = mat_init(n,1);

  matrix* C  = mat_init(n,1);

  for ( int i=1; i<=n; i++ ) {
    xp = mat_copy(x);  mat_set( xp,i,1, mat_get(x,i,1)+d );
    xn = mat_copy(x);  mat_set( xn,i,1, mat_get(x,i,1)-d );
    dp = dx(xp,u);  dn = dx(xn,u);
    C = mat_scale( mat_sub(dp,dn), 1/(2*d));
    for ( int j=1; j<=n; j++ ) {  mat_set( *A,j,i, mat_get(C,j,1) );  }
  }

  for ( int i=1; i<=m; i++ ) {
    up = mat_copy(u);  mat_set( up,i,1, mat_get(u,i,1)+d );
    un = mat_copy(u);  mat_set( un,i,1, mat_get(u,i,1)-d );
    dp = dx(x,up);  dn = dx(x,un);
    C = mat_scale( mat_sub(dp,dn), 1/(2*d));
    for ( int j=1; j<=n; j++ ) {  mat_set( *B,j,i, mat_get(C,j,1) );  }
  }

  mat_clear(xp);  mat_clear(xn);
  mat_clear(up);  mat_clear(un);
  mat_clear(dp);  mat_clear(dn);
  mat_clear(C);

}



