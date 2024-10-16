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
  lcd.setCursor(0, 0);

  Serial.begin(9600); 
}

void setStartingTime();
void sleeping();
void fadingRedLed();
void checkIfGoSleep();
bool isTimeElapsed();
long mapDiff();
void allLedOff();
void logButton();
void setDifficulty();
void addInterruptsForSleep();
void removeInterruptsForSleep();
void addInterruptsForStartGame();
void removeInterruptsForStartGame();
void startMinigame();
boolean isCorrect();
int getRandomNumber();
void buttonPressed();
void doAnimation();


int gameState = 0;
int potVal = 0;
long start_initial_state = 0;
int gameDiff = 1;
int redLedIntensity = 0;
int fadeAmount = 5;
int line = 0;
//-----------------//
int gameRound = 0;
int totalTime = 10000;
int factor = 500;
int buttons[4]= {1, 0, 1, 1};


void loop() {
  switch(gameState){
    case 0:
      setStartingTime();
      gameState = 1;
      break;
  	case 1:
      fadingRedLed();
      checkIfGoSleep();
      addInterruptsForStartGame();
      setDifficulty();
  	  break;
    case 2:
      Serial.println(totalTime);
      break;
    case 3:
      Serial.println(totalTime);
      break;
  }

}

void setStartingTime(){
  start_initial_state = millis();
}

  
void fadingRedLed(){
  analogWrite(LED_S, redLedIntensity); 
  redLedIntensity = redLedIntensity + fadeAmount;
  if (redLedIntensity == 0 || redLedIntensity == 255) {
    fadeAmount = -fadeAmount ; 
  } 
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
  gameState = 2;
  totalTime = totalTime - (gameDiff * 1000); 
  allLedOff();
  removeInterruptsForStartGame();
}


int getRandomNumber(){
  return random(0, 15);
}

boolean isCorrect(int number, int buttons[]){
  float bin = 0;
  for (int i = 0; i < 4; i++){
    if (buttons[i] == 1){
    	bin = (bin + pow(2,i));
    }
  }
  return round(bin) == number;
}

void buttonPressed(int i){
  if (buttons[i] == 0){
    buttons[i] = 1;
  }else{
    buttons[i] = 0;
  }
}

















