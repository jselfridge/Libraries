
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  MatDebug.h
//  Justin M Selfridge
//  Script to debug the MatLib Library
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _MATDEBUG_H
#define _MATDEBUG_H


// Standard include
#include <stdio.h>


// Custom includes
#include "../MatLib/MatLib.h"


// Function prototypes
void DebugMatLib();
void InitMat();
void PrintMat();
void MatIO();
void MatManip();
void MatComplex();
void MatVec();
void MatArith();
void MatProp();
void MatDecomp();
void MatEchelon();
void MatRoot();
void MatSS();
matrix* Plant1 ( matrix* x, matrix* u );
matrix* Plant2 ( matrix* x, matrix* u );
void ClearMat();


// Global variables
matrix* V3a;
matrix* V3b;
matrix* V4;
matrix* M22;
matrix* M23;
matrix* M32;
matrix* M33a;
matrix* M33b;
matrix* M34;
matrix* M43;
matrix* M44;


#endif


