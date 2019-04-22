#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(5, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int soundPin = A5;
const int ledPin[9] = {A0, A1, A2, A3, A4, 12, 11, 10, 9};
const int lightPin = 2;
const int lockPin = 7;
int pinCount = 9;

int compare1 = 635;
int compare2 = 630;
int compare3 = 625;
int compare4 = 620;
int compare5 = 615;
int compare6 = 610;
int compare7 = 605;
int compare8 = 590;
int compare9 = 570;

void setup() {
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);

  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(ledPin[thisPin], OUTPUT); // Cài đặt đèn LED là OUTPUT
    digitalWrite(ledPin[thisPin], HIGH);
  }
  pinMode(lightPin, OUTPUT); // Cài đặt đèn LED là OUTPUT
  pinMode(lockPin, OUTPUT); // Cài đặt đèn LED là OUTPUT
  digitalWrite(lightPin, HIGH);
  digitalWrite(lockPin, HIGH);

  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    //while(true);
  }
  delay(2000);
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30
}

void loop() {
//  int soundValue =  avaragValue();
  int soundValue = avaragValue(5);
  Serial.print("soundValue 1: ");
  Serial.println(soundValue);
  if (soundValue > compare1) {
    clearLed();
  }

  else if ((soundValue <= compare1) && (soundValue > compare2)) {
    onLed(1);
  }

  else if ((soundValue <= compare2) && (soundValue > compare3)) {
    onLed(2);
  }
  else if ((soundValue <= compare3) && (soundValue > compare4)) {
    onLed(3);
  }
  else if ((soundValue <= compare4) && (soundValue > compare5)) {
    onLed(4);
  }

  else if ((soundValue <= compare5) && (soundValue > compare6)) {
    onLed(5);
  }

  else if ((soundValue <= compare6) && (soundValue > compare7)) {
    onLed(6);
  }

  else if ((soundValue <= compare7) && (soundValue > compare8)) {
    onLed(7);
  }

  else if ((soundValue <= compare8) && (soundValue > compare9)) {
    onLed(8);
  }
  else if (soundValue <= compare9) {
    onLed(9);
    myDFPlayer.play(1);
    digitalWrite(lightPin, LOW);
    digitalWrite(lockPin, LOW);
    delay(1000);
    while (1) {
      //      Serial.print("WHILE--");
    }
  }

  delay(300);
}

int avaragValue(int num) {
  int totalValue = 0;
  for (int i = 0; i < num; i++) {
    int soundValue = analogRead(soundPin);
    totalValue += soundValue;
  }
  return totalValue / num;
}

void onLed(int numberic) {
  clearLed();
  for (int thisPin = 0; thisPin < numberic; thisPin++) {
    digitalWrite(ledPin[thisPin], LOW);
    //    delay(10);
  }
}

void clearLed() {
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    digitalWrite(ledPin[thisPin], HIGH);
  }
}

