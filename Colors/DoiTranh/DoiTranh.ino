int buttonPin = 2;    // select the input pin for the potentiometer
int lightPin = 5;      // select the pin for the LED
bool flagDone = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(lightPin, OUTPUT);

  digitalWrite(lightPin, LOW);
}

void loop() {
  if (!flagDone) {
    int buttonValue = digitalRead(buttonPin);
//    Serial.println(buttonValue);
    if (!buttonValue) {
      digitalWrite(lightPin, HIGH);
      delay(10000);
      flagDone = true;
    }
  }
  delay(100);
}
