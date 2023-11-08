// mytest3.ino

// LiquidCrystal 라이브러리 추가
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "test2.h"

// 조이스틱 쉴드의 버튼이 누르는 걸 입력받기 위해 선언
const int buttonPin2 = 2;
const int buttonPin3 = 3;
const int buttonPin4 = 4;
const int buttonPin5 = 5;

// lcd 객체 선언
LiquidCrystal_I2C lcd(0x27, 16, 2);      // 주소, 열, 행

void setup() {
  Serial.begin(9600);                               // 시리얼 통신을 시작하며, 통신속도는 9600

  pinMode(buttonPin2, INPUT_PULLUP );
  pinMode(buttonPin3, INPUT_PULLUP );
  pinMode(buttonPin4, INPUT_PULLUP );
  pinMode(buttonPin5, INPUT_PULLUP );

  lcd.init();     // LCD 초기화
  // Print a message to the LCD
  lcd.backlight();        // LCD 백라이트 켜기
}

// LCD 출력
void LCDprint(String data) {
  lcd.setCursor(0, 0);    // 1번째, 1라인
  lcd.print(data);
  delay(1500);

  lcd.clear();            // 글자를 모두 지워라
}

void loop() {
  
  int X = analogRead(0);                           // 변수 X에 아날로그 0번핀에 입력되는 신호를 대입
  int Y = analogRead(1);                           // 변수 Y에 아날로그 1번핀에 입력되는 신호를 대입

  int buttonValue2 = digitalRead(2);               // buttonValue값 선언
  int buttonValue3 = digitalRead(3);
  int buttonValue4 = digitalRead(4);
  int buttonValue5 = digitalRead(5);

  Serial.print(testnum);

  if (flagCommand() == 1) {
    int answer = 0;
    answer = LCDmessage(answer);

    Serial.print(answer);
  }

  // if (buttonValue2 == LOW) {                       // if문을 이용하여 각 버튼이 눌리면 알파벳이 시리얼모니터에 출력되도록 설정
  //   String data = "front car!";
  //   LCDprint(data);
  // }
  // if (buttonValue3 == LOW) {
  //   String data = "front animal!";
  //   LCDprint(data);
  // }
  // if (buttonValue4 == LOW) {
  //   String data = "baby in car";
  //   LCDprint(data);
  // }
  // if (buttonValue5 == LOW) {
  //   String data = "broken car";
  //   LCDprint(data);
  // }
  // delay(500);                                        // 0.5초동안 지속
}

// /*
//  * 예제
//  * I2C를 이용한 LCD 출력
//  */

// #include <SoftwareSerial.h>
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include <string.h>

// SoftwareSerial mySerial(10, 11); // TX RX
// LiquidCrystal_I2C lcd(0x27, 16, 2);

// void setup()
// {
//   lcd.begin();
//   lcd.backlight();
//   mySerial.begin(9600);
//   Serial.begin(9600);
// }

// char lcdChar = "";
// String lcdString = "";

// String msg1 = "";

// void loop()
// {
//   if (mySerial.available())
//   {
//     delay(100);
//     lcd.clear();
//     lcd.print(msg1);
//     while (mySerial.available())
//     {
//       lcdChar = (char)mySerial.read(); // 문자 하나씩 읽고
//       lcdString += lcdChar;            // 읽은 문자를 하나씩 더해 문자열을 만듬
//       lcd.setCursor(0, 1);
//     }
//     lcd.print(lcdString);
//     msg1 = lcdString;
//     lcdString = "";
//   }

//   if (Serial.available())
//   {
//     Serial.write(Serial.read());
//   }
// }