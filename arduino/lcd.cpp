#pragma once // h파일 반복 제어
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "lcd.h"
#ifdef __cplusplus // 컴파일러가 g++이면 다음과 같이 해라.
extern "C"         // g++컴파일러에서 C언어가 컴파일 되도록 하는 코드
{
#endif
     typedef class LiquidCrystal_I2C;
     LiquidCrystal_I2C lcd(LCD_FAMILY, COLUMN, ROW);
     void lcd_init_CPP()
     {
          // LiquidCrystal_I2C lcd;
          lcd.init();
          lcd.backlight();
     }
     void lcd_print_CPP(char* data)
     {
          lcd.setCursor(0, 0); // 1번째, 1라인에 커서 두기
          lcd.print(data);
          lcd.clear(); // 글자를 모두 지워라
     }
#ifdef __cplusplus // 컴파일러가 g++이면 다음과 같이 해라.
}
#endif