

#include "matLib.h"


/**
 *  mat_err
 *  If error condition is true, prints a warning and exits.
 */
void mat_err ( bool cond, char* msg )  {
  if (cond) {  fprintf( stderr, "%s\n\n", msg );  exit(1);  }
}


/**
 *  mat_init
 *  Initializes a new matrix with the specified dimensions,
 *  and sets the elements to values of zero.
 */
matrix* mat_init ( int rows, int cols )  {

  mat_err( rows <1 || cols <1, "Error (mat_init): Matrix dimensions must be positive." ); 

  matrix* out;
  out = (matrix*) malloc( sizeof(matrix) );
  mat_err( out == NULL, "Error (mat_init): Matrix returned NULL." );

  out->rows = rows;
  out->cols = cols;
  out->data = (double*) malloc( sizeof(double) * rows * cols );

  mat_err( out->data == NULL, "Error (mat_init): Matrix data returned NULL." );
  memset( out->data, 0.0, rows * cols * sizeof(double) );

  return out;
}


/**
 *  mat_read
 *  Reads a matrix from a file.
 */
/*
matrix* mat_read ( char* file )  {

  FILE*    f;
  int      i, r, c, n, scan;
  float    val;
  matrix*  out;
  double*  data;

  f = fopen( file, "r" );
  mat_err( f==NULL, "Error (mat_read): Cannot open file." );

  scan = fscanf( f, "#" );
  mat_err( scan==EOF, "Error (mat_read): Failed to read 'header' from file." );

  scan = fscanf( f, "%d", &r );
  mat_err( scan==EOF, "Error (mat_read): Failed to read 'rows' from file." );

  scan = fscanf( f, "%d", &c );
  mat_err( scan==EOF, "Error (mat_read): Failed to read 'cols' from file." );

  out = mat_init(r,c);
  n = r * c; 
  data = out->data;

  for ( i=0; i<n; i++ ) {
    scan = fscanf( f, "%f", &val );
    mat_err( scan==EOF, "Error (mat_read): Matrix is missing elements." );
    *(data++) = val;
  }

  scan = fscanf( f, "%f", &val );
  mat_err( scan!=EOF, "Error (mat_read): Matrix has extra elements." );

  fclose(f);
  return out;
}
*/

/**
 *  mat_print
 *  Displays a matrix in the terminal.
 */
void mat_print( matrix* mat )  {

  int r, c, i, j;

  r = mat->rows;
  c = mat->cols;

  printf( "[%dx%d]\n", r, c );
  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ )  printf( " %9.6f", mat_get(mat,i,j) );
    printf("\n");
  }

  return;
}


/**
 *  mat_write
 *  Writes a matrix to a file.
 */
/*
void mat_write ( matrix* mat, char* file )  {

  FILE* f;
  int r, c, i, j;

  r = mat->rows;
  c = mat->cols;

  f = fopen( file, "w" );
  mat_err( f==NULL, "Error (mat_write): Cannot open file.\n" );

  fprintf( f, "# %d %d \n", r, c );
  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ )  fprintf( f, " %2.5f", mat_get(mat,i,j) );
    fprintf( f, "\n" );
  }

  fclose(f);  
  return;
}
*/

/**
 *  mat_clear
 *  Destroys an existing matrix and frees the memory.
 */
void mat_clear ( matrix* mat )  {

  double* data = mat->data;
  if ( mat != NULL ) {
    if ( data != NULL ) {  free( data );  data = NULL;  }
    free(mat);
    mat = NULL;
  }

  return;
}


/**
 *  mat_get
 *  Returns the value of a matrix element.
 */
double mat_get ( matrix* mat, int row, int col )  {

  mat_err( row > mat->rows, "Error (mat_get): Row index exceeds matrix dimensions."     );
  mat_err( col > mat->cols, "Error (mat_get): Column index exceeds matrix dimensions."  );
  mat_err( row <1,          "Error (mat_get): Row index must be positive."              );
  mat_err( col <1,          "Error (mat_get): Column index must be positive."           );

  double  val;
  double* data    = mat->data;
  int     offset  = (row-1) * (mat->cols) + (col-1);

  data += offset;
  val = *data;

  return val;
}


/**
 *  mat_getr
 *  Returns the specified row of a matrix.
 */
