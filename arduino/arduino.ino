#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "joystick.h"
#include "button.h"
#include "xystick.h"

// 조이스틱 쉴드의 버튼이 누르는 걸 입력받기 위해 선언

// lcd 객체 선언
LiquidCrystal_I2C lcd(0x27, 16, 2); // 주소, 열, 행
// joystick 객체 생성
joystick_t *joystick;
// led 객체 선언
int GREEN = 10;
int RED = 11;
int BLUE = 12;

void setup()
{
  Serial.begin(9600);                      // 시리얼 통신을 시작하며, 통신속도는 9600
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
  int axis_value[2];
  axis_value[X_PIN_INDEX]=joystick_get_XYaxisvalue(joystick)[X_PIN_INDEX];
  axis_value[Y_PIN_INDEX]=joystick_get_XYaxisvalue(joystick)[Y_PIN_INDEX];
  
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
  Serial.print("X");
  Serial.print(":");
  Serial.print(axis_value[X_PIN_INDEX]);
  Serial.print("  ");
  Serial.print("Y");
  Serial.print(":");
  Serial.print(axis_value[Y_PIN_INDEX]);
  
  if (axis_value[X_PIN_INDEX] < 493)
  {
    // 왼쪽
    if (axis_value[Y_PIN_INDEX] < 515)
    {
      // digitalWrite(GREEN, HIGH);
      // digitalWrite(BLUE, LOW);
      // digitalWrite(RED, HIGH); // 빨간불 끄기

      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      digitalWrite(RED, HIGH);
    }
    else if (axis_value[Y_PIN_INDEX] >= 515)
    {

      // digitalWrite(GREEN, HIGH);
      // digitalWrite(BLUE, HIGH);
      // digitalWrite(RED, LOW);

      
      digitalWrite(GREEN, LOW);
      digitalWrite(BLUE, LOW);
      digitalWrite(RED, HIGH);
    }
  }

  else if (axis_value[X_PIN_INDEX] > 493)
  {
    // 오른쪽
    if (axis_value[Y_PIN_INDEX] < 515)
    {

      // digitalWrite(GREEN, HIGH);
      // digitalWrite(BLUE, LOW);
      // digitalWrite(RED, HIGH);

      analogWrite(RED, 0);  
      analogWrite(GREEN, 255); // GREEN ON
      analogWrite(BLUE, 0);  
    }
    else if (axis_value[Y_PIN_INDEX] >= 515)
    {

      // digitalWrite(GREEN, HIGH);
      // digitalWrite(BLUE, HIGH);
      // digitalWrite(RED, LOW);

      analogWrite(RED, 0);  
      analogWrite(GREEN, 255); // GREEN ON
      analogWrite(BLUE, 0); 
    }
  }

  else if (axis_value[X_PIN_INDEX] == 493)
  {
    // 후진
    if (axis_value[Y_PIN_INDEX] < 515)
    {

      // digitalWrite(GREEN, LOW);
      // digitalWrite(BLUE, LOW);
      // digitalWrite(RED, HIGH);

      analogWrite(RED, 0);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 255);  
    }
    // 전진
    else if (axis_value[Y_PIN_INDEX] > 515)
    {

      // digitalWrite(GREEN, LOW);
      // digitalWrite(BLUE, HIGH);
      // digitalWrite(RED, LOW);

      analogWrite(RED, 0);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 255);  
    }
  }

  if (axis_value[X_PIN_INDEX] == 493)
  {
    if (axis_value[Y_PIN_INDEX] == 515)
    {
      // digitalWrite(GREEN, LOW);
      // digitalWrite(BLUE, LOW);
      // digitalWrite(RED, LOW);

      analogWrite(RED, 0);
      analogWrite(GREEN, 0);
      analogWrite(BLUE, 0); 
    }
  }
//----------------------------------
  // if (X < 493)
  // {
  //   // 왼쪽
  //   if (Y < 515)
  //   {
  //     // digitalWrite(GREEN, HIGH);
  //     // digitalWrite(BLUE, LOW);
  //     // digitalWrite(RED, HIGH); // 빨간불 끄기

  //     digitalWrite(GREEN, LOW);
  //     digitalWrite(BLUE, LOW);
  //     digitalWrite(RED, HIGH);
  //   }
  //   else if (Y >= 515)
  //   {

  //     // digitalWrite(GREEN, HIGH);
  //     // digitalWrite(BLUE, HIGH);
  //     // digitalWrite(RED, LOW);

      
  //     digitalWrite(GREEN, LOW);
  //     digitalWrite(BLUE, LOW);
  //     digitalWrite(RED, HIGH);
  //   }
  // }

  // else if (X > 493)
  // {
  //   // 오른쪽
  //   if (Y < 515)
  //   {

  //     // digitalWrite(GREEN, HIGH);
  //     // digitalWrite(BLUE, LOW);
  //     // digitalWrite(RED, HIGH);

  //     analogWrite(RED, 0);  
  //     analogWrite(GREEN, 255); // GREEN ON
  //     analogWrite(BLUE, 0);  
  //   }
  //   else if (Y >= 515)
  //   {

  //     // digitalWrite(GREEN, HIGH);
  //     // digitalWrite(BLUE, HIGH);
  //     // digitalWrite(RED, LOW);

  //     analogWrite(RED, 0);  
  //     analogWrite(GREEN, 255); // GREEN ON
  //     analogWrite(BLUE, 0); 
  //   }
  // }

  // else if (X == 493)
  // {
  //   // 후진
  //   if (Y < 515)
  //   {

  //     // digitalWrite(GREEN, LOW);
  //     // digitalWrite(BLUE, LOW);
  //     // digitalWrite(RED, HIGH);

  //     analogWrite(RED, 0);
  //     analogWrite(GREEN, 0);
  //     analogWrite(BLUE, 255);  
  //   }
  //   // 전진
  //   else if (Y > 515)
  //   {

  //     // digitalWrite(GREEN, LOW);
  //     // digitalWrite(BLUE, HIGH);
  //     // digitalWrite(RED, LOW);

  //     analogWrite(RED, 0);
  //     analogWrite(GREEN, 0);
  //     analogWrite(BLUE, 255);  
  //   }
  // }

  // if (X == 493)
  // {
  //   if (Y == 515)
  //   {
  //     // digitalWrite(GREEN, LOW);
  //     // digitalWrite(BLUE, LOW);
  //     // digitalWrite(RED, LOW);

  //     analogWrite(RED, 0);
  //     analogWrite(GREEN, 0);
  //     analogWrite(BLUE, 0); 
  //   }
}

