#include <IRremote.h> // thư viện hỗ trợ IR remote

IRsend irsend;// gửi tín hiệu hồng hoại
// ON/OFF 20250AF  33706159

// OK 202B04F
// Tren 202D02F
// || Duoi 202708F
// Trai 20208F7
// |> Phai 2028877
// Play 202C837
// Pause 202D827
// STOP 20228D7
// Menu 20202FD
// Source 202827D

int buttonPin = 2;    // select the input pin for the potentiometer

bool flagDone = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  if (!flagDone) {
    int buttonValue = digitalRead(buttonPin);
    //    Serial.println(buttonValue);
    if (!buttonValue) {
      //      irsend.sendRaw(raw, 68, 38);
      //      delay(1000);
      for (int i = 0; i < 3; i++) {
        irsend.sendNEC(0x20250AF, 32);
        delay(40);
      }
//      irsend.sendNEC(0x20250AF, 32);
      delay(5000);
      //      delay(1000);
      //      irsend.sendNEC(0x202B04F, 32);
      //      delay(1000);
      //      flagDone = true;
    }
  }
  delay(100);
}
