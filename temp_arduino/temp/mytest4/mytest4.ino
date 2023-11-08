// mytest3.ino

// LiquidCrystal 라이브러리 추가
#include "test2.h"

void setup() {
  Serial.begin(9600);                               // 시리얼 통신을 시작하며, 통신속도는 9600
}


void loop() {
  Serial.print("hi");
  
  if (flagCommand() == 1) {
    Serial.print("hello");
    int answer = 0;
    answer = LCDmessage(answer);

    Serial.print(answer);
  }
}