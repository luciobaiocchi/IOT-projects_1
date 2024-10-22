#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

// Function Prototypes

/** 
 * @brief Initialize the LCD display
 */
void initializeLCD();

/** 
 * @brief Scroll text on the LCD display
 */
void scrollText();

/** 
 * @brief Display a number on the LCD display
 * @param randomNum The number to display
 */
void displayNumber(int randomNum);

/** 
 * @brief Display the win message on the LCD display
 * @param gameRound The current game round
 */
void displayWin(int gameRound);

/** 
 * @brief Display the game over message on the LCD display
 * @param gameRound The current game round
 */
void displayGameOver(int gameRound);

/** 
 * @brief Display the remaining time on the LCD display
 * @param time The remaining time in milliseconds
 */
void displayTimeLeft(int time);

/** 
 * @brief Display the game difficulty on the LCD display
 * @param gameDiff The game difficulty level
 */
void displayDifficulty(int gameDiff);

/** 
 * @brief Display the "Go" message on the LCD display
 */
void displayGo();

#endif