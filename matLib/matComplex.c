/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matComplex.c
* Debugging program for tetsing the 'matComplex' library functions.
*
*******************************************************************************/
#include "matLib.h"




/*******************************************************************************
* matrixz* mat_initz ( uint rows, uint cols )
* Initializes a new complex matrix with the specified dimensions,
* and sets the elements to complex values of zero.
*******************************************************************************/
matrixz* mat_initz ( uint rows, uint cols ) {

  mat_err( ( !rows || !cols ), "Error (mat_initz): Matrix dimensions must be positive." );

  matrixz* out = (matrixz*) malloc( sizeof(matrixz) );
  mat_err( ( out == NULL ), "Error (mat_initz): Matrix structure returned NULL." );

  out->rows = rows;
  out->cols = cols;

  out->data = (float complex*) malloc( rows * cols * sizeof(float complex) );
  mat_err( ( out->data == NULL ), "Error (mat_initz): Matrix data returned NULL." );

  memset( out->data, 0.0, rows * cols * sizeof(float complex) );

  return out;
}




/*******************************************************************************
* void mat_clearz ( matrixz* mat )
* Destroys an existing complex matrix and frees the memory.
*******************************************************************************/
void mat_clearz ( matrixz* mat ) {

  if( mat != NULL ) {
    if( mat->data != NULL ) {
      free(mat->data);
      mat->data = NULL;
    }
    free(mat);
    mat = NULL;
  }

  return;
}




/*******************************************************************************
* void mat_printz ( matrixz* mat )
* Display a complex matrix in the terminal.
*******************************************************************************/
void mat_printz ( matrixz* mat ) {

  printf( "[%dx%d]\n", mat->rows, mat->cols );
  for( uint i=1; i<=mat->rows; i++ ) {
    for( uint j=1; j<=mat->cols; j++ ) {
      float re = mat_getre( mat, i, j );
      float im = mat_getim( mat, i, j );
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

  matrixz* out = mat_initz( r, c );
  float complex* data = out->data;

  for( uint i=0; i<r*c; i++ ) {
    scan = fscanf( f, "%f %c %f i", &re, &sign, &im );
    mat_err( ( scan == EOF ), "Error (mat_readz): Matrix is missing elements." );
    if( sign == '-' )  im *= -1.0;
    *(data++) = re + im*I;
  }

  scan = fscanf( f, "%f %c %f i", &re, &sign, &im );
  mat_err( ( scan != EOF ), "Error (mat_readz): Matrix has extra elements." );

  fclose(f);

  return out;
}




/*******************************************************************************
* void mat_writez ( matrixz* mat, char* file )
* Writes a complex matrix to a file.
*******************************************************************************/
void mat_writez ( matrixz* mat, char* file ) {

  float re, im;
  char sign;

  FILE* f = fopen( file, "w" );
  mat_err( ( f == NULL ), "Error (mat_writez): Cannot open file.\n" );

  fprintf( f, "# %d %d \n", mat->rows, mat->cols );
  for( uint i=1; i<=mat->rows; i++ ) {
    for( uint j=1; j<=mat->cols; j++ ) {
      re = mat_getre( mat, i, j );
      im = mat_getim( mat, i, j );
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
* float mat_getre ( matrixz* mat, uint row, uint col )
* Returns the real part of a complex matrix element.
*******************************************************************************/
float mat_getre ( matrixz* mat, uint row, uint col ) {

  mat_err( ( !row || row > mat->rows ), "Error (mat_getre): Row index exceeds matrix dimensions."    );
  mat_err( ( !col || col > mat->cols ), "Error (mat_getre): Column index exceeds matrix dimensions." );

  return (float)creal( *( mat->data + (row-1) * (mat->cols) + (col-1) ) );
}




/*******************************************************************************
* float mat_getim ( matrixz* mat, uint row, uint col )
* Returns the imaginary part of a complex matrix element.
*******************************************************************************/
float mat_getim ( matrixz* mat, uint row, uint col ) {

  mat_err( ( !row || row > mat->rows ), "Error (mat_getim): Row index exceeds matrix dimensions."    );
  mat_err( ( !col || col > mat->cols ), "Error (mat_getim): Column index exceeds matrix dimensions." );

  return (float)cimag( *( mat->data + (row-1) * (mat->cols) + (col-1) ) );
}




/*******************************************************************************
* matrixz* mat_getrz ( matrixz* mat, uint row ) {
* Returns the specified complex row vector of a matrix.
*******************************************************************************/
matrixz* mat_getrz ( matrixz* mat, uint row ) {

  mat_err( ( !row || row > mat->rows ), "Error (mat_getrz): Row index exceeds matrix dimensions." );

  matrixz* out = mat_initz( 1, mat->cols );

  for( uint i=0; i<mat->cols; i++ )  *(out->data+i) = *( mat->data + (row-1) * mat->cols + i );

  return out;
}




/*******************************************************************************
* matrixz* mat_getcz ( matrixz* mat, uint col )
* Returns the specified complex column vector of a matrix.
*******************************************************************************/
matrixz* mat_getcz ( matrixz* mat, uint col ) {

  mat_err( ( !col || col > mat->cols ), "Error (mat_getcz): Column index exceeds matrix dimensions." );

  matrixz* out = mat_initz( mat->rows, 1 );

  for( uint i=0; i<mat->rows; i++ )  *(out->data+i) = *( mat->data + ( i * mat->cols ) + (col-1) );

  return out;
}




/*******************************************************************************
* void mat_setz ( matrixz* mat, uint row, uint col, float re, float im )
* Assigns a complex number into a matrix element.
*******************************************************************************/
void mat_setz ( matrixz* mat, uint row, uint col, float re, float im ) {

  mat_err( ( !row || row > mat->rows ), "Error (mat_setz): Row index exceeds matrix dimensions."    );
  mat_err( ( !col || col > mat->cols ), "Error (mat_setz): Column index exceeds matrix dimensions." );

  *( mat->data + (row-1) * (mat->cols) + (col-1) ) = re + im *I;

  return;
}




/*******************************************************************************
* void mat_setrz ( matrixz* mat, uint row, matrixz* vec )
* Replaces a row of a complex matrix with the specified vector.
*******************************************************************************/
void mat_setrz ( matrixz* mat, uint row, matrixz* vec ) {

  mat_err( ( !row || row > mat->rows ), "Error (mat_setrz): Row index exceeds matrix dimensions."           );
  mat_err( ( vec->rows !=1 ),           "Error (mat_setrz): Input array must be a row vector."              );
  mat_err( ( mat->cols != vec->cols ),  "Error (mat_setrz): Input array and matrix must be the same width." );

  for( uint i=0; i<mat->cols; i++ )  *( mat->data + (row-1) * (mat->cols) + i ) = *( vec->data+i );

  return;
}




/*******************************************************************************
* void mat_setcz ( matrixz* mat, uint col, matrixz* vec )
* Replaces a column of a complex matrix with the specified vector.
*******************************************************************************/
void mat_setcz ( matrixz* mat, uint col, matrixz* vec ) {

  mat_err( ( !col || col > mat->cols ), "Error (mat_setcz): Column index exceeds matrix dimensions."         );
  mat_err( ( vec->cols !=1 ),           "Error (mat_setcz): Input array must be a column vector."            );
  mat_err( ( mat->rows != vec->rows ),  "Error (mat_setcz): Input array and matrix must be the same height." );

  for( uint i=0; i<mat->rows; i++ )  *( mat->data + ( i * mat->cols ) + (col-1) ) = *( vec->data+i );

  return;
}



