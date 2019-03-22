
const int buttonPin[6] = {2, 3, 4, 5, 6, 7};
const int doorPin = 12;

int pinCount = 6 ;

// Các biến này có thể thay đổi giá trị được
int buttonPushCounter = 0;   // số button được nhấn
String trueString = "";

int buttonState[6] = {1, 1, 1, 1, 1, 1};
int trueState[6] = {0, 0, 0, 0, 1, 1};

bool flagLoop = false;

void setup() {
  Serial.begin(9600); //Bật cổng Serial ở baudrate 9600
  for (int thisPin = 0; thisPin < pinCount; thisPin++) {
    pinMode(buttonPin[thisPin], INPUT_PULLUP);
  }
  pinMode(doorPin, OUTPUT); // Cài đặt đèn DOOR là OUTPUT
  digitalWrite(doorPin, LOW);
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

