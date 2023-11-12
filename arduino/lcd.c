#include <Arduino.h>
#include "lcd.h"
 typedef struct lcd_t{

 }lcd_t;
 
 void* lcd_new(){
    return (void*)malloc(sizeof(lcd_t));
 }
 
void lcd_init(){
    lcd_init_CPP(); // 주소, 열, 행
}

void lcd_print(char* data){
    lcd_print_CPP(data);
};