#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "joystick.h"
#include "button.h"

// 조이스틱 쉴드의 버튼이 누르는 걸 입력받기 위해 선언

// lcd 객체 선언
LiquidCrystal_I2C lcd(0x27, 16, 2); // 주소, 열, 행
// joystick 객체 생성
joystick_t *joystick;

void setup()
{
  Serial.begin(9600);                      // 시리얼 통신을 시작하며, 통신속도는 9600
  joystick = (joystick_t *)joystick_new(); // joystick 객체 메모리 할당
  joystick_ctor(joystick);                 // joystick 객체 시그니처로 생성자 함수안에 pin과 pinMode할당이 있다.
  lcd.init();                              // LCD 초기화
  // Print a message to the LCD
  lcd.backlight(); // LCD 백라이트 켜기
}

void lcd_print(String data)
{
  lcd.setCursor(0, 0); // 1번째, 1라인에 커서 두기
  lcd.print(data);
  delay(1500);

  lcd.clear(); // 글자를 모두 지워라
}

void loop()
{
  int X = analogRead(0); // 변수 X에 아날로그 0번핀에 입력되는 신호를 대입
  int Y = analogRead(1); // 변수 Y에 아날로그 1번핀에 입력되는 신호를 대입

  int buttonValue2 = digitalRead(2); // buttonValue값 선언 시그니처 디지털 pin
  int buttonValue3 = digitalRead(3);
  int buttonValue4 = digitalRead(4);
  int buttonValue5 = digitalRead(5);

  char data[16];

  if (buttonValue2 == LOW) // if문을 이용하여 각 버튼이 눌리면 알파벳이 시리얼모니터에 출력되도록 설정
  { //버튼이 high상태로 pullup되었다가. 버튼을 누르면 low로 전압이 떨어지면서 데이터를 송신한다.
    String data = "front car!";
    lcd_print(data);
  }
  if (buttonValue3 == LOW)
  {
    String data = "front animal!";
    lcd_print(data);
  }
  if (buttonValue4 == LOW)
  {
    String data = "baby in car";
    lcd_print(data);
  }
  if (buttonValue5 == LOW)
  {
    String data = "broken car";
    lcd_print(data);
  }

  delay(500); // 0.5초동안 지속
}