
//============================================================
//  MatIO.c
//  Justin M Selfridge
//============================================================
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_err
//  If error condition is true, prints a warning and exits.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_err ( bool cond, char* msg )  {
  if (cond) {  fprintf( stderr, "%s\n\n", msg );  exit(1);  }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_init
//  Initializes a new matrix with the specified dimensions, and
//  sets the elements to values of zero.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_read
//  Reads a matrix from a file.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_print
//  Displays a matrix in the terminal.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_write
//  Writes a matrix to a file.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_clear
//  Destroys an existing matrix and frees the memory.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_clear ( matrix* mat )  {

  double* data = mat->data;
  if ( mat != NULL ) {
    if ( data != NULL ) {  free( data );  data = NULL;  }
    free(mat);
    mat = NULL;
  }
  return;
}



