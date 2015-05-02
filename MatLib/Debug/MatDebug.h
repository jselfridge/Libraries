
//============================================================
//  MatDebug.h
//  Justin M Selfridge
//============================================================
#ifndef _MATDEBUG_H_
#define _MATDEBUG_H_


// Standard includes
#include <stdio.h>


// Custom includes
#include "../MatLib.h"


// Function prototypes
//void DebugMatLib();
void InitMat();
void PrintMat();
void MatIO();
void MatManip();
//void MatComplex();
//void MatVec();
//void MatArith();
//void MatProp();
//void MatDecomp();
//void MatEchelon();
//void MatRoot();
//void MatSS();
//matrix* Plant1 ( matrix* x, matrix* u );
//matrix* Plant2 ( matrix* x, matrix* u );
void ClearMat();


// Global variables
matrix* M13;
matrix* M14;
matrix* M31a;
matrix* M31b;
matrix* M41;
matrix* M22;
matrix* M23;
matrix* M32;
matrix* M33a;
matrix* M33b;
matrix* M34;
matrix* M43;
matrix* M44;


#endif

