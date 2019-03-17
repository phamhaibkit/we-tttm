#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(5, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int ray1 = A0;
int ray2 = A1;
int ray3 = A2;

int doorPin = 11;
int ledPin = 12;

String trueString = "";
int count = 0;

void setup() {
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  pinMode(doorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(doorPin, HIGH);
  digitalWrite(ledPin, HIGH);

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
  int valueRay1 = analogRead(ray1);
  int valueRay2 = analogRead(ray2);
  int valueRay3 = analogRead(ray3);
  Serial.print("Ray 1: ");
  Serial.println(valueRay1);
  Serial.print("Ray 2: ");
  Serial.println(valueRay2);
  Serial.print("Ray 3: ");
  Serial.println(valueRay3);
  if (valueRay1 < 880) {
    myDFPlayer.play(1);
    trueString = trueString + '1';
    count++;
    delay(500);
  }
  if (valueRay2 < 880) {
    myDFPlayer.play(2);
    trueString = trueString + '2';
    count++;
    delay(500);
  }
  if (valueRay3 < 880) {
    myDFPlayer.play(3);
    trueString = trueString + '3';
    count++;
    delay(500);
  }
  if (count == 3) {
    if (trueString == "123") {
      Serial.print("Dung roi mo cua ra ");
      digitalWrite(doorPin, LOW);
      digitalWrite(ledPin, LOW);
      delay(1000);
      while (1) {
        //        Serial.println("Loop Loop ---");
      }
    } else {
      delay(4000);
      trueString = "";
      count = 0;
    }
  }
}

