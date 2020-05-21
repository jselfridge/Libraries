/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matManip.c
* Source code for matrix manipulation functions within the 'matLib' library.
*
*******************************************************************************/
#include "../inc/matManip.h"




/*******************************************************************************
* matrix* mat_init ( uint r, uint c )
* Initializes a new matrix with the specified dimensions, and sets the elements
* to values of zero.
*******************************************************************************/
matrix* mat_init ( uint r, uint c ) {

  mat_err( ( !r || !c ), "Error (mat_init): Matrix dimensions must be positive." );

  matrix* N = (matrix*) malloc( sizeof(matrix) );
  mat_err( ( N == NULL ), "Error (mat_init): Matrix structure returned NULL." );

  N->r = r;
  N->c = c;

  N->e = (float*) malloc( r * c * sizeof(float) );
  mat_err( ( N->e == NULL ), "Error (mat_init): Matrix data returned NULL." );

  memset( N->e, 0.0, r * c * sizeof(float) );

  return N;
}




/*******************************************************************************
* void mat_clear ( matrix* M )
* Destroys an existing matrix and frees the memory.
*******************************************************************************/
void mat_clear ( matrix* M ) {

  if( M != NULL ) {
    if( M->e != NULL ) {
      free(M->e);
      M->e = NULL;
    }
    free(M);
    M = NULL;
  }

  return;
}




/*******************************************************************************
* void mat_print ( matrix* M )
* Displays a matrix within the terminal.
*******************************************************************************/
void mat_print ( matrix* M ) {

  mat_err( ( M == NULL ), "Error (mat_print): Matrix is NULL." );

  printf( "[%dx%d]\n", M->r, M->c );

  for( uint i=0; i<M->r; i++ ) {
    for( uint j=0; j<M->c; j++ ) {
      printf( " %8.4f", *( M->e + i*M->c + j ) );
    }
    printf("\n");
  }

  return;
}




/*******************************************************************************
* matrix* mat_read ( char* file )
* Reads a matrix from a file.
*******************************************************************************/
matrix* mat_read ( char* file ) {

  uint r, c;
  int scan;
  float val;

  FILE* f = fopen( file, "r" );
  mat_err( ( f == NULL ), "Error (mat_read): Cannot open file." );

  scan = fscanf( f, "#" );
  mat_err( ( scan == EOF ), "Error (mat_read): Failed to read 'header' from file." );

  scan = fscanf( f, "%u", &r );
  mat_err( ( scan == EOF ), "Error (mat_read): Failed to read 'rows' from file." );

  scan = fscanf( f, "%u", &c );
  mat_err( ( scan == EOF ), "Error (mat_read): Failed to read 'cols' from file." );

  matrix* N = mat_init( r, c );
  float* p = N->e;

  for( uint i=0; i<r*c; i++ ) {
    scan = fscanf( f, "%f", &val );
    mat_err( ( scan == EOF ), "Error (mat_read): Matrix is missing elements." );
    *(p++) = val;
  }

  scan = fscanf( f, "%f", &val );
  mat_err( ( scan != EOF ), "Error (mat_read): Matrix has extra elements." );

  fclose(f);

  return N;
}




/*******************************************************************************
* void mat_write ( matrix* M, char* file )
* Writes a matrix to a file.
*******************************************************************************/
void mat_write ( matrix* M, char* file ) {

  FILE* f = fopen( file, "w" );
  mat_err( ( f == NULL ), "Error (mat_write): Cannot open file.\n" );

  fprintf( f, "# %d %d \n", M->r, M->c );
  for( uint i=0; i<M->r; i++ ) {
    for( uint j=0; j<M->c; j++ ) {
      fprintf( f, " %e", *( M->e + i*M->c + j ) );
    }
    fprintf( f, "\n" );
  }

  fclose(f);

  return;
}




/*******************************************************************************
* float mat_get ( matrix* M, uint r, uint c )
* Returns the value of a matrix element.
*******************************************************************************/
float mat_get ( matrix* M, uint r, uint c ) {

  mat_err( ( !r || r > M->r ), "Error (mat_get): Row index exceeds matrix dimensions."    );
  mat_err( ( !c || c > M->c ), "Error (mat_get): Column index exceeds matrix dimensions." );

  return *( M->e + (r-1) * M->c + (c-1) );
}




