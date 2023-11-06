// mytest.ino
//#include "test2.h"

// LiquidCrystal 라이브러리 추가 
#include <Wire.h>
#include <LiquidCrystal_I2C.h>      

// 조이스틱 쉴드의 버튼이 누르는 걸 입력받기 위해 선언
const int buttonPin2 = 2;                           
const int buttonPin3 = 3;
const int buttonPin4 = 4;
const int buttonPin5 = 5;

// lcd 객체 선언
LiquidCrystal_I2C lcd(0x27, 16, 2);      // 주소, 열, 행

void setup() {
  Serial.begin(9600);                               // 시리얼 통신을 시작하며, 통신속도는 9600
 
  pinMode(buttonPin2, INPUT_PULLUP );
  pinMode(buttonPin3, INPUT_PULLUP );
  pinMode(buttonPin4, INPUT_PULLUP );
  pinMode(buttonPin5, INPUT_PULLUP );

  lcd.init();     // LCD 초기화
  // Print a message to the LCD
  lcd.backlight();        // LCD 백라이트 켜기
}

void loop() {

  int X = analogRead(0);                           // 변수 X에 아날로그 0번핀에 입력되는 신호를 대입
  int Y = analogRead(1);                           // 변수 Y에 아날로그 1번핀에 입력되는 신호를 대입
 
  int buttonValue2 = digitalRead(2);               // buttonValue값 선언
  int buttonValue3 = digitalRead(3);
  int buttonValue4 = digitalRead(4);
  int buttonValue5 = digitalRead(5);

  char data[16];
  

  if (buttonValue2 == LOW) {                       // if문을 이용하여 각 버튼이 눌리면 알파벳이 시리얼모니터에 출력되도록 설정
    char data[16] = "Car in front stops";
    printCountTest1(data);
  }
  if (buttonValue3 == LOW) {
    Serial.print("joy stick  ");
    Serial.print("X");
    Serial.print(":");
    Serial.print(X);
    Serial.print("  ");
    Serial.print("Y");
    Serial.print(":");
    Serial.print(Y);
    Serial.print("   |");
    Serial.println("A: No  B: Yes  C: No  D: No");
  }
  if (buttonValue4 == LOW) {
    Serial.print("joy stick  ");
    Serial.print("X");
    Serial.print(":");
    Serial.print(X);
    Serial.print("  ");
    Serial.print("Y");
    Serial.print(":");
    Serial.print(Y);
    Serial.print("   |");
    Serial.println("A: No  B: No  C: Yes  D: No");
  }
  if (buttonValue5 == LOW) {
    Serial.print("joy stick  ");
    Serial.print("X");
    Serial.print(":");
    Serial.print(X);
    Serial.print("  ");
    Serial.print("Y");
    Serial.print(":");
    Serial.print(Y);
    Serial.print("   |");
    Serial.println("A: No  B: No  C: No  D: Yes");
  }
  delay(500);                                        // 0.5초동안 지속

  
  // printCountTest3(count+300);
  // delay(500);
  // printCountTest4(count+400);
  // printCountTest1(count);
}