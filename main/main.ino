#include <avr/sleep.h>
#include <EnableInterrupt.h>
#include <LiquidCrystal_I2C.h> 



// Leds declaration
#define LED_S 3
#define LED_1 4
#define LED_2 5
#define LED_3 6
#define LED_4 7
#define STANDARD_TIME 10000
#define FACTOR 500

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
  Serial.println("start " +  String(analogRead(A1)));
  randomSeed(analogRead(A1));

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
void buttontTwoPressed();
void buttonThreePressed();
void buttonFourPressed();
void doAnimation();
void checkEndTime();
void addInterruptsGame();
void checkEndRedLed();


int gameState = 0;
int potVal = 0;
long start_timer_time = 0;
int gameDiff = 1;
int redLedIntensity = 0;
int fadeAmount = 5;
int line = 0;
//-----------------//
int gameRound = 0;
int totalTime = 10000;
int buttons[4]= {0, 0, 0, 0};
int randomNum = 0;

/*Game State:
0 -> first setup
1 -> fading and sleep
2 -> Setup game lcd display number 
3 -> game loop
4 -> game over
*/
void loop() {
  switch(gameState){
    case 0:
      lcd.clear();
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
      Serial.println("game");
      allLedOff();
      randomNum = 0;
      randomNum = getRandomNumber();
      //in case the previus number is 2 digits and the actual number in only one this part of code clear the lcd 
      lcd.setCursor(10, 0);
      lcd.print("  ");
    
      lcd.home();
      lcd.print("number -> "+ String(randomNum));
      //updating total time 
      totalTime = STANDARD_TIME - (gameDiff * 1000) - (gameRound * FACTOR); 
      Serial.println(totalTime);
      setStartingTime();
      removeInterruptsForStartGame();
      addInterruptsGame();
      gameState = 3;
      break;
    case 3:
      checkEndTime();
      //Serial.println(String(buttons[0]) + String(buttons[1]) + String(buttons[2]) + String(buttons[3]));
      //updating total time 
      if (isCorrect()){
        gameState = 2;
        gameRound++;
        lcd.setCursor(8,1);
        lcd.print("score " + String(gameRound));
        Serial.print("win");
      }
      break;
    case 4:
      checkEndRedLed();
      removeInterruptsForSleep();
      break;
  }

}

void setStartingTime(){
  start_timer_time = millis();
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
  if (isTimeElapsed(10000)) {
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
  lcd.setCursor(0, 1);
  lcd.print(String("Diff: ") + String(gameDiff));
}

//eidted map function, in order to obtain a better range for the last number
long mapDiff(long x, long in_min, long in_max, long out_min, long out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max + 1 - in_min) + out_min;
}


bool isTimeElapsed(int time){
  long timePassed = millis() - start_timer_time;
  return timePassed > time;
}

void allLedOff(){
  buttons[0] = 0;
  buttons[1] = 0;
  buttons[2] = 0;
  buttons[3] = 0;

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
}


int getRandomNumber(){
  return random(16);
}

boolean isCorrect(){
  
  float bin = 0;
  for (int i = 0; i < 4; i++){
    if (buttons[i] == 1){
    	bin = (bin + pow(2,i));
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
    
    lcd.clear();
    lcd.home();
    lcd.print("   Game over");
    lcd.setCursor(0, 1);
    lcd.print("    score[" + String(gameRound) + "]");
    digitalWrite(LED_S, HIGH);
    setStartingTime();
    gameState = 4;
  }
}

//print remaining time in this format : ex 5.75 seconds (the last number is either 0 or 5)
void printTimeLeft(){
  int displayTime = (totalTime - timeLeft())/ 100;
  if (displayTime % 10 == 0){
    Serial.println(displayTime/10);
    lcd.setCursor(13,0);
    lcd.print(displayTime/10);
  }
}
//return the time left for the timer in milliseconds 
long timeLeft(){
  long timeLeft = millis() - start_timer_time;
  return timeLeft;
}

void addInterruptsGame(){
  enableInterrupt(BUTTON_1, buttonOnePressed, RISING);
  enableInterrupt(BUTTON_2, buttontTwoPressed, RISING);
  enableInterrupt(BUTTON_3, buttonThreePressed, RISING);
  enableInterrupt(BUTTON_4, buttonFourPressed, RISING);
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
  if (buttons[index] == 0){
    buttons[index] = 1;
    digitalWrite(led, HIGH);
  }else{
    buttons[index] = 0;
    digitalWrite(led, LOW);
  }
}

void checkEndRedLed(){
  if (isTimeElapsed(1000)) {
    digitalWrite(LED_S, LOW);
  }if (isTimeElapsed(10000)) {
    Serial.println("new Game");
    gameState = 0;
  }
}










