#include <stdint.h>
#include "joystick.h"
#include "button.h"


typedef struct joystick_t{
	struct button_t* but;
	//struct joystick_xy_t* xy; 
}joystick_t;

int* joystick_button[4];//digital pin: 4개
int* joystick_xy[2];//analog pin : 2개

void* joystick_new(){
	return (void*)malloc(sizeof(joystick_t));
}// joystick_t 객체할당

void joystick_ctor(joystick_t* obj){
	
	for(signed int i = 2 ; i<6; i++){
	obj->but = button_4new(); //버튼 1개에 대한 하나의 객체 메모리할당
	int16_t input_pullup = get_input_pullup();
	button_4ctor(obj->but, i, input_pullup);
	//버튼 1개에 대한 하나의 객체 생성.
	}

	//obj->xy = xy_new();
	//xy_ctor(obj->xy);
}

