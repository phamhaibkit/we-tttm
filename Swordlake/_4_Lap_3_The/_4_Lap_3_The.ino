#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(5, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

const int ledPin[6] = {7, 8, 9, 10, 11, 12};

int stonePin1 = 2;
int stonePin2 = 3;
int stonePin3 = 4;

bool flag1 = false;
bool flag2 = false;
bool flag3 = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  pinMode(stonePin1, INPUT_PULLUP);
  pinMode(stonePin2, INPUT_PULLUP);
  pinMode(stonePin3, INPUT_PULLUP);
  for (int thisPin = 0; thisPin < 6; thisPin++) {
    pinMode(ledPin[thisPin], OUTPUT); // Cài đặt đèn LED là OUTPUT
    digitalWrite(ledPin[thisPin], HIGH);
  }

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
  if (!flag1) {
    int valueStonne1 = digitalRead(stonePin1);
    Serial.println("Value tag 1: ");
    Serial.println(valueStonne1);
    if (!valueStonne1) {
      digitalWrite(ledPin[0], LOW);
      digitalWrite(ledPin[3], LOW);
      digitalWrite(ledPin[5], LOW);
      Serial.println("Bai 1");
      myDFPlayer.play(1);
      delay(500);
      flag1 = true;
    }
  }
  if (!flag2) {
    int valueStonne2 = digitalRead(stonePin2);
    Serial.println("Value tag 2: ");
    Serial.println(valueStonne2);
    if (!valueStonne2) {
      digitalWrite(ledPin[4], LOW);
      Serial.println("Bai 2");
      myDFPlayer.play(2);
      delay(500);
      flag2 = true;
    }
  }

  if (!flag3) {
    int valueStonne3 = digitalRead(stonePin3);
    Serial.println("Value tag 3: ");
    Serial.println(valueStonne3);
    if (!valueStonne3) {
      digitalWrite(ledPin[1], LOW);
      digitalWrite(ledPin[2], LOW);
      Serial.println("Bai 3");
      myDFPlayer.play(3);
      delay(500);
      flag3 = true;
    }
  }
}



