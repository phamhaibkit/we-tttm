
int doorPin1 = 2;
int doorPin2 = 3;
//int doorPin3 = 4;
//int doorPin4 = 5;

int hammerPin = 12;

bool flag = false;

void setup()
{
  Serial.begin(9600);

  pinMode(doorPin1, OUTPUT);
  digitalWrite(doorPin1, HIGH);
  pinMode(doorPin2, OUTPUT);
  digitalWrite(doorPin2, HIGH);
  //  pinMode(doorPin3, OUTPUT);
  //  digitalWrite(doorPin3, HIGH);
  //  pinMode(doorPin4, OUTPUT);
  //  digitalWrite(doorPin4, HIGH);
  pinMode(hammerPin, INPUT_PULLUP);
}

void loop()
{
  if (!flag) {
    int hammerValue = digitalRead(hammerPin);
    Serial.println(hammerValue);
    if (!hammerValue) {
      digitalWrite(doorPin1, LOW);
      digitalWrite(doorPin2, LOW);
      delay(1500);
      digitalWrite(doorPin1, HIGH);
      digitalWrite(doorPin2, HIGH);
      flag = true;
    }
    delay(300);
  }
}

