#include "game_handler.h"
#include "Constants.h"
#include "LCD_manager.h"
#include "ButtonManager.h"
#include "LedManager.h"
#include "Arduino.h"
#include "Difficulty_manager.h"
#include "Red_Led.h"


#include <LiquidCrystal_I2C.h>
#include <avr/sleep.h>

extern LiquidCrystal_I2C lcd;
extern int booleanButtons[4];
extern int gameDiff;



int gameState = INITIAL_SETUP;
int totalTime = 10000;
long start_timer_time = 0;
int gameRound = 0;
int randomNum = 0;
int clock = 0;



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

void checkIfGoSleep();


/* --- State Functions --- */
void setupAll(){
    switchGameState(INITIAL_SETUP);
    initializeLCD();
    initializeButtons();
    initializeLEDs();

}


void initialSetup(){
    lcd.clear();
    setStartingTime();
    switchGameState(INITIAL_STATE);
    addInterruptsForStartGame();
}

//adding clock to make fading led and text scroll asyncronus
void initialState(){
    if (clock == GAME_CLOCK){
      scrollText();
      clock = 0;
    }
    setDifficulty();
    fadingRedLed();
    checkIfGoSleep();
    clock++;
}

void gameSetup(){
    if (gameRound == 0){
      displayGo();
      delay(2000);
    }
    Serial.println("game");
    allLedOff();
    randomNum = 0;
    randomNum = getRandomNumber();
    displayNumber(randomNum);
    totalTime = STANDARD_TIME - (gameDiff * 1000) - (gameRound * FACTOR); 
    setStartingTime();
    switchGameState(INGAME_STATE);  
}

void inGameState(){
    checkEndTime();
    //Serial.println(String(buttons[0]) + String(buttons[1]) + String(buttons[2]) + String(buttons[3]));
    //updating total time 
    if (isCorrect()){
      gameState = 2;
      gameRound++;
      displayWin(gameRound);
      //insert delay to avoid keep pressing button when next round is displayed
      delay(200);
      //Serial.print("win");
    }
}



void gameOverState(){
    removeInterrupts();
    displayGameOver(gameRound);
    totalTime = STANDARD_TIME;
    gameRound = 0;
    gameOverLed();
    delay(10000);
    switchGameState(INITIAL_SETUP);
}



/* --- Utilities Functions --- */
void switchGameState(const int STATE){
    gameState = STATE;
}

bool isTimeElapsed(int time){
  long timePassed = millis() - start_timer_time;
  return timePassed > time;
}

void setStartingTime(){
  start_timer_time = millis();
}

//return the time left for the timer in milliseconds 
long timeLeft(){
  long timeLeft = millis() - start_timer_time;
  return timeLeft;
}

int getRandomNumber(){
  return random(16);
}

bool isCorrect(){
  
  float bin = 0;
  for (int i = 0; i < 4; i++){
    if (booleanButtons[i] == 1){
    	bin = (bin + pow(2, 3 - i));
    }
  }
  Serial.println(round(bin));
  return round(bin) == randomNum;
}

void checkEndTime(){
  printTimeLeft();
  if (isTimeElapsed(totalTime)) {
    allLedOff();
    Serial.print("game Over");
    switchGameState(GAMEOVER_STATE);
  }
}

//print remaining time in this format : ex 5.75 seconds (the last number is either 0 or 5)
void printTimeLeft(){
  int displayTime = (totalTime - timeLeft())/ 100;
  if (displayTime % 10 == 0){
    displayTimeLeft(displayTime / 10);
  }
}

void checkIfGoSleep(){
  if (isTimeElapsed(STANDARD_TIME)) {
    allLedOff();
    removeInterrupts();
    addInterruptsForSleep(); 
    lcd.clear();
    lcd.noBacklight();
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
    
    sleep_enable(); 
    sleep_mode();    
    lcd.backlight();  
    Serial.println("WAKE UP");
    setStartingTime();
    sleep_disable();
    removeInterrupts();
  }
}
