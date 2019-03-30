/*
  shiftOut ra 1 Module LED 7 đoạn đơn
*/
//chân ST_CP của 74HC595
int latchPin = 8;
//chân SH_CP của 74HC595
int clockPin = 12;
//Chân DS của 74HC595
int dataPin = 11;

int laserPin1 = A5;
int laserPin2 = A4;
int laserPin3 = A3;
int laserPin4 = A2;
int cungPin = 2;
int treoPin = 3;
int beepPin = 5;

// Ta sẽ xây dựng mảng hằng số với các giá trị cho trước
// Các bit được đánh số thứ tự (0-7) từ phải qua trái (tương ứng với A-F,DP)
// Vì ta dùng LED 7 đoạn chung cực dương nên với các bit 0
// thì các đoạn của LED 7 đoạn sẽ sáng
// với các bit 1 thì đoạn ấy sẽ tắt

//mảng có 10 số (từ 0-9) và
const byte Seg[10] = {
  0b11000000,//0 - các thanh từ a-f sáng
  0b11111001,//1 - chỉ có 2 thanh b,c sáng
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000010,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};

static unsigned long point = 20;

void setup() {
  Serial.begin(9600);
  //Bạn BUỘC PHẢI pinMode các chân này là OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  pinMode(cungPin, INPUT_PULLUP);
  pinMode(treoPin, INPUT_PULLUP);

  pinMode(beepPin, OUTPUT);
  digitalWrite(beepPin, LOW);
}

void HienThiLED7doan(unsigned long Giatri, byte SoLed = 2) {

  byte *array = new byte[SoLed];
  for (byte i = 0; i < SoLed; i++) {
    //Lấy các chữ số từ phải quá trái
    array[i] = (byte)(Giatri % 10UL);
    Giatri = (unsigned long)(Giatri / 10UL);
  }
  digitalWrite(latchPin, LOW);
  for (int i = SoLed - 1; i >= 0; i--)
    shiftOut(dataPin, clockPin, MSBFIRST, Seg[array[i]]);

  digitalWrite(latchPin, HIGH);
  free(array);
}


void loop() {
  int valueCung = digitalRead(cungPin);
  if (!valueCung) {
    if (point == 99) {
      return;
    }
    point++;
    delay(1000);
  }

  int valueTreo = digitalRead(treoPin);
  if (!valueTreo) {
    if (point == 0) {
      return;
    }
    point--;
    delay(1000);
  }

  readLaser(laserPin1);
  readLaser(laserPin2);
  readLaser(laserPin3);
  readLaser(laserPin4);

  HienThiLED7doan(point, 2);

  //  delay(500);//Đợi 0.5 s cho mỗi lần tăng số
}

void readLaser(int pin) {
  int valueLaser = analogRead(pin);
  Serial.print("Value-");
  Serial.println(pin);
  Serial.println(valueLaser);
  if (valueLaser < 850) {
    digitalWrite(beepPin, HIGH);
    if (point == 0) {
      return;
    }
    point--;
    delay(1000);
  } else {
    digitalWrite(beepPin, LOW);
  }
}

