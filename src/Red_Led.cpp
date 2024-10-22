#include "Red_Led.h"
#include "Constants.h"
#include "Arduino.h"




int redLedIntensity = MIN_INTENSITY;
int fadeAmount = 5;

void fadingRedLed();

void gameOverLed();


void fadingRedLed(){
  if (redLedIntensity == 0) {
    fadeAmount = 5;
  } else if (redLedIntensity == 255) {
    fadeAmount = -5; 
  }
  analogWrite(LED_S, redLedIntensity); 
  redLedIntensity = redLedIntensity + fadeAmount;
  if (redLedIntensity == MIN_INTENSITY || redLedIntensity == MAX_INTENSITY && redLedIntensity != 0) {
    fadeAmount = -fadeAmount; 
  } 
  Serial.println(redLedIntensity);
  delay(18);
}


void gameOverLed(){
    analogWrite(LED_S, MAX_INTENSITY);
    delay(1000);
    analogWrite(LED_S, MIN_INTENSITY);
}