// test4.cpp
#include <Arduino.h>


extern "C" void printCountTest4ByTest3(int count) {
    Serial.println(count);
}

extern "C" int CppLCDmessage(int num) {
    return num;
}

extern "C" int CppflagCommand() {
    return 1;
}