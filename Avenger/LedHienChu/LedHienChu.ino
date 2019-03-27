#include <Wire.h>
#include "LiquidCrystal_I2C.h"

// Set the LCD address to 0x27 for a 16 chars and 2 line Line
LiquidCrystal_I2C lcd(0x27, 16, 2);

int timeStonePin = 2;
int powerStonePin = 3;
int spaceStonePin = 4;
int doorPin = 5;

double timeOff = 300000;

String timeDisplay = "Wakanda-31890";
String powerDisplay  = "Asgard-96572";
String spaceDisplay = "Sanctuary N5X2";


bool flagTimeStone = true;
bool flagPowerStone = false;
bool flagSpaceStone = false;

void setup()
{
  Serial.begin(9600);
  pinMode(timeStonePin, INPUT_PULLUP);
  pinMode(powerStonePin, INPUT_PULLUP);
  pinMode(spaceStonePin, INPUT_PULLUP);

  pinMode(doorPin, OUTPUT);
  digitalWrite(doorPin, LOW);
  // initialize the LCD
  lcd.begin();
  //  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.clear();
}

void loop()
{
  int timeStoneValue = digitalRead(timeStonePin);
  int powerStoneValue = digitalRead(powerStonePin);
  int spaceStoneValue = digitalRead(spaceStonePin);

  if (flagTimeStone) {
    //    Serial.print("Time Stone: ");
    //    Serial.println(timeStoneValue);
    if (!timeStoneValue) {
      Serial.print("Time duoc nhan ");
      displayText(timeDisplay);
      flagTimeStone = false;
      flagPowerStone = true;
      delay(timeOff);
      lcd.clear();
    }
  }

  if (flagPowerStone) {
    //    Serial.print("Power Stone: ");
    //    Serial.println(powerStoneValue);
    if (!timeStoneValue && !powerStoneValue) {
      Serial.print("Power duoc nhan ");
      displayText(powerDisplay);
      flagPowerStone = false;
      flagSpaceStone = true;
      delay(timeOff);
      lcd.clear();
    }

  }

  if (flagSpaceStone) {
    //    Serial.print("Space Stone: ");
    //    Serial.println(spaceStoneValue);
    if (!timeStoneValue && !powerStoneValue && !spaceStoneValue) {
      Serial.print("Space duoc nhan ");
      displayText(spaceDisplay);
      digitalWrite(doorPin, HIGH);
      flagSpaceStone = false;
    }
  }
}

void displayText(String text) {
  lcd.clear();
  lcd.setCursor (0, 0);
  lcd.print(text);
}
