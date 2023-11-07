// test4.cpp
#include <Arduino.h>

void printCountTest4(int count) {
  Serial.println(500);
}

extern "C" void printCountTest4ByTest3(int count) {
    Serial.println(count);
}