
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatComplex.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_initz
//  Initializes a new matrix with the specified dimensions, and
//  sets the elements to complex values of zero.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrixz* mat_initz ( int rows, int cols ) {

  mat_err( ( rows<1 || cols<1 ), "Error (mat_initz): Matrix dimensions must be positive." ); 
  matrixz* out;

  out = (matrixz*) malloc( sizeof(matrixz) );
  mat_err( out == NULL, "Error (mat_initz): Matrix returned NULL." );

  out->rows = rows;
  out->cols = cols;
  out->data = (double complex*) malloc( sizeof(double complex) * rows * cols );

  mat_err( out->data == NULL, "Error (mat_initz): Matrix data returned NULL." );
  memset( out->data, 0.0, rows * cols * sizeof(double complex) );

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_readz
//  Reads a complex matrix from a file.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrixz* mat_readz ( char* file ) {

  FILE*    f;
  int      i, elem;
  int      rows, cols;
  int      scan;
  double   real, imag;
  char     sign;
  matrixz* out;
  double complex* d;

  if ( ( f= fopen( file, "r" ) ) == NULL ) {
    fprintf( stderr, "Error (mat_readz): Cannot open '%s'.\n", file );
    exit(1);
  }

  scan = fscanf( f, "#" );
  mat_err( scan==EOF, "Error (mat_readz): Failed to read 'header' from file." );

  scan = fscanf( f, "%d", &rows );
  mat_err( scan==EOF, "Error (mat_readz): Failed to read 'rows' from file." );

  scan = fscanf( f, "%d", &cols );
  mat_err( scan==EOF, "Error (mat_readz): Failed to read 'cols' from file." );

  out = mat_initz( rows, cols );
  elem = rows * cols; 
  d = out->data;

  for ( i=0; i<elem; i++ ) {
    scan = fscanf( f, "%lf %c %lf", &real, &sign, &imag );
    mat_err( scan==EOF, "Error (mat_readz): Matrix is missing elements." );
    if ( sign == '-' ) { imag *= -1.0; }
    *d = real + imag*I;
    d++;
  }

  scan = fscanf( f, "%lf %c %lf", &real, &sign, &imag );
  mat_err( scan!=EOF, "Error (mat_readz): Matrix has extra elements." );

  fclose(f);
  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_printz
//  Display a complex matrix in the terminal.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_printz( matrixz* mat ) {

  int r = mat->rows;
  int c = mat->cols;
  double complex* d = mat->data;

  printf( "[%dx%d]\n", r, c );
  for ( int i=0; i<r; i++ ) {
    for ( int j=0; j<c; j++ ) {
      printf( " %9.6f  +%9.6f i\t", creal(*d), cimag(*d) );
    }
    d++;
    printf("\n");
  }

  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_writez
//  Writes a complex matrix to a file.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_writez ( matrixz* mat, char* file ) {

  FILE*   f;
  int r = mat->rows;
  int c = mat->cols;
  double complex* d = mat->data;

  if ( ( f= fopen( file, "w" ) ) == NULL ) {
    fprintf( stderr, "Error (mat_writez): Cannot open '%s'.\n", file );
    exit(1);
  }

  fprintf( f, "# %d %d \n", r, c );
  for ( int i=0; i<r; i++ ) {
    for ( int j=0; j<c; j++ ) {
      fprintf( f, " %4.6f  %4.6f \t", creal(*d), cimag(*d) );
    }
    d++;
    fprintf( f, "\n" );
  }

  fclose(f);  
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_clearz
//  Destroys an existing complex matrix and frees the memory.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_clearz ( matrixz* mat ) {

  double complex* data = mat->data;

  if ( mat != NULL ) {
    if ( data != NULL ) {
      free( data );
      data = NULL;
    }
    free(mat);
    mat = NULL;
  }

  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_getre
