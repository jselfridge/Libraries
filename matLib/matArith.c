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
* matrix* mat_epow ( matrix* mat, float power )
* Element-wise operation which raises each entry to a specified power.
*******************************************************************************/
matrix* mat_epow ( matrix* mat, float power ) {

  matrix* epow = mat_init( mat->rows, mat->cols );
  for( ushort i=0; i < mat->rows * mat->cols; i++ )  *(epow->data+i) = (float)pow( *(mat->data+i), power );
  return pow;

  //for( ushort i=0; i < mat->rows * mat->cols; i++ )  *(mat->data+i) = (float)pow( *(mat->data+i), power );
  //return mat;
}




/*******************************************************************************
* matrix* mat_pow ( matrix* mat, uint power )
* Raises a square matrix to a specified integer power.
*******************************************************************************/
matrix* mat_pow ( matrix* mat, uint power ) {

  mat_err( ( mat->rows != mat->cols ), "Error (mat_pow): Matrix must be square." );

  switch( power ) {
    case 0 : return mat_eye( mat->rows );
    case 1 : return mat;
    default : {
      matrix* pow = mat_eye( mat->rows );
      for( ushort i=0; i<power; i++ )  pow = mat_mul( pow, mat );
      return pow;
    }
  }

}




/*******************************************************************************
* matrix* mat_abs ( matrix* mat )
* Applies absolute value to all elements within a matrix.
*******************************************************************************/
matrix* mat_abs ( matrix* mat ) {

  matrix* abs = mat_init( mat->rows, mat->cols );
  for( ushort i=0; i < mat->rows * mat->cols; i++ )  *(abs->data+i) = (float)fabs( *(mat->data+i) );
  return abs;

  //for( ushort i=0; i < mat->rows * mat->cols; i++ )  *(mat->data+i) = (float)fabs( *(mat->data+i) );
  //return mat;
}




/*******************************************************************************
* matrix* mat_trans ( matrix* mat )
* Returns the transpose of a rectangular matrix.
*******************************************************************************/
matrix* mat_trans ( matrix* mat ) {

  matrix* trans = mat_init( mat->cols, mat->rows );

  for( ushort i=0; i < mat->rows * mat->cols; i++ ) {
    *( trans->data + (i%mat->cols) * trans->cols + i/mat->cols ) = *( mat->data + (i/mat->cols) * mat->cols + i%mat->cols );
  }

  return trans;
}




/*******************************************************************************
* matrix* mat_reshape ( matrix* mat, uint rows, uint cols )
* Reshapes an existing matrix to fit within the specified dimensions.
*******************************************************************************/
matrix* mat_reshape ( matrix* mat, uint rows, uint cols ) {

  mat_err( ( mat->rows * mat->cols != rows * cols ), "Error (mat_reshape): Number of elements do not match." );

  matrix* reshape = mat_init( rows, cols );
  for( ushort i=0; i < mat->rows * mat->cols; i++ ) {
    *( reshape->data + (i/cols)*cols + i%cols ) = *( mat->data + (i/mat->cols)*mat->cols + i%mat->cols );
  }

  return reshape;
}



