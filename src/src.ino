/**
 * @file src.ino
 * @brief Main Arduino sketch for the IOT project.
 *
 * This file contains the setup and loop functions for the Arduino-based IOT project.
 * It includes necessary headers and handles the main game state logic.
 */


#include "Constants.h"
#include "game_handler.h"

void setup() {
  setupAll();
  Serial.begin(9600); 
  Serial.println("start " +  String(analogRead(A1)));
  randomSeed(analogRead(A1));

}


extern int gameState;

void loop() {
  switch(gameState){
    case 0:
      initialSetup();
      break;
  	case 1:
      initialState();
  	  break;
    case 2:
      gameSetup();
      break;
    case 3:
      inGameState();
      break;
    case 4:
      gameOverState();
      break;
  }

}
