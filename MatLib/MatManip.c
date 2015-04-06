
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatManip.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_set
//  Assigns a value into a matrix element
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_set ( matrix* mat, int row, int col, double val ) {

  mat_err( ( row > mat->rows ) || ( col > mat->cols ), "Error (mat_set): Index exceeds matrix dimensions." );

  double* matdata = mat->data;
  int     offset = (row-1) * (mat->cols) + (col-1);

  matdata += offset;
  *matdata = val;

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_get
//  Returns the value of a matrix element.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double mat_get ( matrix* mat, int row, int col ) {

  mat_err( ( row > mat->rows ) || ( col > mat->cols ), "Error (mat_get): Index exceeds matrix dimensions." );

  double* matdata = mat->data;
  int     offset  = (row-1) * (mat->cols) + (col-1);
  double  val;

  matdata += offset;
  val = *matdata;

  return val;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_copy
//  Copies a matrix into a new matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_copy ( matrix* mat ) {
  return mat_scale( mat, 1.0 );
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_eye
//  Creates an identity matrix of size n.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_eye ( int n ) {

  mat_err( n<1, "Error (mat_eye): Matrix dimension must be positive." );

  matrix* out     = mat_init(n,n);
  double* outdata = out->data;

  for ( int i=0; i<n; i++ ) {
    *outdata = 1.0;
    outdata += n+1;
  }

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_ones
//  Creates a new nxm  matrix filled with values of one.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_ones ( int rows, int cols ) {

  mat_err(  rows<1 || cols<1, "Error (mat_ones): Matrix must have positive dimensions." );

  matrix* out     = mat_init( rows, cols );
  double* outdata = out->data;
  int     elem    = rows * cols;

  for ( int i=0; i<elem; i++ ) {
    *outdata = 1.0;
    outdata++;
  }

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_scale
//  Multiplies a matrix by a scalar with type double.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_scale ( matrix* mat, double scale ) {

  int      n        = mat->rows * mat->cols;
  matrix*  out      = mat_init( mat->rows, mat->cols );
  double*  outdata  = out->data;
  double*  matdata  = mat->data;

  for ( int i=0; i<n; i++ ) {
    *(outdata++) = *(matdata++) * scale;
  }

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_swapr
//  Swaps rows within a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_swapr ( matrix* mat, int p, int q ) {

  mat_err( 2> mat->rows, "Error (mat_swapr): Matrix must have at least two rows.");
  mat_err( p> mat->rows || q> mat->rows, "Error (mat_swapr): Row index exceeds matrix dimension.");

  int     c = mat->cols;
  double  temp;
  double* pRow;
  double* qRow;

  if ( p == q ) {  return;  }

  pRow = mat->data + ((p-1)*c);
  qRow = mat->data + ((q-1)*c);

  for ( int i=0; i<c; i++ ) {
    temp  = *pRow;
    *pRow = *qRow;
    *qRow = temp;
    pRow++;
    qRow++;
  }

  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_swapc
//  Swaps columns within a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_swapc ( matrix* mat, int p, int q ) {

  mat_err( 2> mat->cols, "Error (mat_swapc): Matrix must have at least two columns.");
  mat_err( p> mat->cols || q> mat->cols, "Error (mat_swapc): Column index exceeds matrix dimension.");

  int     r = mat->rows;
  int     c = mat->cols;
  double  temp;
  double* pCol;
  double* qCol;

  if ( p == q ) {  return;  }

  pCol = mat->data + (p-1);
  qCol = mat->data + (q-1);

  for ( int i=0; i<r; i++ ) {
    temp  = *pCol;
    *pCol = *qCol;
    *qCol = temp;
    pCol += c;
    qCol += c;
  }

  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_appr
//  Appends two matrices - top to bottom.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_appr ( matrix* matT, matrix* matB ) {

  int tr = matT->rows;  int tc = matT->cols;  int tn = tr*tc;
  int br = matB->rows;  int bc = matB->cols;  int bn = br*bc;

  mat_err( tc != bc, "Error (mat_appr): Matrices must have same number of columns.");

  matrix* mat   = mat_init( tr+br, tc ); 
  double* data  = mat->data;
  double* Tdata = matT->data;
  double* Bdata = matB->data;

  for ( int i=0; i<tn; i++ ) { 
    *data = *Tdata;
    data++;
    Tdata++;
  }
  for ( int j=0; j<bn; j++ ) {
    *data = *Bdata;
    data++;
    Bdata++;
  }

  return mat;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_appc
//  Appends two matrices - side by side.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//void mat_appc ( matrix* matA, matrix* matB ) {

//}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_rmtiny
//  Removes nearly zero entries within a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_rmtiny ( matrix* mat, double tol ) {

  int     n     = mat->rows * mat->cols;
  matrix* tiny  = mat_init( mat->rows, mat->cols );
  double* mdata = mat->data;
  double* tdata = tiny->data;

  for ( int i=0; i<n; i++ ) {
    if ( *mdata < tol ) { *tdata = 0.0; }
    else { *tdata = *mdata; }
    mdata++;
    tdata++;
  }

  return tiny;
}



