#include "../../arduino/arduino.h"
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
	obj->result = (void*)malloc(sizeof(button_flag_t*));
	calloc(obj->result, sizeof(button_flag_t*));

	obj->digitalpin = (int*)malloc(sizeof(int));
	calloc(obj->digitalpin, sizeof(int*));
	obj->digitalpin = digitalpin+1;
	
	pinMode_CPP(digitalpin, pinMode);
}

void button_pin_delete(button_t* obj){
free(obj->digitalpin);
free(obj->result);
free(obj->pinMode);
free(obj);
} //할당제거
void button_pin_dtor(button_t* obj){

} //소멸자 파일 생성때 구현 고민 현재는 안쓰임.p663쪽 파일 닫는데 쓰임

void button_clear(button_t* obj){
obj->result->A = OFF;
obj->result->B = OFF;
obj->result->C = OFF;
obj->result->D = OFF;
}

void button_press(button_t* obj, int pin){
	button_clear(obj);
	if(obj->digitalpin == 2){
		obj->result->A = ON;
		printf("pressA");
	}else if(pin == 3){
		obj->result->B = ON;
		printf("pressB");
	}else if(pin == 4){
		obj->result->C = ON;
		printf("pressC");
	}else if(pin == 5){
		obj->result->D = ON;
		printf("pressD");
	}
}      