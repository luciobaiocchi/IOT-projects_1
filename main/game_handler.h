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
void setupAll();
void initialSetup();
void initialState();
void gameSetup();
void inGameState();
void gameOverState();
void switchGameState(int state);
bool isTimeElapsed(int time);
void printTimeLeft();
void checkEndTime();
void setStartingTime();
long timeLeft();
int getRandomNumber();
bool isCorrect();

#endif /
