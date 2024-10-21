#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H



// Function Prototypes
void initializeLCD();
void scrollText();
void displayNumber(int randomNum);
void displayWin(int gameRound);
void displayGameOver(int gameRound);
void displayTimeLeft(int time);
void displayDifficulty(int gameDiff);


#endif 