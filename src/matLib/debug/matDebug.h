

#ifndef MATDEBUG_H
#define MATDEBUG_H


// Standard includes
#include <stdio.h>


// Custom includes
#include <matLib.h>


// Function prototypes
void InitMat();
void PrintMat();
void MatManip();
void MatComplex();
void MatVec();
void MatArith();
void MatRoot();
//void MatDecomp();
void ClearMat();


// Global variables
matrix *M13;
matrix *M14;
matrix *M31a;
matrix *M31b;
matrix *M41;
matrix *M22;
matrix *M23;
matrix *M32;
matrix *M33a;
matrix *M33b;
matrix *M34;
matrix *M43;
matrix *M44;


#endif



