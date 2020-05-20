/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matComplex.c
* Source code for complex matrix functions within the 'matLib' library.
*
*******************************************************************************/
#include "../inc/matComplex.h"




/*******************************************************************************
* matrixz* mat_initz ( uint r, uint c )
* Initializes a new complex matrix with the specified dimensions,
* and sets the elements to complex values of zero.
*******************************************************************************/
matrixz* mat_initz ( uint r, uint c ) {

  mat_err( ( !r || !c ), "Error (mat_initz): Matrix dimensions must be positive." );

  matrixz* N = (matrixz*) malloc( sizeof(matrixz) );
  mat_err( ( N == NULL ), "Error (mat_initz): Matrix structure returned NULL." );

  N->r = r;
  N->c = c;

  N->e = (float complex*) malloc( r * c * sizeof(float complex) );
  mat_err( ( N->e == NULL ), "Error (mat_initz): Matrix data returned NULL." );

  memset( N->e, 0.0, r * c * sizeof(float complex) );

  return out;
}




/*******************************************************************************
* void mat_clearz ( matrixz* M )
* Destroys an existing complex matrix and frees the memory.
*******************************************************************************/
void mat_clearz ( matrixz* M ) {

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
* void mat_printz ( matrixz* M )
* Display a complex matrix in the terminal.
*******************************************************************************/
void mat_printz ( matrixz* M ) {

  printf( "[%dx%d]\n", M->r, M->c );
  for( uint i=1; i<=M->r; i++ ) {
    for( uint j=1; j<=M->c; j++ ) {
      float re = mat_getre( M, i, j );
      float im = mat_getim( M, i, j );
      char sign;
      if(im<0)  sign = '-';
      else      sign = '+';
      printf( " %9.4f  %c%9.4f i\t", re, sign, fabs(im) );
    }
    printf("\n");
  }

  return;
}




/*******************************************************************************
* matrixz* mat_readz ( char* file )
* Reads a complex matrix from a file.
*******************************************************************************/
matrixz* mat_readz ( char* file ) {

  uint r, c;
  int scan;
  float re, im;
  char sign;

  FILE* f = fopen( file, "r" );
  mat_err( ( f == NULL ), "Error (mat_readz): Cannot open file." );

  scan = fscanf( f, "#" );
  mat_err( ( scan == EOF ), "Error (mat_readz): Failed to read 'header' from file." );

  scan = fscanf( f, "%u", &r );
  mat_err( ( scan == EOF ), "Error (mat_readz): Failed to read 'rows' from file." );

  scan = fscanf( f, "%u", &c );
  mat_err( ( scan == EOF ), "Error (mat_readz): Failed to read 'cols' from file." );

  matrixz* M = mat_initz( r, c );
//  float complex* data = M->e;

  for( uint i=0; i<r*c; i++ ) {
    scan = fscanf( f, "%f %c %f i", &re, &sign, &im );
    mat_err( ( scan == EOF ), "Error (mat_readz): Matrix is missing elements." );
    if( sign == '-' )  im *= -1.0;
//    *(data++) = re + im*I;
    *((M->e)++) = re + im*I;
  }

  scan = fscanf( f, "%f %c %f i", &re, &sign, &im );
  mat_err( ( scan != EOF ), "Error (mat_readz): Matrix has extra elements." );

  fclose(f);

  return out;
}




/*******************************************************************************
* void mat_writez ( matrixz* M, char* file )
* Writes a complex matrix to a file.
*******************************************************************************/
void mat_writez ( matrixz* M, char* file ) {

  float re, im;
  char sign;

  FILE* f = fopen( file, "w" );
  mat_err( ( f == NULL ), "Error (mat_writez): Cannot open file.\n" );

  fprintf( f, "# %d %d \n", M->r, M->c );
  for( uint i=1; i<=M->r; i++ ) {
    for( uint j=1; j<=M->c; j++ ) {
      re = mat_getre( M, i, j );
      im = mat_getim( M, i, j );
      if(im<0)  sign = '-';
      else      sign = '+';
      fprintf( f, " %e %c%e i\t", re, sign, fabs(im) );
    }
    fprintf( f, "\n" );
  }

  fclose(f);

  return;
}




/*******************************************************************************
* float mat_getre ( matrixz* M, uint r, uint c )
* Returns the real part of a complex matrix element.
*******************************************************************************/
float mat_getre ( matrixz* M, uint r, uint c ) {

  mat_err( ( !r || r > M->r ), "Error (mat_getre): Row index exceeds matrix dimensions."    );
  mat_err( ( !c || c > M->c ), "Error (mat_getre): Column index exceeds matrix dimensions." );

  return (float)creal( *( M->e + (r-1) * M->c + (c-1) ) );
}




/*******************************************************************************
* float mat_getim ( matrixz* M, uint r, uint c )
* Returns the imaginary part of a complex matrix element.
*******************************************************************************/
float mat_getim ( matrixz* M, uint r, uint c ) {

  mat_err( ( !r || r > M->r ), "Error (mat_getim): Row index exceeds matrix dimensions."    );
  mat_err( ( !c || c > M->c ), "Error (mat_getim): Column index exceeds matrix dimensions." );

  return (float)cimag( *( M->e + (r-1) * M->c + (c-1) ) );
}




/*******************************************************************************
* matrixz* mat_getrz ( matrixz* M, uint r ) {
* Returns the specified complex row vector of a matrix.
*******************************************************************************/
matrixz* mat_getrz ( matrixz* M, uint r ) {

  mat_err( ( !r || r > M->r ), "Error (mat_getrz): Row index exceeds matrix dimensions." );

  matrixz* N = mat_initz( 1, M->c );

  for( uint i=0; i<M->c; i++ )  *(N->e+i) = *( M->e + (r-1) * M->c + i );

  return N;
}




/*******************************************************************************
* matrixz* mat_getcz ( matrixz* M, uint c )
* Returns the specified complex column vector of a matrix.
*******************************************************************************/
matrixz* mat_getcz ( matrixz* M, uint c ) {

  mat_err( ( !c || c > M->c ), "Error (mat_getcz): Column index exceeds matrix dimensions." );

  matrixz* N = mat_initz( M->r, 1 );

  for( uint i=0; i<M->r; i++ )  *(N->e+i) = *( M->e + i * M->c + (c-1) );

  return N;
}




/*******************************************************************************
* void mat_setz ( matrixz* M, uint r, uint c, float re, float im )
* Assigns a complex number into a matrix element.
*******************************************************************************/
void mat_setz ( matrixz* M, uint r, uint c, float re, float im ) {

  mat_err( ( !r || r > M->r ), "Error (mat_setz): Row index exceeds matrix dimensions."    );
  mat_err( ( !c || c > M->c ), "Error (mat_setz): Column index exceeds matrix dimensions." );

  *( M->e + (r-1) * M->c + (c-1) ) = re + im *I;

  return;
}




/*******************************************************************************
* void mat_setrz ( matrixz* M, uint r, matrixz* V )
* Replaces a row of a complex matrix with the specified vector.
*******************************************************************************/
void mat_setrz ( matrixz* M, uint r, matrixz* V ) {

  mat_err( ( !r || r > M->r ), "Error (mat_setrz): Row index exceeds matrix dimensions."           );
  mat_err( ( V->r !=1 ),       "Error (mat_setrz): Input array must be a row vector."              );
  mat_err( ( M->c != M->c ),   "Error (mat_setrz): Input array and matrix must be the same width." );

  for( uint i=0; i<M->c; i++ )  *( M->e + (r-1) * M->c + i ) = *(V->e+i);

  return;
}




/*******************************************************************************
* void mat_setcz ( matrixz* M, uint c, matrixz* V )
* Replaces a column of a complex matrix with the specified vector.
*******************************************************************************/
void mat_setcz ( matrixz* M, uint c, matrixz* V ) {

  mat_err( ( !c || c > M->c ), "Error (mat_setcz): Column index exceeds matrix dimensions."         );
  mat_err( ( V->c !=1 ),       "Error (mat_setcz): Input array must be a column vector."            );
  mat_err( ( M->r != V->r ),   "Error (mat_setcz): Input array and matrix must be the same height." );

  for( uint i=0; i<M->r; i++ )  *( M->e + i * M->c + (c-1) ) = *(V->e+i);

  return;
}



