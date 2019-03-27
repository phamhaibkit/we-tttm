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

int ledPin = 4;
//int beepPin = 2;

int tag1[5] = {65 , 93, 239, 82, 161};
int tag2[5] = {65, 93 + 1, 239, 82, 161};
int newtag[5] = {0, 0, 0, 0, 0};

int ok = -1;

// Setup variables:
//int serNum0;
//int serNum1;
//int serNum2;
//int serNum3;
//int serNum4;

void setup()
{
  Serial.begin(9600);
  SPI.begin();

  rfid.init();


  //pinMode(beepPin,OUTPUT);
  //digitalWrite(beepPin, LOW);
}

void loop()
{

  readTags();
  delay(1000);
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
      Serial.print(",");
    }

    rfid.halt();

  }
}
