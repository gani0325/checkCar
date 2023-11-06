#include <Wire.h>
#include <LiquidCrystal_I2C.h>


// 주소, 열, 행
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(9600);
    lcd.init();     // LCD 초기화
    // Print a message to the LCD
    lcd.backlight();        // LCD 백라이트 켜기
}

void loop() {
    Serial.print("hihihih");
    lcd.setCursor(0, 0);    // 1번째, 1라인
    lcd.print("Hello, world");
    delay(500);
    lcd.setCursor(0, 1);    // 1번째, 2라인
    lcd.print("gani, world!!");
    delay(500);
}


// #include <LiquidCrystal_I2C.h>     //LiquidCrystal 라이브러리 추가 
// LiquidCrystal_I2C lcd(0x3F, 16, 2);  //lcd 객체 선언
 
// void setup()
// { 
//   Serial.begin(9600);
//   lcd.init(); //LCD 사용 시작
// }
 
// void loop()
// {
//   Serial.print("afjdsakfadsf");
//   lcd.setCursor(0, 0);    // 커서를 5, 0에 가져다 놓아라. (열, 행)
//   lcd.print("Hi ^^");     // 5, 0에 Hi ^^를 출력해라.
//   delay(1000);            // 1초 대기
//   lcd.setCursor(0, 1);    // 커서를 3, 1로 가져다 놓아라. (열, 행)
//   lcd.print("Codingrun"); // Codingrun을 입력해라.
//   delay(1000);            // 1초 대기 
//   lcd.clear();            // 글자를 모두 지워라.
//   delay(1000);            // 1초 대기
// }
