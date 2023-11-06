// mytest.ino
#include "test2.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  printCountTest3(count+300);
  delay(500);
  printCountTest4(count+400);
  printCountTest1(count);
}