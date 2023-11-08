#include "button.h"

typedef enum{
ON,
OFF
}state_t;

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

int* button[4];//digital pin: 4개

void* button_4new(){
	return (void*)malloc(sizeof(button_t));
}// button_t 객체할당

void button_4ctor(button_t* obj, int digitalpin, int pinMode){
	obj->digitalpin = digitalpin;
	
	pinMode_CPP(digitalpin, pinMode);
}
