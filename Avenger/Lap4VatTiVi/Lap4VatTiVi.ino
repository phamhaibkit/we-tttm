
int buttonPin = 2;    // select the input pin for the potentiometer
int pinLed1 = 12;
int pinLed2 = 10;

bool flagDone = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(pinLed1, OUTPUT);
  digitalWrite(pinLed1, HIGH);
  pinMode(pinLed2, OUTPUT);
  digitalWrite(pinLed2, HIGH);
}

void loop() {
  if (!flagDone) {
    int buttonValue = digitalRead(buttonPin);
    if (!buttonValue) {
      digitalWrite(pinLed1, LOW);
      digitalWrite(pinLed2, LOW);
      delay(1000);
      flagDone = true;
    }
  }
  delay(200);
}
