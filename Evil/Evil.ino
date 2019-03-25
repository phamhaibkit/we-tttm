/*
  Chương trình đọc RFID từ RFID-RC522
  Cắm chân (Arduino Uno):
  MOSI: Pin 11
  MISO: Pin 12
  SCK: Pin 13
  SDA: Pin 10
  RST: Pin 9
*/

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(5, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

#include <SPI.h>
#include "RFID.h"

#define SS_PIN 10
#define RST_PIN 9

#define SS_PIN_1 8
#define RST_PIN_1 7

#define SS_PIN_2 4
#define RST_PIN_2 3

RFID rfid(SS_PIN, RST_PIN);
RFID rfid_1(SS_PIN_1, RST_PIN_1);
RFID rfid_2(SS_PIN_2, RST_PIN_2);

int doorPin = A0;
int namchamPin = 2;

int tag[5] = {246, 202, 32, 249, 229};
int tag_1[5] = {198, 183, 27, 249, 147};
int tag_2[5] = {91, 249, 159, 89, 100};

int tagB[5] = {230, 96, 27, 249, 100};
int tagB_1[5] = {166, 83, 194, 249, 206};
int tagB_2[5] = {95, 183, 192, 73, 97};

int newtag[5] = {0, 0, 0, 0, 0};
int newtag_1[5] = {0, 0, 0, 0, 0};
int newtag_2[5] = {0, 0, 0, 0, 0};

int ok = -1;

void setup()
{
  Serial.begin(9600);
  mySoftwareSerial.begin(9600);
  SPI.begin();

  rfid.init();
  rfid_1.init();
  rfid_2.init();

  pinMode(namchamPin, INPUT_PULLUP);
  pinMode(doorPin, OUTPUT);
  digitalWrite(doorPin, LOW);
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
          if (rfid_2.isCard()) {
            if (rfid_2.readCardSerial()) {
              for (int i = 0; i < 5; i++) {
                newtag_2[i] = rfid_2.serNum[i];
              }
            }
            Serial.println("3 th Card");
            for (int i = 0; i < 5; i++) {
              Serial.print(newtag_2[i]);
              Serial.print(",");
            }
            delay(100);
            if (compareTag(newtag_2, tag_2) || compareTag(newtag_2, tagB_2)) {
              Serial.println("AKKKKKKKKKKKKKKAAAKKK");
              int valueNamcham = digitalRead(namchamPin);
              Serial.println(valueNamcham);
              if (!valueNamcham) {
                Serial.println("KICHKICHKICHKICHKICHKICHKICH");
                digitalWrite(doorPin, HIGH);
                myDFPlayer.play(1);
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
