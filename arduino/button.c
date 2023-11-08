#include <stdint.h>
#include "button.h"

enum state_t{
	OFF,
	ON
};

typedef struct button_t{
	int8_t digitalpin;
	int8_t pinMode;
	char button;
}button_t;

void* button_4new(){
	return (void*)malloc(sizeof(button_t));
	
}// button_t 객체할당

void button_4ctor(button_t* obj, int8_t digitalpin, int8_t pinMode){
	obj->digitalpin = digitalpin;
	
	pinMode_CPP(digitalpin, pinMode);
}

char button_digitalRead(button_t* obj){
	obj->button = 'E';
	const int16_t low = get_LOW_CPP();
	const int16_t high = get_HIGH_CPP();
	digitalRead_CPP(obj);
		if(digitalRead_CPP(obj)==high){
			return obj->button ='A';
		}else if(digitalRead_CPP(obj)==high){
			return obj->button ='B';
		}else if(digitalRead_CPP(obj)==high){
			return obj->button ='C';
		}else if(digitalRead_CPP(obj)==high){
			return obj->button ='D';
		}
	return obj->button = 'E';
}

