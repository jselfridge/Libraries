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
* Initializes a new matrix with the specified dimensions,
* and sets the elements to complex values of zero.
*******************************************************************************/
// matrixz* mat_initz ( uint rows, uint cols ) {

//   mat_err( ( rows<1 || cols<1 ), "Error (mat_initz): Matrix dimensions must be positive." );

//   matrixz *out;
//   out = (matrixz *) malloc( sizeof(matrixz) );
//   mat_err( ( out == NULL ), "Error (mat_initz): Matrix structure returned NULL." );

//   out->rows = rows;
//   out->cols = cols;
//   out->data = (float complex *) malloc( rows * cols * sizeof(float complex) );

//   mat_err( ( out->data == NULL ), "Error (mat_initz): Matrix data returned NULL." );
//   memset( out->data, 0.0, rows * cols * sizeof(float complex) );

//   return out;
// }




/*******************************************************************************
* matrixz* mat_readz ( char *file )
* Reads a complex matrix from a file.
*******************************************************************************/
// matrixz* mat_readz ( char *file ) {

//   FILE *f;
//   uint i, r, c, n;
//   int scan;
//   float re, im;
//   char sign;
//   matrixz *out;
//   float complex *data;

//   f = fopen( file, "r" );
//   mat_err( f==NULL, "Error (mat_readz): Cannont open file." );

//   scan = fscanf( f, "#" );
//   mat_err( scan==EOF, "Error (mat_readz): Failed to read 'header' from file." );

//   scan = fscanf( f, "%d", &r );
//   mat_err( scan==EOF, "Error (mat_readz): Failed to read 'rows' from file." );

//   scan = fscanf( f, "%d", &c );
//   mat_err( scan==EOF, "Error (mat_readz): Failed to read 'cols' from file." );

//   n = r * c;
//   out = mat_initz(r,c);
//   data = out->data;

//   for( i=0; i<n; i++ ) {
//     scan = fscanf( f, "%f %c %f i", &re, &sign, &im );
//     mat_err( scan==EOF, "Error (mat_readz): Matrix is missing elements." );
//     if( sign == '-' )  im *= -1.0;
//     *data = re + im*I;
//     data++;
//   }

//   scan = fscanf( f, "%f %c %f i", &re, &sign, &im );
//   mat_err( scan!=EOF, "Error (mat_readz): Matrix has extra elements." );

//   fclose(f);

//   return out;
// }




/*******************************************************************************
* void mat_printz ( matrixz *mat )
* Display a complex matrix in the terminal.
*******************************************************************************/
// void mat_printz ( matrixz *mat ) {

//   uint r, c, i, j;
//   char sign;
//   float re, im;

//   r = mat->rows;
//   c = mat->cols;

//   printf( "[%dx%d]\n", r, c );
//   for( i=1; i<=r; i++ ) {
//     for( j=1; j<=c; j++ ) {
//       re = mat_getre( mat, i, j );
//       im = mat_getim( mat, i, j );
//       if(im<0)  sign = '-';
//       else      sign = '+';
//       printf( " %9.4f  %c%9.4f i\t", re, sign, fabs(im) );
//     }
//     printf("\n");
//   }

//   return;
// }




/*******************************************************************************
* void mat_writez ( matrixz *mat, char *file )
* Writes a complex matrix to a file.
*******************************************************************************/
// void mat_writez ( matrixz *mat, char *file ) {

//   FILE *f;
//   uint r, c, i, j;
//   float re, im;
//   char sign;

//   r = mat->rows;
//   c = mat->cols;

//   f = fopen( file, "w" );
//   mat_err( f==NULL, "Error (mat_writez): Cannot open file." );

//   fprintf( f, "# %d %d \n", r, c );
//   for( i=1; i<=r; i++ ) {
//     for( j=1; j<=c; j++ ) {
//       re = mat_getre( mat, i, j );
//       im = mat_getim( mat, i, j );
//       if(im<0)  sign = '-';
//       else      sign = '+';
//       fprintf( f, " %4.6f %c%4.6f i\t", re, sign, fabs(im) );
//     }
//     fprintf( f, "\n" );
//   }

//   fclose(f);
//   return;
// }




/*******************************************************************************
* void mat_clearz ( matrixz *mat )
* Destroys an existing complex matrix and frees the memory.
*******************************************************************************/
// void mat_clearz ( matrixz *mat ) {

//   float complex *data = mat->data;

//   if( mat != NULL ) {
//     if( data != NULL ) {
//       free( data );
//       data = NULL;
//     }
//     free(mat);
//     mat = NULL;
//   }

//   return;
// }




/*******************************************************************************
* float mat_getre ( matrixz *mat, uint row, uint col )
* Returns the real part of a complex matrix element.
*******************************************************************************/
// float mat_getre ( matrixz *mat, uint row, uint col ) {

//   mat_err( row > mat->rows, "Error (mat_getre): Row index exceeds matrix dimensions."    );
//   mat_err( col > mat->cols, "Error (mat_getre): Column index exceeds matrix dimensions." );
//   mat_err( row < 1,         "Error (mat_getre): Row index must be positive."             );
//   mat_err( col < 1,         "Error (mat_getre): Column index must be positive."          );

