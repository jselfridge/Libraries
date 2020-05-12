/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matManip.h
* Source code for matrix manipulation functions within the 'matLib' library.
*
*******************************************************************************/
#include "matLib.h"




/*******************************************************************************
* void mat_err ( bool cond, char *msg )
* If error condition is true, prints a warning and exits.
*******************************************************************************/
void mat_err ( bool cond, char *msg ) {
  if(cond)  {  fprintf( stderr, "%s\n\n", msg );  exit(1);  }
}




/*******************************************************************************
* matrix* mat_init ( uint rows, uint cols )
* Initializes a new matrix with the specified dimensions,
* and sets the elements to values of zero.
*******************************************************************************/
matrix* mat_init ( uint rows, uint cols ) {

  mat_err( ( !rows || !cols ), "Error (mat_init): Matrix dimensions must be positive." );

  matrix *out;
  out = (matrix*) malloc( sizeof(matrix) );
  mat_err( ( out == NULL ), "Error (mat_init): Matrix structure returned NULL." );

  out->rows = rows;
  out->cols = cols;

  out->data = (float*) malloc( rows * cols * sizeof(float) );
  mat_err( ( out->data == NULL ), "Error (mat_init): Matrix data returned NULL." );

  memset( out->data, 0.0, rows * cols * sizeof(float) );

  return out;
}




/*******************************************************************************
* void mat_clear ( matrix *mat )
* Destroys an existing matrix and frees the memory.
*******************************************************************************/
void mat_clear ( matrix *mat ) {

  float *data = mat->data;

  if( mat != NULL ) {
    if( data != NULL ) {
      free(data);
      data = NULL;
    }
    free(mat);
    mat = NULL;
  }

  return;
}




/*******************************************************************************
* void mat_print ( matrix *mat )
* Displays a matrix within the terminal.
*******************************************************************************/
void mat_print ( matrix *mat ) {

  printf( "[%dx%d]\n", mat->rows, mat->cols );
  for( uint i=1; i<=mat->rows; i++ ) {
    for( uint j=1; j<=mat->cols; j++ ) {
      printf( " %8.4f", mat_get( mat, i, j ) );
    }
    printf("\n");
  }

  return;
}




/*******************************************************************************
* matrix* mat_read ( char *file )
* Reads a matrix from a file.
*******************************************************************************/
matrix* mat_read ( char *file ) {

  uint r, c;
  int scan;
  float val;

  FILE *f = fopen( file, "r" );
  mat_err( ( f == NULL ), "Error (mat_read): Cannot open file." );

  scan = fscanf( f, "#" );
  mat_err( ( scan == EOF ), "Error (mat_read): Failed to read 'header' from file." );

  scan = fscanf( f, "%d", &r );
  mat_err( ( scan == EOF ), "Error (mat_read): Failed to read 'rows' from file." );

  scan = fscanf( f, "%d", &c );
  mat_err( ( scan == EOF ), "Error (mat_read): Failed to read 'cols' from file." );

  uint n = r * c;
  matrix *out = mat_init(r,c);
  float *data = out->data;

  for( uint i=0; i<n; i++ ) {
    scan = fscanf( f, "%f", &val );
    mat_err( ( scan == EOF ), "Error (mat_read): Matrix is missing elements." );
    *(data++) = val;
  }

  scan = fscanf( f, "%f", &val );
  mat_err( ( scan != EOF ), "Error (mat_read): Matrix has extra elements." );

  fclose(f);

  return out;
}




/*******************************************************************************
* void mat_write ( matrix *mat, char *file )
* Writes a matrix to a file.
*******************************************************************************/
void mat_write ( matrix *mat, char *file ) {

  FILE *f = fopen( file, "w" );
  mat_err( ( f == NULL ), "Error (mat_write): Cannot open file.\n" );

  fprintf( f, "# %d %d \n", mat->rows, mat->cols );
  for( uint i=1; i<=mat->rows; i++ ) {
    for( uint j=1; j<=mat->cols; j++ ) {
      fprintf( f, " %e", mat_get( mat, i, j ) );
    }
    fprintf( f, "\n" );
  }

  fclose(f);

  return;
}




/*******************************************************************************
* float mat_get ( matrix *mat, uint row, uint col )
* Returns the value of a matrix element.
*******************************************************************************/
float mat_get ( matrix *mat, uint row, uint col ) {

  mat_err( ( !row || row > mat->rows ), "Error (mat_get): Row index exceeds matrix dimensions."    );
  mat_err( ( !col || col > mat->cols ), "Error (mat_get): Column index exceeds matrix dimensions." );

  return *( mat->data + (row-1) * (mat->cols) + (col-1) );
}




