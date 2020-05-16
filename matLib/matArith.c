/*******************************************************************************
*
* Justin M Selfridge, PhD
* Gradient Consulting, LLC
* jselfridge@gmail.com
*
* matArith.h
* Source code for matrix arithmetic functions within the 'matLib' library.
*
*******************************************************************************/
#include "matLib.h"




/*******************************************************************************
* matrix* mat_add ( matrix* matA, matrix* matB )
* Adds two matrices with indentical dimensions.
*******************************************************************************/
matrix* mat_add ( matrix* matA, matrix* matB ) {

  mat_err( ( matA->rows != matB->rows ), "Error (mat_add): Matrices must have same number of rows."    );
  mat_err( ( matA->cols != matB->cols ), "Error (mat_add): Matrices must have same number of columns." );

  matrix* add = mat_init( matA->rows, matA->cols );
  for( ushort i=0; i < matA->rows * matA->cols; i++ )  *(add->data+i) = *(matA->data+i) + *(matB->data+i);
  return add;

  //for( ushort i=0; i < matA->rows * matA->cols; i++ )  *(matA->data+i) += *(matB->data+i);
  //retrun matA;

}




/*******************************************************************************
* matrix* mat_sub ( matrix* matA, matrix* matB )
* Subtracts two matrices with indentical dimensions.
*******************************************************************************/
matrix* mat_sub ( matrix* matA, matrix* matB ) {

  mat_err( ( matA->rows != matB->rows ), "Error (mat_sub): Matrices must have same number of rows."    );
  mat_err( ( matA->cols != matB->cols ), "Error (mat_sub): Matrices must have same number of columns." );

  matrix* sub = mat_init( matA->rows, matA->cols );
  for( ushort i=0; i < matA->rows * matA->cols; i++ )  *(sub->data+i) = *(matA->data+i) - *(matB->data+i);
  return sub;

  //for( ushort i=0; i < matA->rows * matA->cols; i++ )  *(matA->data+i) -= *(matB->data+i);
  //retrun matA;

}




/*******************************************************************************
* matrix* mat_emul ( matrix* matA, matrix* matB )
* Element-wise multiplication of two matrices with identical dimensions.
*******************************************************************************/
matrix* mat_emul ( matrix* matA, matrix* matB ) {

  mat_err( ( matA->rows != matB->rows ), "Error (mat_emul): Matrices must have same number of rows."    );
  mat_err( ( matA->cols != matB->cols ), "Error (mat_emul): Matrices must have same number of columns." );

  matrix* emul = mat_init( matA->rows, matA->cols );
  for( ushort i=0; i < matA->rows * matA->cols; i++ )  *(emul->data+i) = *(matA->data+i) * *(matB->data+i);
  return emul;

  //for( ushort i=0; i < matA->rows * matA->cols; i++ )  *(matA->data+i) *= *(matB->data+i);
  //retrun matA;

}




/*******************************************************************************
* matrix* mat_ediv ( matrix* matA, matrix* matB )
* Element-wise division of two matrices with identical dimensions.
*******************************************************************************/
matrix* mat_ediv ( matrix* matA, matrix* matB ) {

  mat_err( ( matA->rows != matB->rows ), "Error (mat_ediv): Matrices must have same number of rows."    );
  mat_err( ( matA->cols != matB->cols ), "Error (mat_ediv): Matrices must have same number of columns." );

  matrix* ediv = mat_init( matA->rows, matA->cols );
  for( ushort i=0; i < matA->rows * matA->cols; i++ )  *(ediv->data+i) = *(matA->data+i) / *(matB->data+i);
  return ediv;

  //for( ushort i=0; i < matA->rows * matA->cols; i++ )  *(matA->data+i) /= *(matB->data+i);
  //retrun matA;

}




/*******************************************************************************
* matrix* mat_mul ( matrix* matA, matrix* matB )
* Multiplication of two matrices with proper dimensions.
*******************************************************************************/
matrix* mat_mul ( matrix* matA, matrix* matB ) {

  mat_err( ( matA->cols != matB->rows ), "Error (mat_mul): Matrix dimensions do not agree." );

  matrix* mul = mat_init( matA->rows, matB->cols );

  for( ushort i=0; i<matA->rows; i++ ) {
    for( ushort j=0; j<matB->cols; j++ ) {
      float val = 0.0;
      for( ushort k=0; k<matA->cols; k++ ) {
        val += *( matA->data + i*matA->cols + k ) * *( matB->data + k*matB->cols + j );
      }
      *( mul->data + i*mul->cols + j ) = val;
    }
  }

  return mul;
}




