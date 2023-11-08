#include <Arduino.h>
#include <stdint.h>
#include "button.h"
typedef struct button_t{
	struct button_flag_t* result;
	int8_t digitalpin;
	int8_t pinMode;
}button_t;
#ifdef __cplusplus
extern "C" {
#endif
void pinMode_CPP(int8_t digitalpin, int8_t pin_Mode){
    pinMode(digitalpin, pin_Mode);
}

int digitalRead_CPP(button_t* obj){
	return digitalRead(obj->digitalpin);
}

int16_t get_LOW_CPP(){
	return LOW;
}

int16_t get_HIGH_CPP(){
	return HIGH;
}

#ifdef __cplusplus
}
#endif