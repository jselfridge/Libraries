
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  OptDebug.h
//  Justin M Selfridge
//  Script to debug the OptLib Library
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#ifndef _OPTDEBUG_H
#define _OPTDEBUG_H


// Standard include
#include <stdio.h>


// Custom includes
#include "../OptLib/OptLib.h"


// Function prototypes
void    DebugOptLib();
void    OptGrad();
matrix* F( matrix* x );


#endif

