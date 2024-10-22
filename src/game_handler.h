#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

// Game states
#define INITIAL_SETUP 0
#define INITIAL_STATE 1
#define GAME_SETUP 2
#define INGAME_STATE 3
#define GAMEOVER_STATE 4
#define FADE_SPEED 22
#define STANDARD_TIME 10000
#define FACTOR 500
#define GAME_CLOCK 12

// Function Prototypes

/** 
 * @brief Setup all the necessary components
 */
void setupAll();

/** 
 * @brief Perform initial setup for the game
 */
void initialSetup();

/** 
 * @brief Handle the initial state of the game
 */
void initialState();

/** 
 * @brief Setup the game environment
 */
void gameSetup();

/** 
 * @brief Handle the in-game state
 */
void inGameState();

/** 
 * @brief Handle the game over state
 */
void gameOverState();

/** 
 * @brief Switch the game state
 * @param state The new state to switch to
 */
void switchGameState(int state);

/** 
 * @brief Check if the specified time has elapsed
 * @param time The time to check against
 * @return true if the time has elapsed, false otherwise
 */
bool isTimeElapsed(int time);

/** 
 * @brief Print the remaining time
 */
void printTimeLeft();

/** 
 * @brief Check if the game end time has been reached
 */
void checkEndTime();

/** 
 * @brief Set the starting time for the game
 */
void setStartingTime();

/** 
 * @brief Get the remaining time
 * @return The remaining time in milliseconds
 */
long timeLeft();

/** 
 * @brief Generate a random number
 * @return A random number
 */
int getRandomNumber();

/** 
 * @brief Check if the player's action is correct
 * @return true if the action is correct, false otherwise
 */
bool isCorrect();

#endif
