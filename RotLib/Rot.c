
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Rot.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "RotLib.h"




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  RotConv
//  Rotation functions that perform some type of conversion.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_d2r
//  Converts the angles of a matrix from degrees into radians.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_d2r ( matrix* deg ) {

  int r = deg->rows;
  int c = deg->cols;
  int n = r*c;

  matrix* rad   = mat_init(r,c);
  double* ddata = deg->data;
  double* rdata = rad->data;

  for ( int i=0; i<n; i++ ) {
    *rdata = *ddata * (PI/180.0);
    ddata++;
    rdata++;
  }

  return rad;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_r2d
//  Converts the angles of matrix from radians into degrees.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_r2d ( matrix* rad ) {

  int r = rad->rows;
  int c = rad->cols;
  int n = r*c;

  matrix* deg   = mat_init(r,c);
  double* ddata = deg->data;
  double* rdata = rad->data;

  for ( int i=0; i<n; i++ ) {
    *ddata = *rdata * (180.0/PI);
    ddata++;
    rdata++;
  }

  return deg;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_wrappi
//  Places the elements of a matrix within the range (-pi,pi].
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_wrappi ( matrix* rad ) {

  int r = rad->rows;
  int c = rad->cols;
  int n = r*c;

  matrix* wrap  = mat_init(r,c);
  double* rdata = rad->data;
  double* wdata = wrap->data;

  for ( int i=0; i<n; i++ ) {
    double elem = *rdata;
    while ( elem >   PI ) { elem -= PI2; }
    while ( elem <= -PI ) { elem += PI2; }
    *wdata = elem;
    rdata++;
    wdata++;
  }

  return wrap;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_wrap2pi
//  Places the elements of a matrix within the range [0,2pi).
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_wrap2pi ( matrix* rad ) {

  int r = rad->rows;
  int c = rad->cols;
  int n = r*c;

  matrix* wrap  = mat_init(r,c);
  double* rdata = rad->data;
  double* wdata = wrap->data;

  for ( int i=0; i<n; i++ ) {
    double elem = *rdata;
    while ( elem >= PI2 ) { elem -= PI2; }
    while ( elem <   0  ) { elem += PI2; }
    *wdata = elem;
    rdata++;
    wdata++;
  }

  return wrap;
}




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  RotEuler
//  Functions that perform Euler rotations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_xaxis
//  Generates a rotation matrix around the X-axis.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_xaxis ( double angle ) {

  matrix* R = mat_init(3,3);
  double  S = sin(angle);
  double  C = cos(angle);

  mat_set( R,1,1, 1.0 );  mat_set( R,1,2, 0.0 );  mat_set( R,1,3, 0.0 );
  mat_set( R,2,1, 0.0 );  mat_set( R,2,2,  C  );  mat_set( R,2,3, -S  );
  mat_set( R,3,1, 0.0 );  mat_set( R,3,2,  S  );  mat_set( R,3,3,  C  );

  return R;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_yaxis
//  Generates a rotation matrix around the Y-axis.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_yaxis ( double angle ) {

  matrix* R = mat_init(3,3);
  double  S = sin(angle);
  double  C = cos(angle);

  mat_set( R,1,1,  C  );  mat_set( R,1,2, 0.0 );  mat_set( R,1,3,  S );
  mat_set( R,2,1, 0.0 );  mat_set( R,2,2, 1.0 );  mat_set( R,2,3, 0.0 );
  mat_set( R,3,1, -S  );  mat_set( R,3,2, 0.0 );  mat_set( R,3,3,  C  );

  return R;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_zaxis
//  Generates a rotation matrix around the Z-axis.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_zaxis ( double angle ) {

  matrix* R = mat_init(3,3);
  double  S = sin(angle);
  double  C = cos(angle);

  mat_set( R,1,1,  C  );  mat_set( R,1,2, -S  );  mat_set( R,1,3, 0.0 );
  mat_set( R,2,1,  S  );  mat_set( R,2,2,  C  );  mat_set( R,2,3, 0.0 );
  mat_set( R,3,1, 0.0 );  mat_set( R,3,2, 0.0 );  mat_set( R,3,3, 1.0 );

  return R;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_eul
//  Rotation matrix that transforms from local (body) frame to 
//  global (inertial) frame.  The transpose of this matrix 
//  reverses the relationship.
//  Xi = R * Xb , Xb = R' * Xi
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_eul ( matrix* att ) {

  mat_err( att->rows!=3 || att->cols!=1, "Error (rot_eul): Attitude must be a 3 element column vector." );

  matrix* R = mat_init(3,3);
  double  X = mat_get(att,1,1);
  double  Y = mat_get(att,2,1);
  double  Z = mat_get(att,3,1);

  R =  mat_mul( rot_zaxis(Z), rot_yaxis(Y) ); 
  R =  mat_mul( R, rot_xaxis(X) ); 

  return R;
}




//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  RotQuat
//  Functions that perform quaternion manipulations.
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  rot_e2q
//  Converts an Euler attitude vector to quaternion vector.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* rot_e2q ( matrix* att ) {

  mat_err( att->rows!=3 || att->cols!=1, "Error (rot_e2q): Attitude is a 3 element column vector." );

  matrix* Q = mat_init(4,1);

  double X = 0.5 * mat_get(att,1,1);
  double Y = 0.5 * mat_get(att,2,1);
  double Z = 0.5 * mat_get(att,3,1);

  double Q1 = cos(X) * cos(Y) * cos(Z) + sin(X) * sin(Y) * sin(Z);
  double Q2 = sin(X) * cos(Y) * cos(Z) - cos(X) * sin(Y) * sin(Z);
  double Q3 = cos(X) * sin(Y) * cos(Z) + sin(X) * cos(Y) * sin(Z);
  double Q4 = cos(X) * cos(Y) * sin(Z) - sin(X) * sin(Y) * cos(Z);

  mat_set(Q,1,1,Q1);
  mat_set(Q,2,1,Q2);
  mat_set(Q,3,1,Q3);
  mat_set(Q,4,1,Q4);

  return mat_uvec(Q);
}






/*
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
*/


