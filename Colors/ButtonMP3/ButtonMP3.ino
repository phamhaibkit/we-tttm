#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int buttonPin = 2;
bool flag = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);

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
  if (!flag) {
    int valuePin = digitalRead(buttonPin);
    Serial.print("Gia tri nut nhan ");
    Serial.println(valuePin);
    if (!valuePin) {
      playAudio();
      delay(1000);
     flag = true;
    }
  }
}

void playAudio() {
  myDFPlayer.play(1);
  delay(30000);
  myDFPlayer.stop();
  delay(3000);
  myDFPlayer.play(2);
  delay(32000);
  myDFPlayer.stop();
  delay(3000);
  myDFPlayer.play(3);
  delay(25000);
  myDFPlayer.stop();
  delay(3000);
  myDFPlayer.play(4);
}


