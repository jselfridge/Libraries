

#include "matLib.h"


/**
 *  mat_initz
 *  Initializes a new matrix with the specified dimensions,
 *  and sets the elements to complex values of zero.
 */
matrixz* mat_initz ( uint rows, uint cols )  {

  mat_err( rows<1 || cols<1, "Error (mat_initz): Matrix dimensions must be positive." ); 

  matrixz *out;
  out = (matrixz *) malloc( sizeof(matrixz) );
  mat_err( out == NULL, "Error (mat_initz): Matrix returned NULL." );

  out->rows = rows;
  out->cols = cols;
  out->data = (double complex *) malloc( sizeof(double complex) * rows * cols );

  mat_err( out->data == NULL, "Error (mat_initz): Matrix data returned NULL." );
  memset( out->data, 0.0, rows * cols * sizeof(double complex) );

  return out;
}


/**
 *  mat_readz
 *  Reads a complex matrix from a file.
 */
matrixz* mat_readz ( char *file )  {

  FILE *f;
  uint i, r, c, n;
  int scan;
  double re, im;
  char sign;
  matrixz *out;
  double complex *data;

  f = fopen( file, "r" );
  mat_err( f==NULL, "Error (mat_readz): Cannont open file." );

  scan = fscanf( f, "#" );
  mat_err( scan==EOF, "Error (mat_readz): Failed to read 'header' from file." );

  scan = fscanf( f, "%d", &r );
  mat_err( scan==EOF, "Error (mat_readz): Failed to read 'rows' from file." );

  scan = fscanf( f, "%d", &c );
  mat_err( scan==EOF, "Error (mat_readz): Failed to read 'cols' from file." );

  out = mat_initz(r,c);
  n = r * c;
  data = out->data;

  for ( i=0; i<n; i++ ) {
    scan = fscanf( f, "%lf %c %lf i", &re, &sign, &im );
    mat_err( scan==EOF, "Error (mat_readz): Matrix is missing elements." );
    if ( sign == '-' ) { im *= -1.0; }
    *data = re + im*I;
    data++;
  }

  scan = fscanf( f, "%lf %c %lf i", &re, &sign, &im );
  mat_err( scan!=EOF, "Error (mat_readz): Matrix has extra elements." );

  fclose(f);
  return out;
}


/**
 *  mat_printz
 *  Display a complex matrix in the terminal.
 */
void mat_printz ( matrixz *mat )  {

  int r, c, i, j;
  char sign;
  double re, im;

  r = mat->rows;
  c = mat->cols;

  printf( "[%dx%d]\n", r, c );
  for ( i=1; i<=r; i++ )  {
    for ( j=1; j<=c; j++ )  {
      re = mat_getre( mat, i,j );
      im = mat_getim( mat, i,j );
      if (im<0)  sign = '-';
      else       sign = '+';
      printf( " %4.4f  %c%4.4f i\t", re, sign, fabs(im) );
    }
    printf("\n");
  }

  return;
}


/**
 *  mat_writez
 *  Writes a complex matrix to a file.
 */
void mat_writez ( matrixz *mat, char *file )  {

  FILE *f;
  int r, c, i, j;
  double re, im;
  char sign;

  r = mat->rows;
  c = mat->cols;

  f = fopen( file, "w" );
  mat_err( f==NULL, "Error (mat_writez): Cannot open file." );

  fprintf( f, "# %d %d \n", r, c );
  for ( i=1; i<=r; i++ )  {
    for ( j=1; j<=c; j++ )  {
      re = mat_getre( mat, i,j );
      im = mat_getim( mat, i,j );
      if (im<0)  sign = '-';
      else       sign = '+';
      fprintf( f, " %4.6f %c%4.6f i\t", re, sign, fabs(im) );
    }
    fprintf( f, "\n" );
  }

  fclose(f);  
  return;
}


/**
 *  mat_clearz
 *  Destroys an existing complex matrix and frees the memory.
 */
void mat_clearz ( matrixz *mat )  {

  double complex *data = mat->data;
  if ( mat != NULL ) {
    if ( data != NULL ) {  free( data );  data = NULL;  }
    free(mat);
    mat = NULL;
  }
  return;
}


/**
 *  mat_getre
 *  Returns the real part of a complex matrix element.
 */
