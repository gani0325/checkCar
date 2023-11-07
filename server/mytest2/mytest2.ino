
// mytest.ino
//#include "test2.h"

// LiquidCrystal 라이브러리 추가 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "joystick.h"
#include "button.h"

// 조이스틱 쉴드의 버튼이 누르는 걸 입력받기 위해 선언

// lcd 객체 선언
LiquidCrystal_I2C lcd(0x27, 16, 2);      // 주소, 열, 행
 joystick_t* joystick;
void setup() {
  Serial.begin(9600);    
  joystick = (joystick_t*)joystick_new();                           // 시리얼 통신을 시작하며, 통신속도는 9600
  joystick_ctor(joystick);
  lcd.init();     // LCD 초기화
  // Print a message to the LCD
  lcd.backlight();        // LCD 백라이트 켜기
}


// test1.ino
void printCountTest1(String data) {
  lcd.setCursor(0, 0);    // 1번째, 1라인
  lcd.print(data);
  delay(1500);
  
  lcd.clear();            // 글자를 모두 지워라
}

void loop() {

  int X = analogRead(0);                           // 변수 X에 아날로그 0번핀에 입력되는 신호를 대입
  int Y = analogRead(1);                           // 변수 Y에 아날로그 1번핀에 입력되는 신호를 대입
 
  char buttonValue = joystick_digitalRead(joystick);

  char data[16];
  

  if (buttonValue== 'A') {                       // if문을 이용하여 각 버튼이 눌리면 알파벳이 시리얼모니터에 출력되도록 설정
    String data = "front car!";
    printCountTest1(data);
  }
  if (buttonValue == 'B') {
    String data = "front animal!";
    printCountTest1(data);
  }
  if (buttonValue == 'C') {
    String data = "baby in car";
    printCountTest1(data);
  }
  if (buttonValue == 'D') {
    String data = "broken car";
    printCountTest1(data);
  }
  delay(500);                                        // 0.5초동안 지속
}