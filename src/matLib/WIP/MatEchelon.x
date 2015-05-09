/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatEchelon.c
//  Justin M Selfridge
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include "MatLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  mat_echelon
//  Returns a matrix in reduced row echelon form.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
matrix* mat_echelon ( matrix* mat ) {

  matrix* X = mat_copy(mat);

  int r = mat->rows;
  int c = mat->cols;
  int k = 1;  // Operation counter
  int n = 1;  // Pivot row
  int m = 1;  // Pivot column

  // Iterate through operations
  do {
    printf("\nOperation: %d \n",k);
    printf("Pivot: %d,%d \n",n,m);

    // Skip zero columns
    if ( ech_colzero(X,m) ) { 
      printf("Skip zero colmn \n");
      m++;
      printf("Revised pivot: %d,%d \n",n,m);
    }

    // Work on nonzero columns
    else {
      printf("Working with column %d \n",m);

      // Reorder top to bottom
      ech_reorder(&X,n,m);
      printf("Reordered X: ");  mat_print(X);

      // Get pivot value
      double pivot = mat_get(X,n,m);
      printf("Pivot value: %f \n",pivot);

      // Test for zero value
      if ( pivot == 0 ) {  
	printf("Skipping zero pivot value \n");
	n++;
      }

      // Work with nonzero pivot
      else{
	printf("Working with nonzero pivot value \n");

        // Loop through all rows
        for ( int i=1; i<=r; i++ ) {

	  // Working on pivot row
	  if ( i==n ) {
	    printf("Working on pivot row \n");

	    // Loop through columns
	    for ( int j=1; j<=c; j++ ) {  
	      double val = mat_get(X,i,j)/pivot;
	      printf("[%d,%d] val: %f \n",i,j,val);
	      mat_set(X,i,j,val);
	    }
          }

	  // Working on non pivot row
	  else {
	    printf("Working on row %d \n",i);
	    double coef = mat_get(X,i,m);
	    printf("coef: %f \n",coef);

	    // Loop through columns
	    for ( int j=1; j<=c; j++ ) {
	      double val = mat_get(X,i,j) - coef * mat_get(X,n,j);
	      printf("[%d,%d] val: %f \n",i,j,val);
	      mat_set(X,i,j,val);
	    }
	  }
        }
      }


      printf("Finished column %d ",m);  mat_print(X);
      n++; 
      m++;
      k++;
    }


  } while ( k<=r && k<=c && n<=r && m<=c );  // Keep going until
*/

  /*

  // Loop through column operations 
  for ( int n=1; n<=1; n++ ) {
  //for ( int n=1; n<=N; n++ ) {
    printf("Operating on column %d \n",n);

    // Only operate on nonzero columns
    if ( ech_nonzero(X,n) ) { 
      printf("Nonzero column \n");

      // Rearrange coefficients largest to smallest
      ech_reorder(&X,n);
      printf("Reordered X: "); mat_print(X);

      // Manipulate column
      ech_manip(&X,n);



    }
    else printf("Skip zero column \n");

  }
  */

/*
  return X;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function tests if a column is filled with zeros.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool ech_colzero ( matrix* X, int m ) {
  for ( int i=1; i<= X->rows; i++ )  if ( mat_get(X,i,m) != 0 )  return false;
  return true;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function reorders rows from largest (abs) to smallest.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ech_reorder ( matrix** X, int n, int m ) {

  int r = (*X)->rows;

  // Find largest coefficient for current row
  for ( int i=n; i<r; i++ ) {
    printf("Finding largest coef for row %d \n", i);

    // Loop through remaining rows looking for largest
    double max = 0.0;
    int largest = 0;
    for ( int j=i; j<=r; j++ ) {
      double val = fabs( mat_get(*X,j,m) );
      if ( val > max ) {
	max = val;
	largest = j;
	printf("New max value of %f at row %d \n", val, largest);
      }
    }

    // Shuffle largest row to the top
    for ( int k= largest; k>i; k-- )  mat_swapr(*X,k,k-1);
    printf("Current X: ");  mat_print(*X);

  }
}
*/

/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function manipulates the operation column.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ech_manip ( matrix** X, int n ) {

  int r = (*X)->rows;
  int c = (*X)->cols;

  float pivot = mat_get(X,n,n);

  for ( int i=1; i<=r; i++ ) {
    for ( int j=1; j<=c; j++ ) {


    }
  }

}
*/



/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function finds the last nonzero row.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int ech_lastrow ( matrix* X ) {

  for ( int i= X->rows; i>=1; i-- ) {
    for ( int j=1; j<= X->cols; j++ ) {
      if ( mat_get(X,i,j) != 0 ) return i;
    }
  }
  return 0;
}
*/

/*
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Auxilliary function eliminates column entries.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ech_elim ( matrix** X, int row, int col ) {

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
*/




