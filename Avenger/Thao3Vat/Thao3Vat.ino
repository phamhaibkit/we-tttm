#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int stonePin = 2;
bool flagPlay = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  pinMode(stonePin, INPUT_PULLUP);

  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true);
  }
  delay(500);
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30

}

void loop() {
  if (!flagPlay) {
    int valueStonne = digitalRead(stonePin);
//    Serial.println(valueStonne);
    if (!valueStonne) {
      Serial.println("Bai 1");
      myDFPlayer.play(1);
      delay(500);
      flagPlay = true;
    }
  }
}


