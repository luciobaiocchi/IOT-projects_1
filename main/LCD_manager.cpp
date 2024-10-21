#include <LiquidCrystal_I2C.h>
#include "Red_Led.h"
#include "Difficulty_manager.h"
#include "LCD_manager.h"
#include "Arduino.h"

String msg = "Welcome to GMB! Press B1 to Start!";
int col = 0;


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2);

void initializeLCD();

void scrollText();

void displayNumber();

void displayWin(int );

void displayDifficulty(int);



void initializeLCD(){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  msg = msg + "                ";
}

void scrollText() {
    if (col < msg.length() - 15) {
        lcd.setCursor(0, 0);
        lcd.print(msg.substring(col, col + 16));
        col++;
    } else {
        col = 0;
    }
}


void displayNumber(int randomNum){
    lcd.setCursor(10, 0);
    lcd.print("  ");
    lcd.home();
    lcd.print("Number -> " + String(randomNum) + "      ");
}

void displayWin(int gameRound){
    lcd.setCursor(0,1);
    lcd.print("GOOD! Score: " + String(gameRound)+ "      ");
}

void displayGameOver(int gameRound){
    lcd.clear();
    lcd.home();
    lcd.print("   Game over!");
    lcd.setCursor(0, 1);
    lcd.print(" Final score[" + String(gameRound) + "]");
}

void displayTimeLeft(int time){
    lcd.setCursor(14,0);
    lcd.print(time);
}

void displayDifficulty(int gameDiff){
  lcd.setCursor(0, 1);
  lcd.print(String("Difficulty: ") + String(gameDiff));
}