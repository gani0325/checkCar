#include "button.h"

typedef struct button_flag_t{
	bool_t A;
	bool_t B;
	bool_t C;
	bool_t D;	
} button_flag_t;

typedef struct button_t{
	struct button_flag_t* result;
	int digitalpin;
	int pinMode;
}button_t;


void* button_4new(int i){
	return (void*)malloc(sizeof(button_t));
	
}// button_t 객체할당

void button_4ctor(button_t* obj, int digitalpin, int pinMode){
	obj->digitalpin = digitalpin+1;
	
	pinMode_CPP(digitalpin, pinMode);
}

char button_digitalRead(button_t* obj){
	button = '0';
	if(obj->digitalpin==2){

		if(digitalRead_CPP(obj)==0x0){
			button ='A';
		}

	}else if(obj->digitalpin==3){
		
		if(digitalRead_CPP(obj)==0x0){
			button ='B';
		}

	}else if(obj->digitalpin==4){
		if(digitalRead_CPP(obj)==0x0){
			button ='C';
		}
	}else if(obj->digitalpin==5){
		if(digitalRead_CPP(obj)==0x0){
			button ='D';
		}
	}
	return button;
}