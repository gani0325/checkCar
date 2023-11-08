// mytest.ino
#include "test2.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  int answer = 0;
  Serial.print("첫");
  if (flagCommand() == 1) {
    Serial.print("둘");
    answer = LCDmessage(answer);
  }

  Serial.print(answer);
}