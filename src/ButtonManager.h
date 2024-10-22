#ifndef __BUTTON_MANAGER__
#define __BUTTON_MANAGER__

/**
 * Initialize the buttons.
 */
void initializeButtons();

/**
 * Add the interrupts for wake up Arduino from the sleep mode pressing a button.
 */
void addInterruptsForSleep();

/**
 * Remove the interrupts from the buttons.
 */
void removeInterrupts();

/**
 * Add an interrupt in B1 that starts the game.
 */
void addInterruptsForStartGame();

/**
 * Add the interrupts for the game.
 */
void addInterruptsGame();

/**
 * Function called by the interupt of B1.
 */
void buttonOnePressed();

/**
 * Function called by the interupt of B2.
 */
void buttontTwoPressed();

/**
 * Function called by the interupt of B3.
 */
void buttonThreePressed();

/**
 * Function called by the interupt of B4.
 */
void buttonFourPressed();

/**
 * Function called by the interupt of the buttons.
 * 
 * @param index the index of the button.
 * @param led the led to turn on.
 */
void buttonAction(int index, int led);

/**
 * Function called for waking up Arduino from the deep sleep.
 */
void wakeUp();

/**
 * Function called for starting the game.
 */
void startGame();

/**
 * Set 0 all the buttons.
 */
void allButtonOff();

#endif