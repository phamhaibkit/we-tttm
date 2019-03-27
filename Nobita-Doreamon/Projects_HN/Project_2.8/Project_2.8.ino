/*
  Chương trình đọc RFID từ RFID-RC522
  Cắm chân (Arduino Uno):
  SDA: Pin 10
  SCK: Pin 13
  MOSI: Pin 11
  MISO: Pin 12
  RST: Pin 9
*/

#include <SPI.h>
#include "RFID.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

int truePin = 5;
//int falsePin = 7;
int countFalse = 0;

int tag1[5] = {202, 115, 220, 77, 40};
int tag2[5] = {42, 26, 12, 110, 82};
int newtag[5] = {0, 0, 0, 0, 0};

int ok = -1;
bool flag = false;

SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

void setup()
{
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  SPI.begin();

  rfid.init();

  pinMode(truePin, OUTPUT);
  digitalWrite(truePin, HIGH);
  //
  //  pinMode(falsePin,OUTPUT);
  //  digitalWrite(falsePin, HIGH);
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    //while(true);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(30);  //Set volume value. From 0 to 30

  while (flag == false) {
    readTags();
  }

}

void loop()
{

}

boolean compareTag(int aa[5], int bb[5])
{
  boolean ff = false;
  int fg = 0;
  for (int cc = 0 ; cc < 5 ; cc++)
  {
    if (aa[cc] == bb[cc])
    {
      fg++;
    }
  }
  if (fg == 5)
  {
    ff = true;
  }
  return ff;
}

void checkTags() // compares each tag against the tag just read
{
  ok = 0; // this variable helps decision-making,
  // if it is 1 we have a match, zero is a read but no match,
  // -1 is no read attempt made
  if (compareTag(newtag, tag1) == true)
  {
    ok++;
  }
  if (compareTag(newtag, tag2) == true)
  {
    ok++;
  }
}

void readTags()
{
  ok = -1;

  if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      for (int i = 0; i < 5; i++) {
        newtag[i] = rfid.serNum[i];
      }
    }
    for (int i = 0; i < 5; i++) {
      Serial.print(newtag[i]);
    }
    delay(300);
    checkTags();
    delay(100);

    rfid.halt();

    // now do something based on tag type
    if (ok > 0) // if we had a match
    {

      Serial.println("Accepted");
      digitalWrite(truePin, LOW);
      myDFPlayer.play(1);
      ok = -1;
      flag = true;

    }
    else if (ok == 0) // if we didn't have a match
    {
      Serial.println("Rejected");
      if (countFalse > 1) {
        myDFPlayer.play(2);
        ok = -1;
        flag = true;
        countFalse = 0;
      }
      countFalse++;
    }
  }
}
