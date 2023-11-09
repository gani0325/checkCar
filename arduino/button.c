#include <Arduino.h>
#include <stdint.h>
#include "button.h"

enum state_t{
	OFF,
	ON
};

typedef struct button_t{
	int8_t digitalpin;
	int8_t pinMode;
	char clicked;
}button_t;

void* button_4new(){
	return (void*)malloc(sizeof(button_t));
	
}// button_t 객체할당

void button_4ctor(button_t* obj, int8_t digitalpin, int8_t pinMode){
	obj->digitalpin = digitalpin;
	
	pinMode_CPP(digitalpin, pinMode);
	//pinMode(obj->digitalpin, obj->pinMode);
}

void button_4ctor2(button_t* obj){

	pinMode(obj->digitalpin, obj->pinMode);
}

char button_digitalRead(button_t* obj){
	obj->clicked = 'E';
	const int16_t low = get_LOW_CPP();
	const int16_t high = get_HIGH_CPP();
	digitalRead_CPP(obj);
	digitalRead(obj->digitalpin);
		if(digitalRead_CPP(obj)==low){
			return obj->clicked ='A';
		}else if(digitalRead_CPP(obj)==low){
			return obj->clicked ='B';
		}else if(digitalRead_CPP(obj)==low){
			return obj->clicked ='C';
		}else if(digitalRead_CPP(obj)==low){
			return obj->clicked ='D';
		}
	return obj->clicked = 'E';
}

