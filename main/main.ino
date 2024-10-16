#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include <LiquidCrystal_I2C.h> 



// Leds declaration
#define LED_S 3
#define LED_1 4
#define LED_2 5
#define LED_3 6
#define LED_4 7

// Buttons declaration
#define BUTTON_1 11
#define BUTTON_2 10
#define BUTTON_3 9
#define BUTTON_4 8

// Potentiometer --> map()
#define POT_PIN A0


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); 


void setup() {
  // Leds
  pinMode(LED_S, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
    
  // Buttons
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pinMode(BUTTON_4, INPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(2, 1);

  Serial.begin(9600); 
}

void setInitialStateStartingTime();
void sleeping();
void fadingRedLed();
void checkIfGoSleep();
bool isTimeElapsed();
long mapDiff(long x, long in_min, long in_max, long out_min, long out_max);
void allLedOff();
void logButton(int buttonNumber);
void setDifficulty();
void addInterruptsForSleep();
void removeInterruptsForSleep();
void addInterruptsForStartGame();
void removeInterruptsForStartGame();
void startMinigame();
void switchState();


int gameState = 0;
int potVal = 0;
long start_initial_state = 0;
int gameDiff = 1;
int redLedIntensity = 0;
int fadeAmount = 5;
int totalTime = 10000;



void loop() {
  Serial.println(gameState);
  switch(gameState){
    case 0:
      setInitialStateStartingTime();
      switchState(1);
      break;
  	case 1:
      fadingRedLed();
      setDifficulty();
      checkIfGoSleep();
      addInterruptsForStartGame();
  	  break;
    case 2:

      break;
    case 3:
      Serial.println("game");
      break;
  }

}

void setInitialStateStartingTime(){
  start_initial_state = millis();
}

  
void fadingRedLed(){
  analogWrite(LED_S, redLedIntensity); 
  redLedIntensity = redLedIntensity + fadeAmount;
  if (redLedIntensity == 0 || redLedIntensity == 255) {
    fadeAmount = -fadeAmount ; 
  } 
  Serial.println(redLedIntensity);
  delay(22);
}


void checkIfGoSleep(){
  if (isTimeElapsed()) {
    allLedOff();
    removeInterruptsForStartGame();
    addInterruptsForSleep(); 
    set_sleep_mode(SLEEP_MODE_PWR_DOWN); 
    sleep_enable(); 
    sleep_mode();    

    Serial.print("WakeUP");
      
    sleep_disable();
    removeInterruptsForSleep();
  }
}

void addInterruptsForSleep(){
  for (int i = 8; i < 12; i++){
    enableInterrupt(i, wakeUp, RISING);
  }
}

void removeInterruptsForSleep(){
  for (int i = 8; i < 12; i++){
    disableInterrupt(i);
  }
}

void wakeUp(){
  gameState = 0;
}


void setDifficulty(){
  potVal = analogRead(POT_PIN);   
  gameDiff = mapDiff(potVal, 0, 1023, 1, 5);
  lcd.setCursor(1, 1);
  lcd.print(String("Diff: ") + String(gameDiff));
}

//eidted map function, in order to obtain a better range for the last number
long mapDiff(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max + 1 - in_min) + out_min;
}


bool isTimeElapsed(){
  long timePassed = millis() - start_initial_state;
  return timePassed > 5000;
}

void allLedOff(){
  analogWrite(LED_S, LOW);
  redLedIntensity = 0;
  for (int i = 3; i < 8; i++){
    digitalWrite(i, LOW);
  }
}

void addInterruptsForStartGame(){
  enableInterrupt(11, startMinigame, RISING);
}

void removeInterruptsForStartGame(){
  disableInterrupt(BUTTON_1);
}


void startMinigame(){
  switchState(2);
  totalTime = totalTime - (gameDiff * 1000); 
  allLedOff();
  removeInterruptsForStartGame();
}

void switchState(int state){
  lcd.clear();
  gameState = state;
  lcd.print(String("State: ") + String(state));
}




