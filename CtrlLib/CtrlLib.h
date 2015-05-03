
//============================================================
//  CtrlLib.h
//  Justin M Selfridge
//============================================================
#ifndef _CTRLLIB_H_
#define _CTRLLIB_H_


// Custom includes
#include <MatLib.h>


// Function Prototypes
void     ctrl_lin  ( matrix* f ( matrix*, matrix* ), matrix* x, matrix* u, matrix* A, matrix* B, double d );
matrix*  ctrl_ctrb ( matrix* A, matrix* B );
matrix*  ctrl_obsv ( matrix* A, matrix* C );


#endif



