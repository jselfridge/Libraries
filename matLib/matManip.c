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

  uint r = mat->rows;
  uint c = mat->cols;

  printf( "[%dx%d]\n", r, c );
  for( uint i=1; i<=r; i++ ) {
    for( uint j=1; j<=c; j++ )  printf( " %8.4f", mat_get( mat, i, j ) );
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
    for( uint j=1; j<=mat->cols; j++ )  fprintf( f, " %e", mat_get( mat, i, j ) );
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

  float *data = mat->data;
  uint offset = (row-1) * (mat->cols) + (col-1);
  data += offset;

  return *data;
}




/*******************************************************************************
* matrix* mat_getr ( matrix *mat, uint row )
* Returns the specified row of a matrix.
*******************************************************************************/
// matrix* mat_getr ( matrix *mat, uint row ) {

//   mat_err( row > mat->rows, "Error (mat_getr): Row index exceeds matrix dimensions." );
//   mat_err( row < 1,         "Error (mat_getr): Row index must be positive."          );

//   uint i, c;
//   matrix *out;

//   c = mat->cols;
//   out = mat_init(1,c);

//   for( i=1; i<=c; i++ )  mat_set( out, 1, i, mat_get( mat, row, i ) );

//   return out;
// }




/*******************************************************************************
* matrix* mat_getc ( matrix *mat, uint col )
* Returns the specified column of a matrix.
*******************************************************************************/
// matrix* mat_getc ( matrix *mat, uint col ) {

//   mat_err( col > mat->cols, "Error (mat_getc): Column index exceeds matrix dimensions." );
//   mat_err( col < 1,         "Error (mat_getc): Column index must be positive."          );

//   uint i, r;
//   matrix *out;

//   r = mat->rows;
//   out = mat_init(r,1);

//   for( i=1; i<=r; i++ )  mat_set( out, i, 1, mat_get( mat, i, col ) );

//   return out;
// }




/*******************************************************************************
* void mat_set ( matrix *mat, uint row, uint col, float val )
* Assigns a value into a matrix element.
*******************************************************************************/
void mat_set ( matrix *mat, uint row, uint col, float val ) {

  mat_err( ( !row || row > mat->rows ), "Error (mat_set): Row index exceeds matrix dimensions."    );
  mat_err( ( !col || col > mat->cols ), "Error (mat_set): Column index exceeds matrix dimensions." );

  float *data = mat->data;
  uint offset = (row-1) * (mat->cols) + (col-1);

  data += offset;
  *data = val;

  return;
}




/*******************************************************************************
* void mat_setr ( matrix *mat, uint row, matrix *vec )
* Replaces a row of a matrix with the specified vector.
*******************************************************************************/
// void mat_setr ( matrix *mat, uint row, matrix *vec ) {

//   mat_err( row > mat->rows,        "Error (mat_setr): Row index exceeds matrix dimensions."           );
//   mat_err( row < 1,                "Error (mat_setr): Row index must be positive."                    );
//   mat_err( vec->rows !=1,          "Error (mat_setr): Input array must be a row vector."              );
//   mat_err( mat->cols != vec->cols, "Error (mat_setr): Input array and matrix must be the same width." );

//   uint i;
//   for( i=1; i <= mat->cols; i++ )  mat_set( mat, row, i, mat_get( vec, 1, i ) );

//   return;
// }




/*******************************************************************************
* void mat_setc ( matrix *mat, uint col, matrix *vec )
* Replaces a column of a matrix with the specified vector.
*******************************************************************************/
// void mat_setc ( matrix *mat, uint col, matrix *vec ) {

//   mat_err( col > mat->cols,        "Error (mat_setc): Column index exceeds matrix dimensions."         );
//   mat_err( col < 1,                "Error (mat_setc): Column index must be positive."                  );
//   mat_err( vec->cols !=1,          "Error (mat_setc): Input array must be a column vector."            );
//   mat_err( mat->rows != vec->rows, "Error (mat_setc): Input array and matrix must be the same height." );

//   uint i;
//   for( i=1; i <= mat->rows; i++ )  mat_set( mat, i, col, mat_get( vec, i, 1 ) );

//   return;
// }




/*******************************************************************************
* matrix* mat_copy ( matrix *mat )
* Copies a matrix into a new matrix.
*******************************************************************************/
// matrix* mat_copy ( matrix *mat ) {
//   return mat_scale( mat, 1.0f );
// }




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
// void mat_swapr ( matrix *mat, uint p, uint q ) {

