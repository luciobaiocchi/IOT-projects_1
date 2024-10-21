#include "ButtonManager.h"
#include "Constants.h"
#include "game_handler.h"
#include <EnableInterrupt.h>


void initializeButtons();

void addInterruptsForSleep();

void removeInterrupts();

void addInterruptsForStartGame();

void addInterruptsGame();

void buttonOnePressed();

void buttontTwoPressed();

void buttonThreePressed();

void buttonFourPressed();

void buttonAction(int index, int led);

void wakeUp();

void startMinigame();

void allButtonOff();

int booleanButtons[4]= {0, 0, 0, 0};



void initializeButtons(){
  for (int i = 0; i < NUM_BUTTONS; i++){
    pinMode(BUTTONS[i], INPUT);
  }
}

void addInterruptsForSleep(){
  for (int i = 0; i < NUM_BUTTONS; i++){
    enableInterrupt(BUTTONS[i], wakeUp, RISING);
  }
}

void removeInterrupts(){
  for (int i = 0; i < NUM_BUTTONS; i++){
    disableInterrupt(BUTTONS[i]);
  }
}

void addInterruptsForStartGame(){
  enableInterrupt(BUTTON_1, startGame, RISING);
}

void addInterruptsGame(){
  enableInterrupt(BUTTON_1, buttonOnePressed, RISING);
  enableInterrupt(BUTTON_2, buttontTwoPressed, RISING);
  enableInterrupt(BUTTON_3, buttonThreePressed, RISING);
  enableInterrupt(BUTTON_4, buttonFourPressed, RISING);
}

void allButtonOff(){
  booleanButtons[0] = 0;
  booleanButtons[1] = 0;
  booleanButtons[2] = 0;
  booleanButtons[3] = 0;
}

/* --- Interrupt Functions ---*/
void wakeUp(){
  switchGameState(INITIAL_SETUP);
}

void startGame(){
  switchGameState(GAME_SETUP);
  removeInterrupts(); 
  addInterruptsGame();            
}

void buttonOnePressed(){
  buttonAction(0, LED_1);
}
void buttontTwoPressed(){
  buttonAction(1, LED_2);
}
void buttonThreePressed(){
  buttonAction(2, LED_3);
}
void buttonFourPressed(){
  buttonAction(3, LED_4);
}

void buttonAction(int index, int led){
  if (booleanButtons[index] == 0){
    booleanButtons[index] = 1;
    digitalWrite(led, HIGH);
  }else{
    booleanButtons[index] = 0;
    digitalWrite(led, LOW);
  }
}

