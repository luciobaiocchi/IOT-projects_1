#include "Difficulty_manager.h"
#include "Constants.h"
#include "Arduino.h"
#include "LCD_manager.h"



int potVal = 0;
int gameDiff = 1;


void setDifficulty();

long mapDiff(long x, long in_min, long in_max, long out_min, long out_max);

void setDifficulty(){
  potVal = analogRead(POT_PIN);  
  if (potVal != gameDiff){
    gameDiff = mapDiff(potVal, 0, 1023, 1, 5);
    displayDifficulty(gameDiff);
    
  } 
}

long mapDiff(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max + 1 - in_min) + out_min;
}