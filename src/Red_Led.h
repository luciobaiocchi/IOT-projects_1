#ifndef __RED_LED__
#define __RED_LED__

#define MIN_INTENSITY 0
#define MAX_INTENSITY 255

/**
 * This function is used to manage the fading of the red led.
 */
void fadingRedLed();

/**
 * Animation of the red led when there is a game over.
 */
void gameOverLed();

#endif