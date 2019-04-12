
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(5, 6); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

const int buttonPin[6] = {3, 8, 9, 10, 11};
const int doorPin = 12;

int pinCount = 5;

// Các biến này có thể thay đổi giá trị được
int buttonPushCounter = 0;   // số button được nhấn
String trueString = "";

int buttonState[6] = {0, 0, 0, 0, 0};
int trueState[6] = {1, 0, 1, 1, 1};

bool flagLoop = false;

void setup() {
  Serial.begin(9600); //Bật cổng Serial ở baudrate 9600
  mySoftwareSerial.begin(9600);
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(buttonPin[thisPin], INPUT_PULLUP);
  }
  pinMode(doorPin, OUTPUT); // Cài đặt đèn DOOR là OUTPUT
  digitalWrite(doorPin, LOW);

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
  if (!flagLoop) {
    // đọc giá trị hiện tại của button
    for (int thisPin = 0; thisPin < pinCount; thisPin++) {
      buttonState[thisPin] = digitalRead(buttonPin[thisPin]);
//      Serial.print("STT : ");
//      Serial.println(thisPin);
      Serial.print("Value : ");
      Serial.println(buttonState[thisPin]);
    }
    if (compareArr(buttonState, trueState)) {
      Serial.println("Dung CMNR CMNR CMNR");
      digitalWrite(doorPin, HIGH);
      myDFPlayer.play(1);
      delay(1000);
      flagLoop = true;
    }
  }
  delay(500);
}

// Compare Ar
boolean compareArr(int aa[6], int bb[6])
{
  boolean ff = false;
  int fg = 0;
  for (int cc = 0 ; cc < 6 ; cc++)
  {
    if (aa[cc] == bb[cc])
    {
      fg++;
    }
  }
  if (fg == 6)
  {
    ff = true;
  }
  return ff;
}

