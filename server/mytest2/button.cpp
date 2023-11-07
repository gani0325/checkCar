#include <Arduino.h>
#include "button.h"
typedef struct button_t{
	struct button_flag_t* result;
	int digitalpin;
	int pinMode;
}button_t;
#ifdef __cplusplus
extern "C" {
#endif
void pinMode_CPP(int digitalpin, int pin_Mode){
    pinMode(digitalpin, pin_Mode);
}

int16_t digitalRead_CPP(button_t* obj){
	
  	return digitalRead(obj->digitalpin);
}

#ifdef __cplusplus
}
#endif