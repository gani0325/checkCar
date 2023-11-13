#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>
#include "joystick.h"
#include "button.h"
#include "xystick.h"
#include "led.h"
#include "lcd.h"

// joystick 객체 생성
joystick_t *joystick;   

void setup()
{
  Serial.begin(9600);    // 시리얼 통신을 시작하며, 통신속도는 9600
  //joystick 생성
  joystick = (joystick_t *)joystick_new(); // joystick 객체 메모리 할당
  joystick_ctor(joystick);                 // joystick 객체 시그니처로 생성자 함수안에 pin과 pinMode할당이 있다.
}

void loop()
{

  // int x=analogRead(X_PIN_INDEX);
  // int y=analogRead(Y_PIN_INDEX);
  // Serial.print("x:");
  // Serial.print(x);
  // Serial.print("y:");
  // Serial.print(y);
  // Serial.print("\n");

  joystick_control(joystick);
  joystick_lcd_print(joystick);
}
