
//============================================================
//  bbbLED.c
//  Justin M Selfridge
//============================================================
#include "bbbLib.h"


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  led_rmtrig
//  Sets the LED trigger status to 'none'.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int led_rmtrig ( unsigned int index )  {

  mat_err( index>3, "Error (led_rmtrig): LED index is between 0-3." );

  int fd, len;
  char path[MAX_BUF];

  len = snprintf ( path, sizeof(path), LED_PATH "%d/trigger", index );
  mat_err( len<=0, "Error (led_rmtrig): Failed to generate 'trigger' file path. ");
  //if (len<=0) {
  //printf("Error with trigger \n");
  //return -1;
  //}
  fd = open( path , O_WRONLY );  
  mat_err( fd<0, "Error (led_rmtrig): Failed to open 'trigger' file. ");
  //if (fd<0) return -1; 

  write( fd, "none", 5  );
  close(fd);

  return 0;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  led_on
//  Turns on the specified user LED.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int led_on ( unsigned int index )  {

  mat_err( index>3, "Error (led_on): LED index is between 0-3." );

  int fd, len;
  char path[MAX_BUF];

  led_rmtrig(index);

  len = snprintf ( path, sizeof(path), LED_PATH "%d/brightness", index );
  mat_err( len<=0, "Error (led_on): Failed to generate 'brightness' file path. ");
  //if (len<=0) {
  //printf("Error with brightness \n");
  //return -1;
  //}

  fd = open ( path, O_WRONLY );
  mat_err( fd<0, "Error (led_on): Failed to open 'brightness' file. ");
  //if (fd<0) return -1;

  write( fd, "1", 2 );
  close(fd);

  return 0;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  led_off
//  Turns off the specified user LED.  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int led_off ( unsigned int index )  {

  mat_err( index>3, "Error (led_off): LED index is between 0-3." );

  int fd, len;
  char path[MAX_BUF];

  led_rmtrig(index);

  len = snprintf ( path, sizeof(path), LED_PATH "%d/brightness", index );
  mat_err( len<=0, "Error (led_off): Failed to generate 'brightness' file path. ");
  //if (len<=0) {
  //printf("Error with brightness \n");
  //return -1;
  //}
  fd = open ( path, O_WRONLY );
  mat_err( fd<0, "Error (led_off): Failed to open 'brightness' file. ");
  // if (fd<0) return -1;

  write( fd, "0", 2 );
  close(fd);

  return 0;
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  led_blink
//  Blinks the specified user LED.  
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int led_blink ( unsigned int index, unsigned int on, unsigned int off )  {

  mat_err( index>3, "Error (led_blink): LED index is between 0-3."         );
  mat_err( on<=0,   "Error (led_blink): Duration 'on' must be positive."   );
  mat_err( off<=0,  "Error (led_blink): Duration 'off' must be positive."  );

  int fd, len;
  char path[MAX_BUF];
  char val[MAX_BUF];

  len = snprintf ( path, sizeof(path), LED_PATH "%d/trigger", index );
  mat_err( len<=0, "Error (led_blink): Failed to generate 'trigger' file path. ");
  //if (len<=0) {
  //printf("Error with trigger \n");
  //return -1;
  //}
  fd = open ( path, O_WRONLY );
  mat_err( fd<0, "Error (led_blink): Failed to open 'trigger' file. ");
  //if (fd<0) return -1;
  path[0] = '\0';

  write( fd, "timer", 6 );
  close(fd);

  len = snprintf ( path, sizeof(path), LED_PATH "%d/delay_on", index );
  mat_err( len<=0, "Error (led_blink): Failed to generate 'delay_on' file path. ");
  //if (len<=0) {
  //printf("Error with delay_on \n");
  //return -1;
  //}
  fd = open ( path, O_WRONLY );
  mat_err( fd<0, "Error (led_blink): Failed to open 'delay_on' file. ");
  //if (fd<0) return -1;
  path[0] = '\0';

  len = snprintf ( val, sizeof(val), "%d", on );
  mat_err( len<=0, "Error (led_blink): Failed to generate 'delay_on' description. ");
  //if (len<=0) {
  //printf("Error with delay_on \n");
  //return -1;
  //}
  write( fd, val, len+1 );
  val[0] = '\0';
  close(fd);

  len = snprintf ( path, sizeof(path), LED_PATH "%d/delay_off", index );
  mat_err( len<=0, "Error (led_blink): Failed to generate 'delay_off' file path. ");
  //if (len<=0) {
  //printf("Error with delay_off \n");
  //return -1;
  //}
  fd = open ( path, O_WRONLY );
  mat_err( fd<0, "Error (led_blink): Failed to open 'delay_off' file. ");
  //if (fd<0) return -1;
  path[0] = '\0';

  len = snprintf( val, sizeof(val), "%d", off );
  mat_err( len<=0, "Error (led_blink): Failed to generate 'delay_off' description. ");
  //if (len<=0) {
  //printf("Error with delay_off \n");
  //return -1;
  //}
  write( fd, val, len+1 );
  val[0] = '\0';
  close(fd);

  return 0;
}