/*******************************************************************************
* matrix* mat_getr ( matrix* M, uint r )
* Returns the specified r of a matrix.
*******************************************************************************/
matrix* mat_getr ( matrix* M, uint r ) {

  mat_err( ( !r || r > M->r ), "Error (mat_getr): Row index exceeds matrix dimensions." );

  matrix* N = mat_init( 1, M->c );

  for( uint i=0; i<M->c; i++ )  *(N->e+i) = *( M->e + (r-1) * M->c + i );

  return N;
}




/*******************************************************************************
* matrix* mat_getc ( matrix* M, uint c )
* Returns the specified column of a matrix.
*******************************************************************************/
matrix* mat_getc ( matrix* M, uint c ) {

  mat_err( ( !c || c > M->c ), "Error (mat_getc): Column index exceeds matrix dimensions." );

  matrix* N = mat_init( M->r, 1 );

  for( uint i=0; i<M->r; i++ )  *(N->e+i) = *( M->e + i * M->c + (c-1) );

  return N;
}




/*******************************************************************************
* void mat_set ( matrix* M, uint r, uint c, float val )
* Assigns a value into a matrix element.
*******************************************************************************/
void mat_set ( matrix* M, uint r, uint c, float val ) {

  mat_err( ( !r || r > M->r ), "Error (mat_set): Row index exceeds matrix dimensions."    );
  mat_err( ( !c || c > M->c ), "Error (mat_set): Column index exceeds matrix dimensions." );

  *( M->e + (r-1) * M->c + (c-1) ) = val;

  return;
}




/*******************************************************************************
* void mat_setr ( matrix* M, uint r, matrix* V )
* Replaces a row of a matrix with the specified vector.
*******************************************************************************/
void mat_setr ( matrix* M, uint r, matrix* V ) {

  mat_err( ( !r || r > M->r ), "Error (mat_setr): Row index exceeds matrix dimensions."           );
  mat_err( ( V->r !=1 ),       "Error (mat_setr): Input array must be a row vector."              );
  mat_err( ( M->c != V->c ),   "Error (mat_setr): Input array and matrix must be the same width." );

  for( uint i=0; i<M->c; i++ )  *( M->e + (r-1) * M->c + i ) = *(V->e+i);

  return;
}




/*******************************************************************************
* void mat_setc ( matrix* M, uint c, matrix* V )
* Replaces a column of a matrix with the specified vector.
*******************************************************************************/
void mat_setc ( matrix* M, uint c, matrix* V ) {

  mat_err( ( !c || c > M->c ), "Error (mat_setc): Column index exceeds matrix dimensions."         );
  mat_err( ( V->c !=1 ),       "Error (mat_setc): Input array must be a column vector."            );
  mat_err( ( M->r != V->r ),   "Error (mat_setc): Input array and matrix must be the same height." );

  for( uint i=0; i<M->r; i++ )  *( M->e + i * M->c + (c-1) ) = *(V->e+i);

  return;
}




/*******************************************************************************
* matrix* mat_copy ( matrix* M )
* Copies a matrix into a new matrix.
*******************************************************************************/
matrix* mat_copy ( matrix* M ) {

  matrix* N = mat_init( M->r, M->c );

  memcpy( N->e, M->e, M->r * M->c * sizeof(float) );

  return N;
}




/*******************************************************************************
* matrix* mat_eye ( uint n )
* Creates an identity matrix of dimension n.
*******************************************************************************/
matrix* mat_eye ( uint n ) {

  mat_err( (!n), "Error (mat_eye): Matrix dimension must be positive." );

  matrix* N = mat_init( n, n );

  for( uint i=0; i<n*n; i+=(n+1) )  *(N->e+i) = 1.0;

  return N;
}




/*******************************************************************************
* matrix* mat_ones ( uint r, uint c )
* Creates a new matrix filled with values of one.
*******************************************************************************/
matrix* mat_ones ( uint r, uint c ) {

  mat_err( (!r), "Error (mat_ones): Matrix rows must be a positive."    );
  mat_err( (!c), "Error (mat_ones): Matrix columns must be a positive." );

  matrix* N = mat_init( r, c );

  for( uint i=0; i<r*c; i++ )  *(N->e+i) = 1.0;

  return N;
}




