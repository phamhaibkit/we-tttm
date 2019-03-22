
int tagPin = 2;    // select the input pin for the potentiometer
int doorPin = 12;
int lightPin = 11;

bool flagDone = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(tagPin, INPUT_PULLUP);
  pinMode(doorPin, OUTPUT);
  pinMode(lightPin, OUTPUT);
  digitalWrite(doorPin, HIGH);
  digitalWrite(lightPin, HIGH);
}

void loop() {
  if (!flagDone) {
    int buttonValue = digitalRead(tagPin);
    Serial.println(buttonValue);
    if (buttonValue) {
      Serial.println("Dung CMNR CMNR CMNR");
      digitalWrite(doorPin, LOW);
      digitalWrite(lightPin, LOW);
      delay(1000);
      flagDone = true;
    }
  }
  delay(100);
}
