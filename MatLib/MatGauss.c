
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatGauss.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_gauss
//  Performs gauss elimination on a matrix.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void mat_gaus ( ) {

}




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function finds the last nonzero row.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int findlast ( matrix** X ) {

  int n = (*X)->rows;
  int m = (*X)->cols;
  double val;

  for ( int i=n; i>=1; i-- ) {
    for ( int j=1; j<=m; j++ ) {
      val = mat_get(*X,i,j);
      if ( val != 0 ) return i;
    }    
  }
  return 0;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function reorders rows so all zeros are on bottom.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int reorder ( matrix** X, int last ) {

  int c = (*X)->cols;
  int row = last;
  double val;

  for ( int i= last-1; i>=1; i-- ) {
    val = 0.0;
    for ( int j=1; j<=c; j++ )  {  val += fabs( mat_get(*X,i,j) );  }
    if ( val == 0 )  {  mat_swapr(*X,i,row);  row--;  }
  }
  return row;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function shifts rows to prevent divide by zero.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void shiftzero ( matrix** X, int row, int col ) {

  int count = 0;
  while ( !mat_get(*X,col,col) ) {
    for ( int i=1; i<row; i++ )  mat_swapr(*X,i,i+1);
    count++;
    mat_err(count>row, "Error (mat_gauss): Column filled with zeros." );
  }
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function eliminates column entries.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void elim ( matrix** X, int row, int col ) {

  int c = (*X)->cols;
  for ( int i= col+1; i<= row; i++ ) {

    double num = mat_get(*X,i,col);
    double den = mat_get(*X,col,col);
    double ratio = num / den;
    printf(" Row: %d   ", i);
    printf("num: %f   ",num);
    printf("den: %f   ",den);
    printf("ratio: %f ",ratio);
    printf("\n");

    for ( int j= col; j<=c; j++ ) {

      double val = mat_get(*X,i,j) - ratio * mat_get(*X,col,j);
      mat_set(*X,i,j,val);

      printf("  Col: %d   ",j);
      printf("val: %f",val);
      printf("\n");
    }
  }
  printf("X: ");  mat_print(*X);        

}





