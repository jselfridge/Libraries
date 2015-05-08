
//============================================================
//  bbbLib.c
//  Justin M Selfridge
//============================================================
#ifndef _BBBLIB_H_
#define _BBBLIB_H_


//  Standard includes
//#include <math.h>
//#include <stdio.h>


// Custom includes
#include <matLib.h>
#include <rotLib.h>



// bbbLED functions
int   led_rmtrig  ( unsigned int index );
int   led_on      ( unsigned int index );
int   led_off     ( unsigned int index );
int   led_blink   ( unsigned int index, unsigned int on, unsigned int off );


// bbbGPIO functions



// bbbUART function



// bbbI2C functions



// bbbMPU functions



// bbbPRU functions



// bbbServo functions



// bbbRadio functions




// EXAMPLE: ~~~~~~~~~~~~~~
// RotConv functions
matrix*  rot_d2r      ( matrix* deg );
matrix*  rot_r2d      ( matrix* rad );
void     rot_wrappi   ( matrix* rad );
void     rot_wrap2pi  ( matrix* rad );


#endif



