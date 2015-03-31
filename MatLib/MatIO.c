
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatIO.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_err
//  If error condition is true, prints a warning and exits.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_err ( int cond, char* msg ) {
  if (cond) {
    fprintf( stderr, "%s\n\n", msg );
    exit(1);
  }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_init
//  Initializes a new matrix with the specified dimensions, and
//  sets the elements to values of zero.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_init ( int rows, int cols ) {

  matrix* out;
  mat_err( ( rows<1 || cols<1 ), "Error (mat_init): Matrix dimensions must be positive." ); 

  out = (matrix*) malloc( sizeof(matrix) );
  mat_err( out == NULL, "Error (mat_init): Matrix returned NULL." );

  out->rows = rows;
  out->cols = cols;
  out->data = (double*) malloc( sizeof(double) * rows * cols );

  mat_err( out->data == NULL, "Error (mat_init): Matrix data returned NULL." );
  memset( out->data, 0.0, rows * cols * sizeof(double) );

  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_read
//  Reads a matrix from a file.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_read ( char* file ) {

  FILE*    f;
  int      i, elem;
  int      rows, cols;
  int      scan;
  float    val;
  matrix*  out;
  double*  outdata;

  if ( ( f= fopen( file, "r" ) ) == NULL ) {
    fprintf( stderr, "Error (mat_read): Cannot open '%s'.\n", file );
    exit(1);
  }

  scan = fscanf( f, "%d", &rows );
  mat_err( scan==EOF, "Error (mat_read): Failed to read 'rows' from file." );

  scan = fscanf( f, "%d", &cols );
  mat_err( scan==EOF, "Error (mat_read): Failed to read 'col' from file." );

  out = mat_init( rows, cols );
  elem = rows * cols; 
  outdata = out->data;

  for ( i=0; i<elem; i++ ) {
    scan = fscanf( f, "%f", &val );
    mat_err( scan==EOF, "Error (mat_read): Matrix is missing elements." );
    *(outdata++) = val;
  }

  scan = fscanf( f, "%f", &val );
  mat_err( scan!=EOF, "Error (mat_read): Matrix has extra elements." );

  fclose(f);
  return out;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_print
//  Display a matrix in the terminal.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_print( matrix* mat ) {

  double* matdata = mat->data;
  printf( "[%dx%d]\n", mat->rows, mat->cols );

  for ( int i=0; i< mat->rows; i++ ) {
    for ( int j=0; j< mat->cols; j++ ) {
      printf( " %9.6f", *(matdata++) );
    }
    printf("\n");
  }

  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_write
//  Writes a matrix to a file.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_write ( matrix* mat, char* file ) {

  FILE* f;
  double* matdata = mat->data;

  if ( ( f= fopen( file, "w" ) ) == NULL ) {
    fprintf( stderr, "Error (mat_write): Cannot open '%s'.\n", file );
    exit(1);
  }

  fprintf( f, "%d %d\n", mat->rows, mat->cols );

  for ( int i=0; i< mat->rows; i++ ) {
    for ( int j=0; j< mat->cols; j++ ) {
      fprintf( f, " %2.5f", *(matdata++) );
    }
    fprintf( f, "\n" );
  }

  fclose(f);  
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_clear
//  Destroys an existing matrix and frees the memory.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_clear( matrix* mat ) {

  if ( mat != NULL ) {
    if ( mat->data != NULL ) {
      free( mat->data );
      mat->data = NULL;
    }
    free(mat);
    mat = NULL;
  }

  return;
}



