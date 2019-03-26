/*
  Chương trình đọc RFID từ RFID-RC522
  Cắm chân (Arduino Uno):
  MOSI: Pin 11
  MISO: Pin 12
  SCK: Pin 13
  SDA: Pin 10
  RST: Pin 9
*/

#include <SPI.h>
#include "RFID.h"

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

int doorPin1 = 2;
int doorPin2 = 3;
int doorPin3 = 4;
int doorPin4 = 5;

int tag1[5] = {154, 51, 214, 111, 16};
int tag2[5] = {170, 69, 224, 111, 96};
int tag3[5] = {224, 234, 45, 26, 61};
int tag4[5] = {224, 106, 123, 26, 235};
int newtag[5] = {0, 0, 0, 0, 0};

int ok = -1;

bool flag = false;

void setup()
{
  Serial.begin(9600);
  SPI.begin();

  rfid.init();

  pinMode(doorPin1, OUTPUT);
  digitalWrite(doorPin1, HIGH);
  pinMode(doorPin2, OUTPUT);
  digitalWrite(doorPin2, HIGH);
  pinMode(doorPin3, OUTPUT);
  digitalWrite(doorPin3, HIGH);
  pinMode(doorPin4, OUTPUT);
  digitalWrite(doorPin4, HIGH);

}

void loop()
{
  if (!flag) {
    readTags();
  }
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
  if (compareTag(newtag, tag3) == true)
  {
    ok++;
  }
  if (compareTag(newtag, tag4) == true)
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
      digitalWrite(doorPin1, LOW);

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
