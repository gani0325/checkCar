#pragma once

#define LCD_FAMILY 0x27
#define COLUMN 16
#define ROW 2

struct lcd_t;

void* lcd_new();
void lcd_init();
void lcd_print(char*);