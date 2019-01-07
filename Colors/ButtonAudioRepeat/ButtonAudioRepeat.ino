#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(4, 5); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int buttonPin = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);

  pinMode(buttonPin, INPUT);
  //attachInterrupt(0, openDoor, RISING);
  digitalWrite(buttonPin, LOW);

  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    //while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30

}

void loop() {
  int valuePin = digitalRead(buttonPin);
  Serial.print("Gia tri nut nhan ");
  Serial.println(valuePin);
  if (valuePin) {
    playAudio();
    delay(11000);
    playAudio();
    while (1) {
    }
  }
}

void playAudio() {
  myDFPlayer.play(1);
  delay(10000);
  myDFPlayer.stop();
  myDFPlayer.play(2);
  delay(15000);
  myDFPlayer.stop();
  myDFPlayer.play(3);
  delay(7000);
  myDFPlayer.stop();
  myDFPlayer.play(4);
}


