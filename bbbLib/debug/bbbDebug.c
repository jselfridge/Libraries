
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
  //bbbLED();
  bbbGPIO();
  printf("   --- bbbLib Complete --- \n\n");
  return 0;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  bbbLED
//  Debugs the bbbLED file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void bbbLED ( void )  {

  // Start the LED demo
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

  // Exit the function
  printf("\n");
  return;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  bbbGPIO
//  Debugs the bbbGPIO file functions.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void bbbGPIO ( void )  {

  // Start the GPIO demo
  printf("BBB GPIO functions \n");

  // Local variables
  int i;
  int gpio_led    = 60;    // P9_12  GPIO1[28] = (1x32)+28 = 60
  int gpio_button = 15;    // P9_24  GPIO0[15] = (0x32)+15 = 15
  unsigned int val;

  // Export the pins
  gpio_export( gpio_led );
  gpio_export( gpio_button );
    
  // Set pin direction
  gpio_set_dir( gpio_led,    OUTPUT_PIN );
  gpio_set_dir( gpio_button, INPUT_PIN  );
    
  // Flash the LED
  for( i=0; i<5; i++ ) {
    printf("LED on... \n");
    gpio_set_val( gpio_led, HIGH );
    usleep(200000);
    printf("LED off... \n");
    gpio_set_val( gpio_led, LOW );
    usleep(200000);
  }
    
  // Demonstrate the push button
  printf("Press the button! \n");
  val = LOW;
  do {
    gpio_get_val( gpio_button, &val );
    printf(".");
    usleep(100);
  } while ( val == LOW );
  printf("\nButton was pressed!\n");
    
  // Unexport the pins
  gpio_unexport( gpio_led );
  gpio_unexport( gpio_button );

  // Exit the function
  printf("\n");
  return;
}



