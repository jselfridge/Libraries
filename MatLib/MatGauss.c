
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
    for ( int j=1; j<=c; j++ )  {  val += mat_get(*X,i,j);  }
    if ( val == 0 )  {  mat_swapr(*X,i,row);  row--;  }
  }
  return row;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function eliminates column entries.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void elim ( matrix** X, int row, int col ) {

  int c = (*X)->cols;
  //double val;
  //double num = mat_get(*X,col,col);
  //printf("num: %f \n", num );

  for ( int i= col+1; i<= row; i++ ) {
    printf("row: %d \n", i);

    double scale = mat_get(*X,i,col);
    printf("scale: %f \n", scale);

    for ( int j= col; j<=c; j++ ) {
      printf("col: %d \n", j);
      /*
      double current = mat_get(*X,i,j);
      printf("current: %f \n", current);

      double base = mat_get(*X,col,j);
      printf("base: %f \n", base);
      
      double val = current - scale * base;
      printf("val: %f \n", val);      
      */
      double val = mat_get(*X,i,j) - scale * mat_get(*X,col,j);
      printf("val: %f \n", val);      
      mat_set(*X,i,j,val);


    }

    printf("X: ");  mat_print(*X);        
  }
}

