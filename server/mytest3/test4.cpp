// test4.cpp
#include <Arduino.h>

void printCountTest4(int count) {
  Serial.println(500);
}

extern "C" int printCountTest4ByTest3(int num) {
    return num;
}