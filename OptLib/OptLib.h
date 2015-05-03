
//============================================================
//  OptLib.h
//  Justin M Selfridge
//============================================================
#ifndef _OPTLIB_H_
#define _OPTLIB_H_


//  Standard includes
#include <stdbool.h>
#include <stdio.h>


// Custom includes
#include <MatLib.h>


// Function Prototypes
void  opt_grad ( matrix* F (matrix*), matrix** x, matrix* d, double tol, double gain, int max );


#endif



