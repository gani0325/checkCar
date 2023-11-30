#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "lcd.h"
 typedef struct lcd_t{

 }lcd_t;
 
void lcd_init(){
    lcd.init(); // 주소, 열, 행
    lcd.backlight();
}

void lcd_print(char* data){
    lcd.setCursor(0,0);
    lcd.print(data);
    lcd.clear();
};