#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "joystick.h"
#include "button.h"

// 조이스틱 쉴드의 버튼이 누르는 걸 입력받기 위해 선언

// lcd 객체 선언
LiquidCrystal_I2C lcd(0x27, 16, 2); // 주소, 열, 행
// joystick 객체 생성
joystick_t *joystick;
//millis()
// led 객체 선언
int GREEN = 13;
int RED = 11;
int BLUE = 9;

void setup()
{
  Serial.begin(9600);                      // 시리얼 통신을 시작하며, 통신속도는 9600
  joystick = (joystick_t *)joystick_new(); // joystick 객체 메모리 할당
  joystick_ctor(joystick);                 // joystick 객체 시그니처로 생성자 함수안에 pin과 pinMode할당이 있다.

  lcd.init(); // LCD 초기화
  // Print a message to the LCD
  lcd.backlight(); // LCD 백라이트 켜기

  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void LCDprint(String data)
{
  lcd.setCursor(0, 0); // 1번째, 1라인에 커서 두기
  lcd.print(data);
  //delay(1500);

  lcd.clear(); // 글자를 모두 지워라
}

void loop()
{

  if (Serial.available())
  {
    char data[16] = {
        0,
    };
    char buf;

    for (int i = 0; i < 16; i++)
    {
      buf = Serial.read();
      // Serial.print("hi");
      data[i] = buf;
    }

    // Serial.print(data);
    LCDprint(data);
    //delay(500);

  }

  int X = analogRead(0); // 변수 X에 아날로그 0번핀에 입력되는 신호를 대입
  int Y = analogRead(1); // 변수 Y에 아날로그 1번핀에 입력되는 신호를 대입
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  char clicked_button = 'E';
 
 
  //delay(500);



  clicked_button = joystick_digitalRead(joystick);
  Serial.print(clicked_button);
  // int buttonValue2 = digitalRead(2); // buttonValue값 선언 시그니처 디지털 pin
  // int buttonValue3 = digitalRead(3);
  // int buttonValue4 = digitalRead(4);
  // int buttonValue5 = digitalRead(5);

  
  if (clicked_button == 'A')
  { // if문을 이용하여 각 버튼이 눌리면 알파벳이 시리얼모니터에 출력되도록 설정
    String data = "front car!";
    LCDprint(data);
  }
  if (clicked_button == 'B')
  {
    String data = "front animal!";
    LCDprint(data);
  }
  if (clicked_button == 'C')
  {
    String data = "baby in car";
    LCDprint(data);
  }
  if (clicked_button == 'D')
  {
    String data = "broken car";
    LCDprint(data);
  }
  Serial.print("X");
  Serial.print(":");
  Serial.print(X);
  Serial.print("  ");
  Serial.print("Y");
  Serial.print(":");
  Serial.print(Y);
  // if (X < 495)
  // {
  //   // 왼쪽
  //   if (Y < 515)
  //   {
  //     digitalWrite(GREEN, HIGH);
  //     digitalWrite(BLUE, LOW);
  //     digitalWrite(RED, HIGH); // 빨간불 끄기
  //   }
  //   else if (Y >= 515)
  //   {

  //     digitalWrite(GREEN, HIGH);
  //     digitalWrite(BLUE, HIGH);
  //     digitalWrite(RED, LOW);
  //   }
  // }

  // else if (X > 495)
  // {
  //   // 오른쪽
  //   if (Y < 515)
  //   {

  //     digitalWrite(GREEN, HIGH);
  //     digitalWrite(BLUE, LOW);
  //     digitalWrite(RED, HIGH);
  //   }
  //   else if (Y >= 515)
  //   {

  //     digitalWrite(GREEN, HIGH);
  //     digitalWrite(BLUE, HIGH);
  //     digitalWrite(RED, LOW);
  //   }
  // }

  // else if (X == 495)
  // {
  //   // 후진
  //   if (Y < 515)
  //   {

  //     digitalWrite(GREEN, LOW);
  //     digitalWrite(BLUE, LOW);
  //     digitalWrite(RED, HIGH);
  //   }
  //   // 전진
  //   else if (Y > 515)
  //   {

  //     digitalWrite(GREEN, LOW);
  //     digitalWrite(BLUE, HIGH);
  //     digitalWrite(RED, LOW);
  //   }
  // }

  // if (X == 495)
  // {
  //   if (Y == 515)
  //   {
  //     // digitalWrite(GREEN, LOW);
  //     // digitalWrite(BLUE, LOW);
  //     // digitalWrite(RED, LOW);
  //   }
  // }

  //delay(1000);
}