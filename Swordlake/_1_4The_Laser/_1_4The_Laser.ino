
int tagPin = 2;    // select the input pin for the potentiometer
int laserPin = 3;

bool flagDone = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(tagPin, INPUT_PULLUP);
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW);
}

void loop() {
  if (!flagDone) {
    int buttonValue = digitalRead(tagPin);
    Serial.println(buttonValue);
    if (!buttonValue) {
      Serial.println("Dung CMNR CMNR CMNR");
      digitalWrite(laserPin, HIGH);
      delay(1000);
      flagDone = true;
    }
  }
  delay(100);
}

