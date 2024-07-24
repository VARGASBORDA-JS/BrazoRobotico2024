#include <Servo.h>
#include <LiquidCrystal_I2C.h>
//SERIAL
String dataString = "";
bool dataComplete = false;
const char separator = ',';
const int dataLength = 7;
double datos[dataLength];

double q1 = 0;
double q2 = 0;
double q3 = 0;
double q4 = 0;
double Px = 0;
double Py = 0;
double Pz = 0;

const int SDA_PIN = PB9; // Pin para SDA pb9
const int SCL_PIN = PB8; // Pin para SCL pb8

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  Serial.begin(9600);

  servo1.attach(PA3);
  servo2.attach(PC0);
  servo3.attach(PC3);
  servo4.attach(PF3);

  servo1.write(0);
  servo2.write(0);
  servo3.write(0);
  servo4.write(0);

  Wire.begin(SDA_PIN, SCL_PIN);
  lcd.init();
  lcd.backlight();
  
}

void loop() {
  if (dataComplete) {
    for (int i = 0; i < dataLength; i++) {
      int index = dataString.indexOf(separator);
      datos[i] = dataString.substring(0, index).toFloat();
      dataString = dataString.substring(index + 1);
    }
    
    q1 = datos[0];
    q2 = datos[1];
    q3 = datos[2];
    q4 = datos[3];
    Px = datos[4];
    Py = datos[5];
    Pz = datos[6];

    servo1.write(q1);
    servo2.write(q2);
    servo3.write(q3+90);
    servo4.write(q4);

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print(q1);
    lcd.setCursor(5, 0);
    lcd.print(",");
    lcd.setCursor(6, 0);
    lcd.print(q2);
    lcd.setCursor(11, 0);
    lcd.print(",");
    lcd.setCursor(12, 0);
    lcd.print(q3);
    lcd.setCursor(17, 0);
    lcd.print(",");
    lcd.print(q4);
    lcd.setCursor(0, 1);
    lcd.print(",");
    lcd.print(Px);
    lcd.setCursor(3, 1);
    lcd.print(",");
     lcd.print(Py);
    lcd.setCursor(6, 1);
    lcd.print(",");
    lcd.print(Pz);
    lcd.setCursor(9, 1);
    lcd.print(",");

    lcd.setCursor(0, 2);
    lcd.print("A");
    lcd.setCursor(1, 2);
    lcd.print(q1);
    lcd.setCursor(5, 2);
    lcd.print("x");
    lcd.setCursor(6, 2);
    lcd.print(Px);
      lcd.setCursor(10, 2);
    lcd.print("y");
    lcd.setCursor(11, 2);
    lcd.print(Py);
    

    lcd.setCursor(0, 3);
    lcd.print("B");
    lcd.setCursor(1, 3);
    lcd.print(q2);
   

    lcd.setCursor(6, 3);
    lcd.print("c");
    lcd.setCursor(7, 3);
    lcd.print(q3);
    lcd.setCursor(13, 3);
    lcd.print("z");
    lcd.setCursor(14, 3);
    lcd.print(Pz);

    Serial.println(q1);
    Serial.println(q2);
    Serial.println(q3);
    Serial.println(q4);
    Serial.println(Px);
    Serial.println(Py);
    Serial.println(Pz);
    Serial.println(1);

    dataString = "";
    dataComplete = false;
  }
}
void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    dataString += inChar;
    if (inChar == '\n') {
      dataComplete = true;
    }
  }
}