/*******************************************************************************
* matrix* mat_scale ( matrix* M, float scale )
* Multiplies a matrix by a scalar with type float.
*******************************************************************************/
matrix* mat_scale ( matrix* M, float scale ) {

  matrix* N = mat_init( M->r, M->c );

  memcpy( N->e, M->e, M->r * M->c * sizeof(float) );

  for( uint i=0; i < N->r * N->c; i++ )  *(N->e+i) *= scale;

  return N;
}




/*******************************************************************************
* void mat_swapr ( matrix* M, uint p, uint q )
* Swaps rows within a matrix.
*******************************************************************************/
void mat_swapr ( matrix* M, uint p, uint q ) {

  mat_err( ( M->r < 2 ),       "Error (mat_swapr): Matrix must have at least two rows." );
  mat_err( ( !p || p > M->r ), "Error (mat_swapr): Row index exceeds matrix dimension." );
  mat_err( ( !q || q > M->r ), "Error (mat_swapr): Row index exceeds matrix dimension." );

  if( p == q )  return;

  for( uint i=0; i<M->c; i++ ) {
    float tmp = *( M->e + (p-1) * (M->c) + i );
    *( M->e + (p-1) * (M->c) + i ) = *( M->e + (q-1) * (M->c) + i );
    *( M->e + (q-1) * (M->c) + i ) = tmp;
  }

  return;
}




/*******************************************************************************
* void mat_swapc ( matrix* M, uint p, uint q )
* Swaps columns within a matrix.
*******************************************************************************/
void mat_swapc ( matrix* M, uint p, uint q ) {

  mat_err( ( M->c < 2 ),       "Error (mat_swapc): Matrix must have at least two columns." );
  mat_err( ( !p || p > M->c ), "Error (mat_swapc): Column index exceeds matrix dimension." );
  mat_err( ( !q || q > M->c ), "Error (mat_swapc): Column index exceeds matrix dimension." );

  if ( p == q )  return;

  for( uint i=0; i<M->r; i++ ) {
    float tmp = *( M->e + i*M->c + (p-1) );
    *( M->e + i*M->c + (p-1) ) = *( M->e + i*M->c + (q-1) );
    *( M->e + i*M->c + (q-1) ) = tmp;
  }

  return;
}




/*******************************************************************************
* matrix* mat_appr ( matrix* T, matrix* B )
* Appends two matrices, top to bottom.
*******************************************************************************/
matrix* mat_appr ( matrix* T, matrix* B ) {

  mat_err( ( T->c != B->c ), "Error (mat_appr): Matrices must be the same width." );

  matrix* N = mat_init( T->r + B->r, T->c );

  memcpy( N->e,               T->e, T->r * T->c * sizeof(float) );
  memcpy( N->e + T->r * T->c, B->e, B->r * T->c * sizeof(float) );

  return N;
}




/*******************************************************************************
* matrix* mat_appc ( matrix* L, matrix* R )
* Appends two matrices, left to right.
*******************************************************************************/
matrix* mat_appc ( matrix* L, matrix* R ) {

  mat_err( ( L->r != R->r ), "Error (mat_appc): Matrices must be the same height." );

  matrix* N = mat_init( L->r, L->c + R->c );

  for( uint i=0; i<L->r; i++ ) {
    memcpy( N->e + i*N->c,         L->e + i*L->c, L->c * sizeof(float) );
    memcpy( N->e + i*N->c + L->c , R->e + i*R->c, R->c * sizeof(float) );
  }

  return N;
}




/*******************************************************************************
* void mat_rmtiny ( matrix* M, float tol )
* Matrix entries smaller than 'tol' are replaced with values of zero.
*******************************************************************************/
void mat_rmtiny ( matrix* M, float tol ) {

  mat_err( ( tol < 0.0 ), "Error (mat_rmtiny): Tolerance must be nonnegative." );

  for( uint i=0; i < M->r * M->c; i++ ) {
    if( fabsf( *(M->e+i) ) < tol )  *(M->e+i) = 0.0;
  }

  return;
}



