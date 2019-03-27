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

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

int doorPin = 7;
int beepPin = 2;

int tag1[5] = {246 , 121, 207, 161, 225};
int tag2[5] = {97, 58, 38, 97, 28};
int newtag[5] = {0, 0, 0, 0, 0};

int ok = -1;

bool flag = false;

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  
  rfid.init();
  
  pinMode(doorPin,OUTPUT);
  digitalWrite(doorPin, HIGH);

  pinMode(beepPin,OUTPUT);
  digitalWrite(beepPin, LOW);

  delay(300);
  while(flag == false){
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
      digitalWrite(beepPin, HIGH);
      digitalWrite(doorPin, LOW);
      delay(500);
      digitalWrite(beepPin, LOW);

      ok = -1;
      flag = true;
    }
    else if (ok == 0) // if we didn't have a match
    {
      Serial.println("Rejected");
//      digitalWrite(no, LOW);
//      delay(1000);
//      digitalWrite(no, HIGH);

      ok = -1;
    }
  }
}
