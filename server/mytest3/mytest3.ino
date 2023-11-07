// // mytest3.ino

// // LiquidCrystal 라이브러리 추가
// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
// #include "test2.h"

// // 조이스틱 쉴드의 버튼이 누르는 걸 입력받기 위해 선언
// const int buttonPin2 = 2;
// const int buttonPin3 = 3;
// const int buttonPin4 = 4;
// const int buttonPin5 = 5;

// // lcd 객체 선언
// LiquidCrystal_I2C lcd(0x27, 16, 2);      // 주소, 열, 행

// void setup() {
//   Serial.begin(9600);                               // 시리얼 통신을 시작하며, 통신속도는 9600

//   pinMode(buttonPin2, INPUT_PULLUP );
//   pinMode(buttonPin3, INPUT_PULLUP );
//   pinMode(buttonPin4, INPUT_PULLUP );
//   pinMode(buttonPin5, INPUT_PULLUP );

//   lcd.init();     // LCD 초기화
//   // Print a message to the LCD
//   lcd.backlight();        // LCD 백라이트 켜기
// }

// // LCD 출력
// void LCDprint(String data) {
//   lcd.setCursor(0, 0);    // 1번째, 1라인
//   lcd.print(data);
//   delay(1500);

//   lcd.clear();            // 글자를 모두 지워라
// }

// void loop() {

//   int X = analogRead(0);                           // 변수 X에 아날로그 0번핀에 입력되는 신호를 대입
//   int Y = analogRead(1);                           // 변수 Y에 아날로그 1번핀에 입력되는 신호를 대입

//   int buttonValue2 = digitalRead(2);               // buttonValue값 선언
//   int buttonValue3 = digitalRead(3);
//   int buttonValue4 = digitalRead(4);
//   int buttonValue5 = digitalRead(5);

//   if (flagCommand() == 1) {
//     int answer = 0;
//     answer = LCDmessage(answer);

//     Serial.print(answer);
//   }

//   // if (buttonValue2 == LOW) {                       // if문을 이용하여 각 버튼이 눌리면 알파벳이 시리얼모니터에 출력되도록 설정
//   //   String data = "front car!";
//   //   LCDprint(data);
//   // }
//   // if (buttonValue3 == LOW) {
//   //   String data = "front animal!";
//   //   LCDprint(data);
//   // }
//   // if (buttonValue4 == LOW) {
//   //   String data = "baby in car";
//   //   LCDprint(data);
//   // }
//   // if (buttonValue5 == LOW) {
//   //   String data = "broken car";
//   //   LCDprint(data);
//   // }
//   // delay(500);                                        // 0.5초동안 지속
// }

/*
 * 예제
 * I2C를 이용한 LCD 출력
 */

#include <Wire.h>              // I2C 통신 라이브러리 설정
#include <LiquidCrystal_I2C.h> // I2C LCD 라이브러리 설정

LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD I2C adrress 설정

void setup()
{
  Serial.begin(9600); // 9600 bps로 시리얼 통신 설정
  lcd.init();         // LCD 설정
  lcd.clear();        // LCD를 모두 지운다.
  lcd.backlight();    // 백라이트를 켠다

  // Arduino LCD, Welcome 표시
  lcd.setCursor(0, 0);
  lcd.print("Arduino LCD");
  delay(1000);
  lcd.setCursor(0, 1);
  lcd.print("Welcom!");
  delay(250);

  // LCD 백라이트를 두 번 점멸
  lcd.noBacklight();
  delay(250);
  lcd.backlight();
  delay(250);
  lcd.noBacklight();
  delay(250);
  lcd.backlight();
  delay(3000);

  // Open Serial Monitor, Type to dispaly 표시
  lcd.clear();
  lcd.setCursor(0, 0); // Start at character 0 on line 0
  lcd.print("Open Serial Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Type to display");
}

void loop()
{
  // 시리어 통신 수신값이 있을 때
  if (Serial.available())
  {
    delay(100);
    lcd.clear();                 // 모두 삭제
    lcd.setCursor(0, 0);         // 커서를 좌측 상단으로
    lcd.print("Message for PC"); // 메지지 출력
    lcd.setCursor(0, 1);         // 커서를 두 번째 줄로

    // LCD에 PC에서 전송된 데이터를 출력
    while (Serial.available() > 0)
    {
      lcd.write(Serial.read());
    }
  }
}