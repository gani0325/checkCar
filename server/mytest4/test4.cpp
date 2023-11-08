// test4.cpp
#include <Arduino.h>

extern "C" int CppLCDmessage(int num) {
    return num;
}

extern "C" int CppflagCommand() {
    return 1;
}