//   float re;
//   float complex *data = mat->data;
//   uint offset = (row-1) * (mat->cols) + (col-1);

//   data += offset;
//   re = creal(*data);

//   return re;
// }




/*******************************************************************************
* float mat_getim ( matrixz *mat, uint row, uint col )
* Returns the imaginary part of a complex matrix element.
*******************************************************************************/
// float mat_getim ( matrixz *mat, uint row, uint col ) {

//   mat_err( row > mat->rows, "Error (mat_getim): Row index exceeds matrix dimensions."    );
//   mat_err( col > mat->cols, "Error (mat_getim): Column index exceeds matrix dimensions." );
//   mat_err( row < 1,         "Error (mat_getim): Row index must be positive."             );
//   mat_err( col < 1,         "Error (mat_getim): Column index must be positive."          );

//   float im;
//   float complex *data = mat->data;
//   uint offset = (row-1) * (mat->cols) + (col-1);

//   data += offset;
//   im = cimag(*data);

//   return im;
// }




/*******************************************************************************
* matrixz* mat_getrz ( matrixz *mat, uint row ) {
* Returns the specified complex row vector of a matrix.
*******************************************************************************/
// matrixz* mat_getrz ( matrixz *mat, uint row ) {

//   mat_err( row > mat->rows, "Error (mat_getrz): Row index exceeds matrix dimensions." );
//   mat_err( row < 1,         "Error (mat_getrz): Row index must be positive."          );

//   uint i, c;
//   matrixz *out;

//   c = mat->cols;
//   out = mat_initz(1,c);

//   for( i=1; i<=c; i++ )  mat_setz( out, 1, i, mat_getre( mat, row, i ), mat_getim( mat, row, i ) );

//   return out;
// }




/*******************************************************************************
* matrixz* mat_getcz ( matrixz *mat, uint col )
* Returns the specified complex column vector of a matrix.
*******************************************************************************/
// matrixz* mat_getcz ( matrixz *mat, uint col ) {

//   mat_err( col > mat->cols, "Error (mat_getcz): Column index exceeds matrix dimensions." );
//   mat_err( col < 1,         "Error (mat_getcz): Column index must be positive."          );

//   uint i, r;
//   matrixz *out;

//   r = mat->rows;
//   out = mat_initz(r,1);
  
//   for( i=1; i<=r; i++ )  mat_setz( out, i, 1, mat_getre( mat, i, col ), mat_getim( mat, i, col ) );

//   return out;
// }




/*******************************************************************************
* void mat_setz ( matrixz *mat, uint row, uint col, float re, float im )
* Assigns a complex number into a matrix element.
*******************************************************************************/
// void mat_setz ( matrixz *mat, uint row, uint col, float re, float im ) {

//   mat_err( row > mat->rows, "Error (mat_setz): Row index exceeds matrix dimensions."    );
//   mat_err( col > mat->cols, "Error (mat_setz): Column index exceeds matrix dimensions." );
//   mat_err( row < 1,         "Error (mat_setz): Row index must be positive."             );
//   mat_err( col < 1,         "Error (mat_setz): Column index must be positive."          );

//   float complex *data = mat->data;
//   uint offset = (row-1) * (mat->cols) + (col-1);

//   data += offset;
//   *data = re + im *I;

//   return;
// }




/*******************************************************************************
* void mat_setrz ( matrixz *mat, uint row, matrixz *vec )
* Replaces a row of a complex matrix with the specified vector.
*******************************************************************************/
// void mat_setrz ( matrixz *mat, uint row, matrixz *vec ) {

//   mat_err( row > mat->rows,        "Error (mat_setrz): Row index exceeds matrix dimensions."           );
//   mat_err( row < 1,                "Error (mat_setrz): Row index must be positive."                    );
//   mat_err( vec->rows != 1,         "Error (mat_setrz): Input array must be a row vector."              );
//   mat_err( mat->cols != vec->cols, "Error (mat_setrz): Input array and matrix must be the same width." );

//   uint i;
//   for( i=1; i <= mat->cols; i++ )  mat_setz( mat, row, i, mat_getre( vec, 1, i ), mat_getim( vec, 1, i ) );

//   return;
// }




/*******************************************************************************
* void mat_setcz ( matrixz *mat, uint col, matrixz *vec )
* Replaces a column of a complex matrix with the specified vector.
*******************************************************************************/
// void mat_setcz ( matrixz *mat, uint col, matrixz *vec ) {

//   mat_err( col > mat->cols,        "Error (mat_setcz): Column index exceeds matrix dimensions."         );
//   mat_err( col < 1,                "Error (mat_setcz): Column index must be positive."                  );
//   mat_err( vec->cols != 1,         "Error (mat_setcz): Input array must be a column vector."            );
//   mat_err( mat->rows != vec->rows, "Error (mat_setcz): Input array and matrix must be the same height." );

//   uint i;
//   for( i=1; i <= mat->rows; i++ )  mat_setz( mat, i, col, mat_getre( vec, i, 1 ), mat_getim( vec, i, 1 ) );

//   return;
// }



