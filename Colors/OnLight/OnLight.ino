int buttonPin = 2;    // select the input pin for the potentiometer
int lightPin = 5;      // select the pin for the LED
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(buttonPin, INPUT);
  pinMode(lightPin, OUTPUT);

  digitalWrite(buttonPin, LOW);
  digitalWrite(lightPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonValue = digitalRead(buttonPin);
  if (buttonValue) {
    digitalWrite(lightPin, HIGH);
    delay(11000);
    digitalWrite(lightPin, LOW);
    delay(1000);
    while (1) {
    }
  }
}