/*******************************************************************************
* matrix* mat_getr ( matrix *mat, uint row )
* Returns the specified row of a matrix.
*******************************************************************************/
matrix* mat_getr ( matrix *mat, uint row ) {

  mat_err( ( !row || row > mat->rows ), "Error (mat_getr): Row index exceeds matrix dimensions." );

  matrix *out = mat_init( 1, mat->cols );

  for( uint i=0; i<mat->cols; i++ )  *(out->data+i) = *( mat->data + (row-1) * mat->cols + i );

  return out;
}




/*******************************************************************************
* matrix* mat_getc ( matrix *mat, uint col )
* Returns the specified column of a matrix.
*******************************************************************************/
matrix* mat_getc ( matrix *mat, uint col ) {

  mat_err( ( !col || col > mat->cols ), "Error (mat_getc): Column index exceeds matrix dimensions." );

  matrix *out = mat_init( mat->rows, 1 );

  for( uint i=0; i<mat->rows; i++ )  *(out->data+i) = *( mat->data + ( i * mat->cols ) + (col-1) );

  return out;
}




/*******************************************************************************
* void mat_set ( matrix *mat, uint row, uint col, float val )
* Assigns a value into a matrix element.
*******************************************************************************/
void mat_set ( matrix *mat, uint row, uint col, float val ) {

  mat_err( ( !row || row > mat->rows ), "Error (mat_set): Row index exceeds matrix dimensions."    );
  mat_err( ( !col || col > mat->cols ), "Error (mat_set): Column index exceeds matrix dimensions." );

  *( mat->data + (row-1) * (mat->cols) + (col-1) ) = val;

  return;
}




/*******************************************************************************
* void mat_setr ( matrix *mat, uint row, matrix *vec )
* Replaces a row of a matrix with the specified vector.
*******************************************************************************/
void mat_setr ( matrix *mat, uint row, matrix *vec ) {

  mat_err( ( !row || row > mat->rows ), "Error (mat_setr): Row index exceeds matrix dimensions."           );
  mat_err( ( vec->rows !=1 ),           "Error (mat_setr): Input array must be a row vector."              );
  mat_err( ( mat->cols != vec->cols ),  "Error (mat_setr): Input array and matrix must be the same width." );

  for( uint i=0; i<mat->cols; i++ )  *( mat->data + (row-1) * (mat->cols) + i ) = *( vec->data+i );

  return;
}




/*******************************************************************************
* void mat_setc ( matrix *mat, uint col, matrix *vec )
* Replaces a column of a matrix with the specified vector.
*******************************************************************************/
void mat_setc ( matrix *mat, uint col, matrix *vec ) {

  mat_err( ( !col || col > mat->cols ), "Error (mat_setc): Column index exceeds matrix dimensions."         );
  mat_err( ( vec->cols !=1 ),           "Error (mat_setc): Input array must be a column vector."            );
  mat_err( ( mat->rows != vec->rows ),  "Error (mat_setc): Input array and matrix must be the same height." );

  for( uint i=0; i<mat->rows; i++ )  *( mat->data + ( i * mat->cols ) + (col-1) ) = *( vec->data+i );

  return;
}




/*******************************************************************************
* matrix* mat_copy ( matrix *mat )
* Copies a matrix into a new matrix.
*******************************************************************************/
matrix* mat_copy ( matrix *mat ) {

  matrix *out = mat_init( mat->rows, mat->cols );

  memcpy( out->data, mat->data, sizeof(float) * out->rows * out->cols );
  
  return out;
}




/*******************************************************************************
* matrix* mat_eye ( uint n )
* Creates an identity matrix of dimension n.
*******************************************************************************/
matrix* mat_eye ( uint n ) {

  mat_err( (!n), "Error (mat_eye): Matrix dimension must be positive." );

  matrix *out = mat_init(n,n);

  for( float *ptr = out->data; ptr < out->data + ( out->rows * out->cols ); ptr += n+1 )  *ptr = 1.0;  

  return out;
}




/*******************************************************************************
* matrix* mat_ones ( uint rows, uint cols )
* Creates a new matrix filled with values of one.
*******************************************************************************/
matrix* mat_ones ( uint rows, uint cols ) {

  mat_err( (!rows), "Error (mat_ones): Matrix rows must be a positive."    );
  mat_err( (!cols), "Error (mat_ones): Matrix columns must be a positive." );

  matrix *out = mat_init( rows, cols );

  for( float *ptr = out->data; ptr < out->data + ( out->rows * out->cols ); ptr++ )  *ptr = 1.0;

  return out;
}




