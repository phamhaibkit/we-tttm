
int ray1 = A5;
int ray2 = A4;

int mode1 = 2;
int mode2 = 3;
int mode3 = 4;

int doorPin = 12;
bool flag = true;

void setup() {
  Serial.begin(9600);
  pinMode(doorPin, OUTPUT);

  pinMode(mode1, INPUT_PULLUP);
  pinMode(mode2, INPUT_PULLUP);
  pinMode(mode3, INPUT_PULLUP);

  digitalWrite(doorPin, HIGH);
}

void loop() {
  int readMode1 = digitalRead(mode1);
  int readMode2 = digitalRead(mode2);
  int readMode3 = digitalRead(mode3);

  if (!readMode1) {
    digitalWrite(doorPin, HIGH);
    delay(1000);
    flag = true;
  }
  if (!readMode2) {
    digitalWrite(doorPin, LOW);
    delay(1000);
    flag = true;
  }

  if (!readMode3) {
    if (flag) {
      digitalWrite(doorPin, HIGH);
    }
    flag = false;
    int valueRay1 = analogRead(ray1);
    int valueRay2 = analogRead(ray2);

    Serial.print("Ray 1: ");
    Serial.println(valueRay1);
    Serial.print("Ray 2: ");
    Serial.println(valueRay2);

    if (valueRay1 < 220) {
      digitalWrite(doorPin, LOW);
      delay(2000);
    } else {
      digitalWrite(doorPin, HIGH);
    }
    if (valueRay2 < 220) {
      digitalWrite(doorPin, LOW);
      delay(2000);
    } else {
      digitalWrite(doorPin, HIGH);
    }
  }


}
