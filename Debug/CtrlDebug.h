
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  CtrlDebug.h
//  Justin M Selfridge
//  Script to debug the CtrlLib Library
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _CTRLDEBUG_H
#define _CTRLDEBUG_H


// Standard include
//#include <stdio.h>


// Custom includes
#include "../MatLib/MatLib.h"


// Function prototypes
void    DebugCtrlLib();
void    CtrlLin();
void    ctrl_lin ( matrix* f ( matrix*, matrix* ), matrix* x, matrix* u, matrix** A, matrix** B, double d );
matrix* Plant1 ( matrix* x, matrix* u );
matrix* Plant2 ( matrix* x, matrix* u );


#endif