/*******************************************************************************
* matrix* mat_inv ( matrix* mat )
* Calculates the inverse of a square matrix
*******************************************************************************/
/*
matrix* mat_inv ( matrix* mat ) {

  mat_err( mat->rows != mat->cols, "Error (mat_inv): Matrix must be square." );

  matrix* eye = mat_eye( mat->rows );
  matrix* inv = mat_divL( mat, eye );

  mat_clear(eye);

  return inv;
}*/




/*******************************************************************************
* matrix* mat_divL ( matrix* matA, matrix* matB )
* Solves for X in AX=B; which is equivalent to X=A\B.
*******************************************************************************/
/*
matrix* mat_divL ( matrix* matA, matrix* matB ) {

  // Error checking
  mat_err( matA->rows != matA->cols, "Error (mat_divL): A matrix must be square. "        );
  mat_err( matA->rows != matB->rows, "Error (mat_divL): A and B must be the same height." );

  // Local variables
  ushort r, c, i, j, k;
  float val;

  // Dimensions
  r = matB->rows;
  c = matB->cols;

  // Initialize matrices
  matrix* Y = mat_init(r,c);
  matrix* X = mat_init(r,c);

  // QR factorization
  matrix* Q = NULL;
  matrix* R = NULL;
  mat_QR( matA, &Q, &R );

  // Solve intermediate matrix
  Y = mat_mul( mat_trans(Q), matB );

  // Trangluar substitution
  for( k=1; k<=c; k++ ) {
    for( i=r; i>=1; i-- ) {
      val = mat_get( Y, i, k );
      for( j=r; j>i; j-- )  val -= mat_get( R, i, j ) * mat_get( X, j, k );
      val /= mat_get( R, i, i );
      mat_set( X, i, k, val );
    }
  }

  // Clear matrices
  mat_clear(Q);
  mat_clear(R);
  mat_clear(Y);

  return X;
}*/




/*******************************************************************************
* matrix* mat_divR ( matrix* matA, matrix* matB )
* Solves for X in XA=B; which is equivalent to X=B/A.
*******************************************************************************/
/*
matrix* mat_divR ( matrix* matA, matrix* matB ) {

  mat_err( matA->rows != matA->cols, "Error (mat_divR): A matrix must be square.       " );
  mat_err( matA->cols != matB->cols, "Error (mat_divR): A and B must be the same width." );

  matrix* X = mat_init( matB->rows, matB->cols );

  X = mat_mul( matB, mat_inv(matA) );

  return X;
}*/




/*******************************************************************************
* matrix* mat_pow ( matrix* mat, ushort power )
* Raises a square matrix to a specified power.
*******************************************************************************/
// matrix* mat_pow ( matrix* mat, ushort power ) {

//   mat_err( mat->rows != mat->cols, "Error (mat_pow): Matrix must be square."        );
//   mat_err( power < 0,              "Error (mat_pow): Exponent must be nonnegative." );

//   ushort i;
//   ushort n = mat->rows;
//   matrix* pow;

//   if      ( power == 0 )  pow = mat_eye(n);
//   else if ( power == 1 )  pow = mat_copy(mat);
//   else {
//     pow = mat_init(n,n);
//     for( i=1; i <= power-1; i++ ) {
//       if (i==1)  pow = mat_mul( mat, mat );
//       else       pow = mat_mul( pow, mat );
//     }
//   }

//   return pow;
// }




/*******************************************************************************
* matrix* mat_abs ( matrix* mat )
* Applies absolute value to all elements within a matrix.
*******************************************************************************/
// matrix* mat_abs ( matrix* mat ) {

//   ushort i, j, r, c;
//   float val;
//   matrix* abs;

//   r = mat->rows;
//   c = mat->cols;
//   abs = mat_init(r,c);

//   for( i=1; i<=r; i++ ) {
//     for( j=1; j<=c; j++ ) {
//       val = fabs( mat_get( mat, i, j ) );
//       mat_set( abs, i, j, val );
//     }
//   }

//   return abs;
// }




/*******************************************************************************
* matrix* mat_trans ( matrix* mat )
* Returns the transpose of a rectangular matrix.
*******************************************************************************/
// matrix* mat_trans ( matrix* mat ) {

//   ushort i, j, r, c;
//   float val;
//   matrix* trans;

//   r = mat->rows;
//   c = mat->cols;
//   trans = mat_init(c,r);

//   for( i=1; i<=r; i++ ) {
//     for( j=1; j<=c; j++ ) {
//       val = mat_get( mat, i, j );
//       mat_set( trans, j, i, val );
//     }
//   }

//   return trans;
// }



