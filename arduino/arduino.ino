#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "joystick.h"
#include "button.h"

// lcd 객체 선언
LiquidCrystal_I2C lcd(0x27, 16, 2); // 주소, 열, 행

// joystick 객체 생성
joystick_t *joystick;
int joyX = 0;
int joyY = 1;

// led 객체 선언
int GREEN = 13;
int RED = 11;
int BLUE = 9;

void setup()
{
  // 시리얼 통신을 시작, 통신속도 9600
  Serial.begin(9600);                      
  // joystick 객체 메모리 할당
  joystick = (joystick_t *)joystick_new(); 
  // joystick 객체 시그니처로 생성자 함수안에 pin과 pinMode할당이 있다
  joystick_ctor(joystick);
  // joystick 운전대
  pinMode(joyX, INPUT);
  pinMode(joyY, INPUT);

  // LCD 초기화
  lcd.init();     
  // LCD 백라이트 켜기
  lcd.backlight();

  // LED 초기화
  pinMode(RED, OUTPUT); 
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);  
}

// LCD 1행에 데이터 출력하기
void LCDprint(String data)
{
  // 1번째, 1라인에 커서 두기
  lcd.setCursor(0, 0);
  lcd.print(data);
  delay(1500);

  // 글자를 모두 지워라
  lcd.clear(); 
}

void loop() {
  // 변수에 아날로그 핀에 입력되는 신호를 대입
  int X = analogRead(joyX); 
  int Y = analogRead(joyY);

  // buttonValue값 선언 시그니처 디지털 pin
  int buttonValue2 = digitalRead(2); 
  int buttonValue3 = digitalRead(3);
  int buttonValue4 = digitalRead(4);
  int buttonValue5 = digitalRead(5);

  // TCP 에서 메시지 전달이 왔다면 (by 시리얼 통신)
  if(Serial.available()) {
      char data[16] = {0,};
      char buf;

      // 최대 16개까지 buf을 읽어서 data[i]에 넣는다
      for (int i = 0; i < 16; i++) {
          buf = Serial.read();
          data[i] = buf;
      }
      // LCD에 출력하기
      LCDprint(data);
  }
  else {
    // 각 버튼이 눌리면 4가지 상황에 대한 메시지를 LCD에 출력
    if (buttonValue2 == LOW) {                       
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
  }

  // joystick 운전대로 전진/좌우회전/후진 하면 LED 출력
  if(X < 495) {
    // 왼쪽
    if(Y < 515) {
      Serial.println('1');      
      digitalWrite(GREEN, HIGH);     
      digitalWrite(BLUE, LOW);     
      digitalWrite(RED, HIGH);
    }
    else if(Y >= 515) {
      Serial.println('1');
      digitalWrite(GREEN, HIGH);     
      digitalWrite(BLUE, HIGH);     
      digitalWrite(RED, LOW);      
    }
  }

  else if(X > 495) {
    // 오른쪽
    if(Y < 515) {
      Serial.println('2');    
      digitalWrite(GREEN, HIGH);     
      digitalWrite(BLUE, LOW);     
      digitalWrite(RED, HIGH);      
    }
    else if(Y >= 515) {
      Serial.println('2');
      digitalWrite(GREEN, HIGH);     
      digitalWrite(BLUE, HIGH);     
      digitalWrite(RED, LOW);      
    }
  }

  else if(X == 495) {
    // 후진
    if(Y < 515) {
      Serial.println('4');     
      digitalWrite(GREEN, LOW);     
      digitalWrite(BLUE, LOW);     
      digitalWrite(RED, HIGH);      
    }
    // 전진
    else if(Y > 515) {
      Serial.println('3');
      digitalWrite(GREEN, LOW);     
      digitalWrite(BLUE, HIGH);     
      digitalWrite(RED, LOW);      
    }
  }

  // 가만히 있으면 LED 꺼져있음
  if (X == 495) {
    if (Y == 515) {
      digitalWrite(GREEN, LOW);     
      digitalWrite(BLUE, LOW);     
      digitalWrite(RED, LOW);  
    }
  }

  delay(1000); 
}