//   mat_err( mat->rows < 2,                  "Error (mat_swapr): Matrix must have at least two rows." );
//   mat_err( mat->rows < p || mat->rows < q, "Error (mat_swapr): Row index exceeds matrix dimension." );
//   mat_err( p<1 || q<1,                     "Error (mat_swapr): Row index must be positive."         );

//   if( p == q )  return;

//   matrix *pr = mat_getr(mat,p);
//   matrix *qr = mat_getr(mat,q);

//   mat_setr( mat, p, qr );
//   mat_setr( mat, q, pr );

//   mat_clear(pr);
//   mat_clear(qr);

//   return;
// }




/*******************************************************************************
* void mat_swapc ( matrix *mat, uint p, uint q )
* Swaps columns within a matrix.
*******************************************************************************/
// void mat_swapc ( matrix *mat, uint p, uint q ) {

//   mat_err( mat->cols < 2,                  "Error (mat_swapc): Matrix must have at least two columns." );
//   mat_err( mat->cols < p || mat->cols < q, "Error (mat_swapc): Column index exceeds matrix dimension." );
//   mat_err( p<1 || q<1,                     "Error (mat_swapc): Column index must be positive."         );

//   if ( p == q )  return;

//   matrix *pc = mat_getc(mat,p);
//   matrix *qc = mat_getc(mat,q);

//   mat_setc( mat, p, qc );
//   mat_setc( mat, q, pc );

//   mat_clear(pc);
//   mat_clear(qc);

//   return;
// }




/*******************************************************************************
* matrix* mat_appr ( matrix *matT, matrix *matB )
* Appends two matrices, top to bottom.
*******************************************************************************/
// matrix* mat_appr ( matrix *matT, matrix *matB ) {

//   mat_err( matT->cols != matB->cols, "Error (mat_appr): Matrices must be the same width." );

//   uint i, j, k, c, rt, rb;
//   matrix *temp, *out;

//   c  = matT->cols;
//   rt = matT->rows;
//   rb = matB->rows;

//   temp = mat_init(1,c);
//   out  = mat_init( rt + rb, c );

//   for ( i=1; i<=rt; i++ ) {
//     temp = mat_getr( matT, i );
//     mat_setr( out, i, temp );
//   }

//   for ( j=1; j<=rb; j++ ) {
//     temp = mat_getr( matB, j );
//     k = j + rt;
//     mat_setr( out, k, temp );
//   }

//   mat_clear(temp);
//   return out;
// }




/*******************************************************************************
* matrix* mat_appc ( matrix *matL, matrix *matR )
* Appends two matrices, left to right.
*******************************************************************************/
// matrix* mat_appc ( matrix *matL, matrix *matR ) {

//   mat_err( matL->rows != matR->rows, "Error (mat_appc): Matrices must be the same height." );

//   uint i, j, k, r, cl, cr;
//   matrix *temp, *out;

//   r  = matL->rows;
//   cl = matL->cols;
//   cr = matR->cols;

//   temp = mat_init(r,1);
//   out  = mat_init( r, cl + cr );

//   for ( i=1; i<=cl; i++ ) {
//     temp = mat_getc( matL, i );
//     mat_setc( out, i, temp );
//   }

//   for ( j=1; j<=cr; j++ ) {
//     temp = mat_getc( matR, j );
//     k = j + cl;
//     mat_setc( out, k, temp );
//   }

//   mat_clear(temp);
//   return out;
// }




/*******************************************************************************
* void mat_rmtiny ( matrix **mat, float tol )
* Matrix entries smaller than 'tol' are replaced with values of zero.
*******************************************************************************/
// void mat_rmtiny ( matrix **mat, float tol ) {

//   mat_err( tol < 0.0f, "Error (mat_rmtiny): Tolerance must be nonnegative." );

//   uint i, j, r, c;
//   float val;

//   r = (*mat)->rows;
//   c = (*mat)->cols;

//   for( i=1; i<=r; i++ ) {
//     for( j=1; j<=c; j++ ) {
//       val = fabs( mat_get( *mat, i, j ) );
//       if( val < tol )  mat_set( *mat, i, j, 0.0 );
//     }
//   }

//   return;
// }



