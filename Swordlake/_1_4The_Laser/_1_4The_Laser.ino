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

#define SS_PIN_1 8
#define RST_PIN_1 7

RFID rfid(SS_PIN, RST_PIN);
RFID rfid_1(SS_PIN_1, RST_PIN_1);

int doorPin = 3;
int namchamPin = 2;

int tag[5] = {230, 186, 191, 249, 26};
int tag_1[5] = {54, 39, 193, 249, 41};

int tagB[5] = {182, 209, 193, 249, 95};
int tagB_1[5] = {150, 249, 183, 249, 33};

int newtag[5] = {0, 0, 0, 0, 0};
int newtag_1[5] = {0, 0, 0, 0, 0};

int ok = -1;

void setup()
{
  Serial.begin(9600);
  SPI.begin();

  rfid.init();
  rfid_1.init();

  pinMode(namchamPin, INPUT_PULLUP);
  pinMode(doorPin, OUTPUT);
  digitalWrite(doorPin, LOW);
}

void loop()
{
  readTags();
  delay(200);
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
    Serial.println("1 st Card");
    for (int i = 0; i < 5; i++) {
      Serial.print(newtag[i]);
      Serial.print(",");
    }
    delay(100);
    if (compareTag(newtag, tag) || compareTag(newtag, tagB)) {
      if (rfid_1.isCard()) {
        if (rfid_1.readCardSerial()) {
          for (int i = 0; i < 5; i++) {
            newtag_1[i] = rfid_1.serNum[i];
          }
        }
        Serial.println("2 nd Card");
        for (int i = 0; i < 5; i++) {
          Serial.print(newtag_1[i]);
          Serial.print(",");
        }
        delay(100);
        if (compareTag(newtag_1, tag_1) || compareTag(newtag_1, tagB_1)) {
          Serial.println("AKKKKKKKKKKKKKKAAAKKK");
          int valueNamcham = digitalRead(namchamPin);
          Serial.println(valueNamcham);
          if (!valueNamcham) {
            Serial.println("KICHKICHKICHKICHKICHKICHKICH");
            digitalWrite(doorPin, HIGH);
            delay(1000);
            while (1) {
              //                  Serial.println("LOOOPLOOPLOOOP---------");
            }
          }
        }

        rfid.halt();
      }
    }

    rfid.halt();
  }

}

// Compare tag
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
