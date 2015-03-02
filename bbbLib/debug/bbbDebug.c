
//============================================================
//  bbbDebug.c
//  Justin M Selfridge
//============================================================
#include "bbbDebug.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  main
//  Runs the main bbbLib debugging program.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main ()  {
  printf("\n   --- bbbLib Debugging --- \n\n");
  bbbLED();
  bbbGPIO();
  printf("   --- bbbLib Complete --- \n\n");
  return 0;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  bbbLED
//  Debugs the bbbLED file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void bbbLED ( void )  {
  printf("BBB LED functions \n");

  // Set trigger status
  printf("led_rmtrig()\n");
  led_rmtrig(0);
  led_rmtrig(1);
  led_rmtrig(2);
  led_rmtrig(3);

  // Turn LEDs on for a second
  printf("led_on() \n");
  led_on(0);
  led_on(1);
  led_on(2);
  led_on(3);
  usleep(1000000);

  // Blink the LEDs
  printf("led_blink()\n");
  led_blink(0,250,250);
  led_blink(1,100,900);
  led_blink(2,500,500);
  led_blink(3,900,100);
  usleep(3000000);

  // Turn LEDs off for a second
  printf("led_off() \n");
  led_off(0);
  led_off(1);
  led_off(2);
  led_off(3);
  usleep(1000000);

  printf("\n");
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  bbbGPIO
//  Debugs the bbbGPIO file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void bbbGPIO ( void )  {
  printf("BBB GPIO functions \n");





  printf("\n");
  return;
}



