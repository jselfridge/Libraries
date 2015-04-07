
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  CtrlDebug.h
//  Justin M Selfridge
//  Script to debug the CtrlLib Library
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _CTRLDEBUG_H
#define _CTRLDEBUG_H


// Custom includes
#include "../MatLib/MatLib.h"
#include "../CtrlLib/CtrlLib.h"


// Function prototypes
void    DebugCtrlLib();
void    CtrlFunc();
matrix* Plant1 ( matrix* x, matrix* u );
matrix* Plant2 ( matrix* x, matrix* u );


#endif

