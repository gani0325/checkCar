// mytest3.ino

// LiquidCrystal 라이브러리 추가
#include <string.h>
#include <stdio.h>
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

// LCD 출력
void LCDprint(String data) {
  lcd.setCursor(0, 0);    // 1번째, 1라인
  lcd.print(data);
  delay(1500);

  lcd.clear();            // 글자를 모두 지워라
}

void loop() {

  if(Serial.available()) {
      char data[16] = {0,};
      char buf;

      for (int i = 0; i < 16; i++) {
          buf = Serial.read();
          //Serial.print("hi");
          data[i] = buf;
      }

      //Serial.print(data);
      LCDprint(data);
      delay(500);
  }

  int X = analogRead(0);                           // 변수 X에 아날로그 0번핀에 입력되는 신호를 대입
  int Y = analogRead(1);                           // 변수 Y에 아날로그 1번핀에 입력되는 신호를 대입

  int buttonValue2 = digitalRead(2);               // buttonValue값 선언
  int buttonValue3 = digitalRead(3);
  int buttonValue4 = digitalRead(4);
  int buttonValue5 = digitalRead(5);

  if (buttonValue2 == LOW) {                       // if문을 이용하여 각 버튼이 눌리면 알파벳이 시리얼모니터에 출력되도록 설정
    String data = "front car!";
    LCDprint(data);
  }
  if (buttonValue3 == LOW) {
    String data = "front animal!";
    LCDprint(data);
  }
  if (buttonValue4 == LOW) {
    String data = "baby in car";
    LCDprint(data);
  }
  if (buttonValue5 == LOW) {
    String data = "broken car";
    LCDprint(data);
  }

  Serial.print(X);
  Serial.print(", ");
  Serial.println(Y);


  if(X < 495) {
    if(Y < 495) {
      Serial.println('3');      
    }
    else if(Y > 515) {
      Serial.println('1');
    }
  }
  else if(X > 515) {
    if(Y < 495) {
      Serial.println('4');      
    }
    else if(Y > 515) {
      Serial.println('2');
    }
  }

  delay(1000);               
                           // 0.5초동안 지속
}