double mat_getre ( matrixz* mat, int row, int col )  {

  mat_err( row > mat->rows, "Error (mat_getre): Row index exceeds matrix dimensions."     );
  mat_err( col > mat->cols, "Error (mat_getre): Column index exceeds matrix dimensions."  );
  mat_err( row <1,          "Error (mat_getre): Row index must be positive."              );
  mat_err( col <1,          "Error (mat_getre): Column index must be positive."           );

  double re;
  double complex* data = mat->data;
  int offset = (row-1) * (mat->cols) + (col-1);

  data += offset;
  re = creal(*data);

  return re;
}


/**
 *  mat_getim
 *  Returns the imaginary part of a complex matrix element.
 */
double mat_getim ( matrixz* mat, int row, int col )  {

  mat_err( row > mat->rows, "Error (mat_getim): Row index exceeds matrix dimensions."     );
  mat_err( col > mat->cols, "Error (mat_getim): Column index exceeds matrix dimensions."  );
  mat_err( row <1,          "Error (mat_getim): Row index must be positive."              );
  mat_err( col <1,          "Error (mat_getim): Column index must be positive."           );

  double im;
  double complex* data = mat->data;
  int offset = (row-1) * (mat->cols) + (col-1);

  data += offset;
  im = cimag(*data);

  return im;
}


/**
 *  mat_getzr
 *  Returns the specified complex row vector of a matrix.
 */
matrixz* mat_getzr ( matrixz* mat, int row )  {

  mat_err( row > mat->rows, "Error (mat_getzr): Row index exceeds matrix dimensions."  );
  mat_err( row <1,          "Error (mat_getzr): Row index must be positive."           );

  int i;
  matrixz* out  = mat_initz(1,mat->cols);
  for ( i=1; i<= mat->cols; i++ )  mat_setz( out,1,i, mat_getre(mat,row,i), mat_getim(mat,row,i) );

  return out;
}


/**
 *  mat_getzc
 *  Returns the specified complex column vector of a matrix.
 */
matrixz* mat_getzc ( matrixz* mat, int col )  {

  mat_err( col > mat->cols, "Error (mat_getzc): Column index exceeds matrix dimensions."  );
  mat_err( col <1,          "Error (mat_getzc): Column index must be positive."           );

  int i;
  matrixz* out  = mat_initz(mat->rows,1);
  for ( i=1; i<= mat->rows; i++ )  mat_setz( out,i,1, mat_getre(mat,i,col), mat_getim(mat,i,col) );

  return out;
}


/**
 *  mat_setz
 *  Assigns a complex number into a matrix element.
 */
void mat_setz ( matrixz* mat, int row, int col, double re, double im )  {

  mat_err( row > mat->rows, "Error (mat_setz): Row index exceeds matrix dimensions."     );
  mat_err( col > mat->cols, "Error (mat_setz): Column index exceeds matrix dimensions."  );
  mat_err( row <1,          "Error (mat_setz): Row index must be positive."              );
  mat_err( col <1,          "Error (mat_setz): Column index must be positive."           );

  double complex* data = mat->data;
  int offset = (row-1) * (mat->cols) + (col-1);

  data += offset;
  *data = re + im *I;

  return;
}


/**
 *  mat_setzr
 *  Replaces a row of a complex matrix with the specified vector.
 */
void mat_setzr ( matrixz* mat, int row, matrixz* vec )  {

  mat_err( row > mat->rows,        "Error (mat_setzr): Row index exceeds matrix dimensions."            );
  mat_err( row <1,                 "Error (mat_setzr): Row index must be positive."                     );
  mat_err( vec->rows !=1,          "Error (mat_setzr): Input array must be a row vector."               );
  mat_err( mat->cols != vec->cols, "Error (mat_setzr): Input array and matrix must be the same width."  );

  int i;
  for ( i=1; i<= mat->cols; i++ )  mat_setz( mat,row,i, mat_getre(vec,1,i), mat_getim(vec,1,i) );

  return;
}


/**
 *  mat_setzc
 *  Replaces a column of a complex matrix with the specified vector.
 */
void mat_setzc ( matrixz* mat, int col, matrixz* vec )  {

  mat_err( col > mat->cols,        "Error (mat_setzc): Column index exceeds matrix dimensions."          );
  mat_err( col <1,                 "Error (mat_setzc): Column index must be positive."                   );
  mat_err( vec->cols !=1,          "Error (mat_setzc): Input array must be a column vector."             );
  mat_err( mat->rows != vec->rows, "Error (mat_setzc): Input array and matrix must be the same height."  );

  int i;
  for ( i=1; i<= mat->rows; i++ )  mat_setz( mat,i,col, mat_getre(vec,i,1), mat_getim(vec,i,1) );

  return;
}



