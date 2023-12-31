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

typedef struct joystick_t
{
	struct button_t *but[5]; // 버튼 4개의 주소 배열에 할당. 마지막index는 빈 return 값을 받기위함.
	struct xystick_t *xystick;
	char data[16];
} joystick_t;

void setup()
{
  Serial.begin(9600);    // 시리얼 통신을 시작하며, 통신속도는 9600
  //joystick 생성
  joystick = (joystick_t *)joystick_new(); // joystick 객체 메모리 할당
  joystick_ctor(joystick);                 // joystick 객체 시그니처로 생성자 함수안에 pin과 pinMode할당이 있다.
}

void loop()
{
	if(Serial.available()){
      char buf;
      // 최대 16개까지 buf을 읽어서 data[i]에 넣는다
      for (int i = 0; i < 16; i++) {
          buf = Serial.read();
          joystick->data[i] = buf;
      }
      // LCD에 출력하기
      joystick_lcd_print(joystick);
  	}
  joystick_control(joystick);
  
}
