#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(4, 5); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int drawerPin = 6;
int doorPin = 2;
bool flagPlay = false;
//bool flagSong = false;
int valuedrawPin = 0;
int valuedoorPin = 0;

int numberSong = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);

  pinMode(drawerPin, INPUT_PULLUP);
  pinMode(doorPin, INPUT_PULLUP);
  //attachInterrupt(0, openDoor, RISING);
  //digitalWrite();

  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    //while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30

  while (flagPlay == false ) {
    valuedrawPin = digitalRead(drawerPin);
    Serial.println(valuedrawPin);
    if (valuedrawPin == 1) {
      Serial.println("Phat nhac");
      flagPlay = true;
      myDFPlayer.play(1);
    }
    delay(100);
  }
}

void loop() {
  Serial.println("Loop");
  static unsigned long timer = millis();
  if (millis() - timer > 300000) {
    Serial.println("Choi nhac");
    timer = millis();
    myDFPlayer.play(1);
  }
  int valDoor = digitalRead(doorPin);
  Serial.println(valDoor);
  if (valDoor) {
    Serial.println("Bai 2");
    myDFPlayer.play(2);
    while (true);
  }
}

//void openDoor() {
//  Serial.println("INterrupt ne!!!!!");
//  flagSong = true;
//  myDFPlayer.play(2);
//}

