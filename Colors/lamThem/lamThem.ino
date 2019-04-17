int namcham = 2;
int quat = 5;
bool flagDone = false;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(namcham, INPUT_PULLUP);
  pinMode(quat, OUTPUT);
  digitalWrite(quat, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!flagDone){
  int kiemtraNamCham = digitalRead(namcham);
  Serial.print("Gia tri kiem tra nam cham: ");
  Serial.println(kiemtraNamCham);
  if (kiemtraNamCham == 0) {
    digitalWrite(quat, LOW);
    delay(1000);
    flagDone = true;
  }
  delay(300);
  }
}