/*******************************************************************************
* matrix* mat_scale ( matrix *mat, float scale )
* Multiplies a matrix by a scalar with type float.
*******************************************************************************/
matrix* mat_scale ( matrix *mat, float scale ) {

  matrix *out = mat_init( mat->rows, mat->cols );

  memcpy( out->data, mat->data, sizeof(float) * out->rows * out->cols );

  for( float *ptr = out->data; ptr < out->data + ( out->rows * out->cols ); ptr++ )  *ptr *= scale;

  return out;
}




/*******************************************************************************
* void mat_swapr ( matrix *mat, uint p, uint q )
* Swaps rows within a matrix.
*******************************************************************************/
void mat_swapr ( matrix *mat, uint p, uint q ) {

  mat_err( ( mat->rows < 2 ),       "Error (mat_swapr): Matrix must have at least two rows." );
  mat_err( ( !p || p > mat->rows ), "Error (mat_swapr): Row index exceeds matrix dimension." );
  mat_err( ( !q || q > mat->rows ), "Error (mat_swapr): Row index exceeds matrix dimension." );

  if( p == q )  return;

  for( uint i=0; i<mat->cols; i++ ) {
    float tmp = *( mat->data + (p-1) * (mat->cols) + i );
    *( mat->data + (p-1) * (mat->cols) + i ) = *( mat->data + (q-1) * (mat->cols) + i );
    *( mat->data + (q-1) * (mat->cols) + i ) = tmp;
  }

  return;
}




/*******************************************************************************
* void mat_swapc ( matrix *mat, uint p, uint q )
* Swaps columns within a matrix.
*******************************************************************************/
void mat_swapc ( matrix *mat, uint p, uint q ) {

  mat_err( ( mat->cols < 2 ),       "Error (mat_swapc): Matrix must have at least two columns." );
  mat_err( ( !p || p > mat->cols ), "Error (mat_swapc): Column index exceeds matrix dimension." );
  mat_err( ( !q || q > mat->cols ), "Error (mat_swapc): Column index exceeds matrix dimension." );

  if ( p == q )  return;

  for( uint i=0; i<mat->rows; i++ ) {
    float tmp = *( mat->data + ( i * mat->cols ) + (p-1) );
    *( mat->data + ( i * mat->cols ) + (p-1) ) = *( mat->data + ( i * mat->cols ) + (q-1) );
    *( mat->data + ( i * mat->cols ) + (q-1) ) = tmp;
  }

  return;
}




/*******************************************************************************
* matrix* mat_appr ( matrix *matT, matrix *matB )
* Appends two matrices, top to bottom.
*******************************************************************************/
matrix* mat_appr ( matrix *matT, matrix *matB ) {

  mat_err( ( matT->cols != matB->cols ), "Error (mat_appr): Matrices must be the same width." );

  matrix *out = mat_init( matT->rows + matB->rows, matT->cols );

  memcpy( out->data, matT->data, sizeof(float) * matT->rows * matT->cols );
  memcpy( out->data + ( matT->rows * matT->cols ), matB->data, sizeof(float) * matB->rows * matT->cols );

  return out;
}




/*******************************************************************************
* matrix* mat_appc ( matrix *matL, matrix *matR )
* Appends two matrices, left to right.
*******************************************************************************/
matrix* mat_appc ( matrix *matL, matrix *matR ) {

  mat_err( ( matL->rows != matR->rows ), "Error (mat_appc): Matrices must be the same height." );

  matrix *out = mat_init( matL->rows, matL->cols + matR->cols );

  for( uint i=0; i<matL->rows; i++ ) {
    memcpy( out->data + (i*out->cols),               matL->data + (i*matL->cols), sizeof(float) * matL->cols );
    memcpy( out->data + (i*out->cols) + matL->cols , matR->data + (i*matR->cols), sizeof(float) * matR->cols );    
  }

  return out;
}




/*******************************************************************************
* void mat_rmtiny ( matrix **mat, float tol )
* Matrix entries smaller than 'tol' are replaced with values of zero.
*******************************************************************************/
void mat_rmtiny ( matrix **mat, float tol ) {

  mat_err( ( tol < 0.0 ), "Error (mat_rmtiny): Tolerance must be nonnegative." );

  for( float *ptr = (*mat)->data; ptr < (*mat)->data + ( (*mat)->rows * (*mat)->cols ); ptr++ ) {
    if( fabs(*ptr) < tol )  *ptr = 0.0;
  }

  return;
}