/*
matrix* mat_getr ( matrix* mat, int row )  {

  mat_err( row > mat->rows, "Error (mat_getr): Row index exceeds matrix dimensions."  );
  mat_err( row <1,          "Error (mat_getr): Row index must be positive."           );

  int i;
  matrix* out = mat_init(1,mat->cols);
  for ( i=1; i<= mat->cols; i++ )  mat_set( out,1,i, mat_get(mat,row,i) );

  return out;
}
*/

/**
 *  mat_getc
 *  Returns the specified column of a matrix.
 */
/*
matrix* mat_getc ( matrix* mat, int col )  {

  mat_err( col > mat->cols, "Error (mat_getc): Column index exceeds matrix dimensions."  );
  mat_err( col <1,          "Error (mat_getc): Column index must be positive."           );

  int i;
  matrix* out = mat_init(mat->rows,1);
  for ( i=1; i<= mat->rows; i++ )  mat_set( out,i,1, mat_get(mat,i,col) );

  return out;
}
*/

/**
 *  mat_set
 *  Assigns a value into a matrix element.
 */
void mat_set ( matrix* mat, int row, int col, double val )  {

  mat_err( row > mat->rows, "Error (mat_set): Row index exceeds matrix dimensions."     );
  mat_err( col > mat->cols, "Error (mat_set): Column index exceeds matrix dimensions."  );
  mat_err( row <1,          "Error (mat_set): Row index must be positive."              );
  mat_err( col <1,          "Error (mat_set): Column index must be positive."           );

  double* data   = mat->data;
  int     offset = (row-1) * (mat->cols) + (col-1);

  data += offset;
  *data = val;

  return;
}


/**
 *  mat_setr
 *  Replaces a row of a matrix with the specified vector.
 */
/*
void mat_setr ( matrix* mat, int row, matrix* vec )  {

  mat_err( row > mat->rows,        "Error (mat_setr): Row index exceeds matrix dimensions."           );
  mat_err( row <1,                 "Error (mat_setr): Row index must be positive."                    );
  mat_err( vec->rows !=1,          "Error (mat_setr): Input array must be a row vector."              );
  mat_err( mat->cols != vec->cols, "Error(mat_setr): Input array and matrix must be the same width."  );

  int i;
  for ( i=1; i<= mat->cols; i++ )  mat_set( mat,row,i, mat_get(vec,1,i) );

  return;
}
*/

/**
 *  mat_setc
 *  Replaces a column of a matrix with the specified vector.
 */
/*
void mat_setc ( matrix* mat, int col, matrix* vec )  {

  mat_err( col > mat->cols,        "Error (mat_setc): Column index exceeds matrix dimensions."          );
  mat_err( col <1,                 "Error (mat_setc): Column index must be positive."                   );
  mat_err( vec->cols !=1,          "Error (mat_setc): Input array must be a column vector."             );
  mat_err( mat->rows != vec->rows, "Error (mat_setc): Input array and matrix must be the same height."  );

  int i;
  for ( i=1; i<= mat->rows; i++ )  mat_set( mat,i,col, mat_get(vec,i,1) );

  return;
}
*/

/**
 *  mat_copy
 *  Copies a matrix into a new matrix.
 */
/*
matrix* mat_copy ( matrix* mat )  {
  return mat_scale( mat, 1.0 );
}
*/

/**
 *  mat_eye
 *  Creates an identity matrix of dimension n.
 */
/*
matrix* mat_eye ( int n )  {

  mat_err( n<1, "Error (mat_eye): Matrix dimension must be positive." );

  int i;
  matrix* out = mat_init(n,n);
  for ( i=1; i<=n; i++ )  mat_set(out,i,i,1.0);

  return out;
}
*/

/**
 *  mat_ones
 *  Creates a new [nxm] matrix filled with values of one.
 */
/*
matrix* mat_ones ( int rows, int cols )  {

  mat_err( rows <1, "Error (mat_ones): Matrix rows must be a positive dimension."     );
  mat_err( cols <1, "Error (mat_ones): Matrix columns must be a positive dimension."  );

  int i, j;
  matrix* out = mat_init( rows, cols );

  for ( i=1; i<=rows; i++ ) {
    for ( j=1; j<=cols; j++ ) {
      mat_set(out,i,j,1.0);
    }
  }

  return out;
}
*/

