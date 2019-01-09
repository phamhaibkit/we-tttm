int button = 13;
int led = 2;
void setup() {
  pinMode(button, INPUT);  //Cài đặt chân D11 ở trạng thái đọc dữ liệu
  pinMode(led,OUTPUT); // Cài đặt chân D2 dưới dạng OUTPUT
  digitalWrite(led,LOW);
}

void loop() {
  int buttonStatus = digitalRead(button);    //Đọc trạng thái button
  if (buttonStatus == HIGH) { // Nếu mà button bị nhấn
    digitalWrite(led,HIGH); // Đèn led sáng
    delay(1000);
    while(1){
      }
  } 
}
