#include <Arduino.h>

extern "C" void pinMode_CPP(int digitalpin, int pin_Mode){
    pinMode(digitalpin, pin_Mode);
}