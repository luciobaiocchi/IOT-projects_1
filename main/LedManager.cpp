#include "Constants.h"
#include "ButtonManager.h"
#include "Arduino.h"
#include "Red_Led.h"

void initializeLEDs(){
  pinMode(LED_S, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
}

extern int redLedIntensity;


void allLedOff(){
  allButtonOff();

  analogWrite(LED_S, LOW);
  redLedIntensity = 0;
  for (int i = 3; i < 8; i++){
    digitalWrite(i, LOW);
  }
}

