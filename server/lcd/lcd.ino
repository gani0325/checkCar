#include <Wire.h>
#include <LiquidCrystal_I2C.h>      // LiquidCrystal 라이브러리 추가 


// 주소, 열, 행
LiquidCrystal_I2C lcd(0x27, 16, 2);      // lcd 객체 선언

void setup() {
    Serial.begin(9600);
    lcd.init();     // LCD 초기화
    // Print a message to the LCD
    lcd.backlight();        // LCD 백라이트 켜기
}

void loop() {
    Serial.print("hihihih");
    lcd.setCursor(0, 0);    // 1번째, 1라인 (열, 행)
    lcd.print("Hello, world");

    lcd.clear();            // 글자를 모두 지워라
    delay(500);
}