/*
  Ket noi voi Arduino Uno hoac Mega
  ----------------------------------------------------- Nicola Coppola
   Pin layout should be as follows:
   Signal     Pin              Pin               Pin
              Arduino Uno      Arduino Mega      MFRC522 board
   ------------------------------------------------------------
   Reset      9                5                 RST
   SPI SS     10               53                SDA
   SPI MOSI   11               51                MOSI
   SPI MISO   12               50                MISO
   SPI SCK    13               52                SCK

*/


#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <SPI.h>
#include "RFID.h"

#define SS_PIN 10
#define RST_PIN 9

int doorPin = 7;

RFID rfid(SS_PIN, RST_PIN);
int tag1[5] = {10,90,12,110,50};
int tag2[5] = {122 , 33, 162, 108, 149};
int newtag[5] = {0, 0, 0, 0, 0};

int ok = -1;

SoftwareSerial mySoftwareSerial(2, 3); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

bool flag = false;


void setup() {
  // put your setup code here, to run once:
  mySoftwareSerial.begin(9600);
  Serial.begin(9600);
  SPI.begin();

  rfid.init();

  pinMode(doorPin, OUTPUT);
  digitalWrite(doorPin, HIGH);

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

void loop() {
  
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
    //    for (int i = 0; i < 5; i++) {
    //      Serial.print(newtag[i]);
    //    }

    checkTags();
    delay(300);

    rfid.halt();

    // now do something based on tag type
    if (ok > 0) // if we had a match
    {
      Serial.println("Accepted");
      myDFPlayer.play(1);
     // myDFPlayer.enableLoopAll();
      digitalWrite(doorPin, LOW);
//      delay(11000);
//      digitalWrite(doorPin, HIGH);
      ok = -1;
      flag = true;
    }
    else if (ok == 0) // if we didn't have a match
    {
      Serial.println("Rejected");

      ok = -1;
    }
  }
}