//  Returns the real part of a complex matrix element.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double mat_getre ( matrixz* mat, int row, int col ) {

  mat_err( row > mat->rows, "Error (mat_getre): Row index exceeds matrix dimensions." );
  mat_err( col > mat->cols, "Error (mat_getre): Column index exceeds matrix dimensions." );
  mat_err( row <1, "Error (mat_getre): Row index must be positive." );
  mat_err( col <1, "Error (mat_getre): Column index must be positive." );

  double complex* d = mat->data;
  int offset = (row-1) * (mat->cols) + (col-1);
  double re;

  d += offset;
  re = creal(*d);

  return re;

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_getim
//  Returns the imaginary part of a complex matrix element.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
double mat_getim ( matrixz* mat, int row, int col ) {

  mat_err( row > mat->rows, "Error (mat_getim): Row index exceeds matrix dimensions." );
  mat_err( col > mat->cols, "Error (mat_getim): Column index exceeds matrix dimensions." );
  mat_err( row <1, "Error (mat_getim): Row index must be positive." );
  mat_err( col <1, "Error (mat_getim): Column index must be positive." );

  double complex* d = mat->data;
  int offset = (row-1) * (mat->cols) + (col-1);
  double im;

  d += offset;
  im = cimag(*d);

  return im;

}

/* REVISE "mat_set" FIRST
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_getzr
//  Returns the specified complex row vector of a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrixz* mat_getzr ( matrixz* mat, int row ) {

  matrixz* out  = mat_initz(1,mat->cols);

  mat_err( row > mat->rows, "Error (mat_getzr): Row index exceeds matrix dimensions." );
  mat_err( row <1, "Error (mat_getzr): Row index must be positive." );

  for ( int i=1; i<= mat->cols; i++ ) {
    mat_setre( out,1,i, mat_getre(mat,row,i) );
    mat_setim( out,1,i, mat_getim(mat,row,i) );
  }

  return out;
}
*/


/* REVISE 'mat_set' FIRST
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_getzc
//  Returns the specified complex column vector of a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrixz* mat_getzc ( matrixz* mat, int col ) {

  matrixz* out  = mat_initz(mat->rows,1);

  mat_err( col > mat->cols, "Error (mat_getzc): Column index exceeds matrix dimensions." );
  mat_err( col <1, "Error (mat_getzc): Column index must be positive." );

  for ( int i=1; i<= mat->rows; i++ ) {
    mat_setre( out,i,1, mat_getre(mat,i,col) );
    mat_setim( out,i,1, mat_getim(mat,i,col) );
  }

  return out;
}
*/


/* SHOULD I PASS RE AND IM INTO FUNCTION?
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_setre
//  Assigns real part of a complex number into a matrix element.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_setre ( matrixz* mat, int row, int col, double real ) {

  mat_err( ( row > mat->rows ) || ( col > mat->cols ), "Error (mat_setre): Index exceeds matrix dimensions." );

  double complex* d = mat->data;
  int offset = (row-1) * (mat->cols) + (col-1);

  d += offset;
  *d = real + imag*I;

}
*/


//  SAME AS ABOVE...
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_setim
//  Assigns imaginary part of a complex number into a matrix element.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~





/* REVISE mat_set FIRST
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_setzr
//  Replaces a row of a complex matrix with the specified vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_setzr ( matrixz* mat, int row, matrixz* vec ) {

  mat_err( row > mat->rows, "Error (mat_setzr): Row index exceeds matrix dimensions." );
  mat_err( row <1, "Error (mat_setzr): Row index must be positive." );
  mat_err( vec->rows !=1, "Error (mat_setzr): Input array must be a row vector." );
  mat_err( mat->cols != vec->cols, "Error(mat_setzr): Input array and matrix must be the same width." );

  for ( int i=1; i<= mat->cols; i++ ) {
    mat_setre( mat,row,i, mat_getre(vec,1,i) );
    mat_setim( mat,row,i, mat_getim(vec,1,i) );
  }
}
*/


/*  REVISE mat_set FIRST
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_setzc
//  Replaces a column of a complex matrix with the specified vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_setzc ( matrixz* mat, int col, matrixz* vec ) {

  mat_err( col > mat->cols, "Error (mat_setzc): Column index exceeds matrix dimensions." );
  mat_err( col <1, "Error (mat_setzc): Column index must be positive." );
  mat_err( vec->cols !=1, "Error (mat_setzc): Input array must be a column vector." );
  mat_err( mat->rows != vec->rows, "Error(mat_setzc): Input array and matrix must be the same height." );

  for ( int i=1; i<= mat->rows; i++ ) {
    mat_setre( mat,i,col, mat_getre(vec,i,1) );
    mat_setim( mat,i,col, mat_getim(vec,i,1) );
  }
}
*/