/**
 *  mat_scale
 *  Multiplies a matrix by a scalar with type double.
 */
/*
matrix* mat_scale ( matrix* mat, double scale )  {

  int r, c, i, j;
  double  val;
  matrix* out;

  r   = mat->rows;
  c   = mat->cols;
  out = mat_init(r,c);

  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ ) {
      val = mat_get(mat,i,j) * scale;
      mat_set(out,i,j,val);
    }
  }

  return out;
}
*/

/**
 *  mat_swapr
 *  Swaps rows within a matrix.
 */
/*
void mat_swapr ( matrix* mat, int p, int q )  {

  mat_err( mat->rows <2,                 "Error (mat_swapr): Matrix must have at least two rows."  );
  mat_err( mat->rows <p || mat->rows <q, "Error (mat_swapr): Row index exceeds matrix dimension."  );
  mat_err( p<1 || q<1,                   "Error (mat_swapr): Row index must be positive."          );

  if ( p == q )  return;

  matrix* pr = mat_getr(mat,p);
  matrix* qr = mat_getr(mat,q);

  mat_setr( mat, p, qr );
  mat_setr( mat, q, pr );

  mat_clear(pr);
  mat_clear(qr);

  return;
}
*/

/**
 *  mat_swapc
 *  Swaps columns within a matrix.
 */
/*
void mat_swapc ( matrix* mat, int p, int q )  {

  mat_err( mat->cols <2,                 "Error (mat_swapc): Matrix must have at least two columns."  );
  mat_err( mat->cols <p || mat->cols <q, "Error (mat_swapc): Column index exceeds matrix dimension."  );
  mat_err( p<1 || q<1,                   "Error (mat_swapc): Column index must be positive."          );

  if ( p == q )  return;

  matrix* pc = mat_getc(mat,p);
  matrix* qc = mat_getc(mat,q);

  mat_setc( mat, p, qc );
  mat_setc( mat, q, pc );

  mat_clear(pc);
  mat_clear(qc);

  return;
}
*/

/**
 *  mat_appr
 *  Appends two matrices, top to bottom.
 */
/*
matrix* mat_appr ( matrix* matT, matrix* matB )  {

  mat_err( matT->cols != matB->cols, "Error (mat_appr): Matrices must be the same width." );

  int i, j, k;
  matrix* temp = mat_init( 1, matT->cols );
  matrix* out  = mat_init( matT->rows + matB->rows, matT->cols );

  for ( i=1; i<= matT->rows; i++ ) {
    temp = mat_getr( matT, i );
    mat_setr( out, i, temp );
  }

  for ( j=1; j<= matB->rows; j++ ) {
    temp = mat_getr( matB, j );
    k = j + matT->rows;
    mat_setr( out, k, temp );
  }

  mat_clear(temp);
  return out;
}
*/

/**
 *  mat_appc
 *  Appends two matrices, left to right.
 */
/*
matrix* mat_appc ( matrix* matL, matrix* matR )  {

  mat_err( matL->rows != matR->rows, "Error (mat_appc): Matrices must be the same height." );

  int i, j, k;
  matrix* temp = mat_init( matL->rows, 1 );
  matrix* out  = mat_init( matL->rows, matL->cols + matR->cols );

  for ( i=1; i<= matL->cols; i++ ) {
    temp = mat_getc( matL, i );
    mat_setc( out, i, temp );
  }

  for ( j=1; j<= matR->cols; j++ ) {
    temp = mat_getc( matR, j );
    k = j + matL->cols;
    mat_setc( out, k, temp );
  }

  mat_clear(temp);
  return out;
}
*/

/**
 *  mat_rmtiny
 *  Removes nearly zero entries within a matrix.
 */
/*
void mat_rmtiny ( matrix** mat, double tol )  {

  mat_err( tol<0, "Error (mat_rmtiny): Tolerance must be nonnegative." );

  int i, j, r, c;
  double val;

  r = (*mat)->rows;
  c = (*mat)->cols;

  for ( i=1; i<=r; i++ ) {
    for ( j=1; j<=c; j++ ) {
      val = fabs( mat_get(*mat,i,j) );
      if ( val < tol )  mat_set( *mat,i,j, 0.0 );
    }
  }

  return;
}
*/


