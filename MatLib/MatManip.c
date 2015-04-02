
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

  double* matdata;
  int     offset;

  mat_err( ( row > mat->rows ) || ( col > mat->cols ), "Error (mat_set): Index exceeds matrix dimensions." );

  matdata = mat->data;
  offset = (row-1) * (mat->cols) + (col-1);
  matdata += offset;
  *matdata = val;

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_get
//  Returns the value of a matrix element.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double mat_get ( matrix* mat, int row, int col ) {

  double* matdata;
  int     offset;
  double  val;

  mat_err( ( row > mat->rows ) || ( col > mat->cols ), "Error (mat_get): Index exceeds matrix dimensions." );

  matdata = mat->data;
  offset = (row-1) * (mat->cols) + (col-1);
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

  matrix* out;
  double* outdata;

  mat_err( n<1, "Error (mat_eye): Matrix dimension must be positive." );

  out = mat_init( n, n );
  outdata = out->data;

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

  matrix* out;
  double* outdata;
  int elem = rows * cols;

  mat_err(  rows<1 || cols<1, "Error (mat_ones): Matrix must have positive dimensions." );

  out = mat_init( rows, cols );
  outdata = out->data;

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

  int      elem     = mat->rows * mat->cols;
  matrix*  out      = mat_init( mat->rows, mat->cols );
  double*  outdata  = out->data;
  double*  matdata  = mat->data;

  for ( int i=0; i<elem; i++ ) {
    *(outdata++) = *(matdata++) * scale;
  }

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_swapr
//  Swaps rows within a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_swapr ( matrix* mat, int p, int q ) {

  int     r = mat->rows;
  int     c = mat->cols;
  double  temp;
  double* pRow;
  double* qRow;

  mat_err( r<2, "Error (mat_swapr): Matrix must have at least two rows.");
  mat_err( p>r || q>r, "Error (mat_swapr): Row index exceeds matrix dimension.");

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

  int     r = mat->rows;
  int     c = mat->cols;
  double  temp;
  double* pCol;
  double* qCol;

  mat_err( c<2, "Error (mat_swapc): Matrix must have at least two columns.");
  mat_err( p>c || q>c, "Error (mat_swapc): Column index exceeds matrix dimension.");

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
//  mat_rmtiny
//  Removes nearly zero entries within a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_rmtiny ( matrix* mat, double tol ) {

  int     r     = mat->rows;
  int     c     = mat->cols;
  int     n     = r*c;
  matrix* tiny  = mat_init(r,c);
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



