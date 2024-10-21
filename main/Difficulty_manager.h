#ifndef __DIFFICULTY_MANAGER__
#define __DIFFICULTY_MANAGER__

/**
 * Read the potentiometer value and set the difficulty of the game accordingly.
 */
void setDifficulty();

/**
 * Edited map function, in order to obtain a better range for the last number.
 */
long mapDiff(long x, long in_min, long in_max, long out_min, long out_max);

#endif