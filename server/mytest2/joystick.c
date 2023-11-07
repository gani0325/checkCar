#include <stdint.h>
#include "joystick.h"
#include "button.h"


typedef struct joystick_t{
	struct button_t* but;
	//struct joystick_xy_t* xy; 
}joystick_t;

void* joystick_new(){
	return (void*)malloc(sizeof(joystick_t));
}// joystick_t 객체할당

void joystick_ctor(joystick_t* obj){
	
	for(int i = 0 ; i<5; i++){
	obj->but = button_4new(i); //버튼 1개에 대한 하나의 객체 메모리할당
	int16_t input_pullup = get_input_pullup();
	button_4ctor(obj->but, i, input_pullup);
	//버튼 1개에 대한 하나의 객체 생성.
	}

	//obj->xy = xy_new();
	//xy_ctor(obj->xy);
}

char joystick_digitalRead(joystick_t* obj){
	return button_digitalRead(obj->but);
}
