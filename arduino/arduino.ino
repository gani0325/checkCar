#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "joystick.h"
#include "button.h"
#include "xystick.h"
#include "led.h"

// 조이스틱 쉴드의 버튼이 누르는 걸 입력받기 위해 선언

// lcd 객체 선언
LiquidCrystal_I2C lcd(0x27, 16, 2); // 주소, 열, 행
// joystick 객체 생성
joystick_t *joystick;   

void setup()
{
  Serial.begin(9600);    // 시리얼 통신을 시작하며, 통신속도는 9600
  //joystick 생성
  joystick = (joystick_t *)joystick_new(); // joystick 객체 메모리 할당
  joystick_ctor(joystick);                 // joystick 객체 시그니처로 생성자 함수안에 pin과 pinMode할당이 있다.
  lcd.init(); // LCD 초기화
  // Print a message to the LCD
  lcd.backlight(); // LCD 백라이트 켜기

}

void LCDprint(String data)
{
  lcd.setCursor(0, 0); // 1번째, 1라인에 커서 두기
  lcd.print(data);
  lcd.clear(); // 글자를 모두 지워라
}

void loop()
{

  if (Serial.available())
  {
    char data[16] = {
        0,
    };
    char buf;

    for (int i = 0; i < 16; i++)
    {
      buf = Serial.read();
      data[i] = buf;
    }
    LCDprint(data);
  }

  char clicked_button = 'E';//초기화
  clicked_button = joystick_digitalRead(joystick);
  Serial.print(clicked_button);
  if (clicked_button == 'A')
  { // if문을 이용하여 각 버튼이 눌리면 알파벳이 시리얼모니터에 출력되도록 설정
    String data = "front car!";
    LCDprint(data);
  }
  if (clicked_button == 'B')
  {
    String data = "front animal!";
    LCDprint(data);
  }
  if (clicked_button == 'C')
  {
    String data = "baby in car";
    LCDprint(data);
  }
  if (clicked_button == 'D')
  {
    String data = "broken car";
    LCDprint(data);
  }
  
  joystick_control(joystick);
}

