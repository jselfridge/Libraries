
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatIOZ.c
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



