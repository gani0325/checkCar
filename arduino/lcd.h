#pragma once

#define LCD_FAMILY 0x27
#define COLUMN 16
#define ROW 2

void lcd_init();
void lcd_print(char*);