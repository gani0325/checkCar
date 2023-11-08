#include <stdint.h>
#include "joystick.h"
#include "button.h"

enum state_t{
	OFF,
	ON
};

typedef struct joystick_t{
	struct button_t* but[5];
	//struct joystick_xy_t* xy;
}joystick_t;

char button;

void* joystick_new(){
	return (void*)malloc(sizeof(joystick_t));
}

void joystick_ctor(joystick_t* obj){
	for(int8_t i = 2, j = 0; i<6; i++, j++){
		obj->but[j] = button_4new(); //버튼 1개에 대한 하나의 객체 메모리할당
	int16_t input_pullup = get_input_pullup();
	button_4ctor(obj->but[j], i, input_pullup);
	//버튼 1개에 대한 하나의 객체 생성.
	}

	//obj->xy = xy_new();
	//xy_ctor(obj->xy);
}
char joystick_digitalRead(joystick_t* obj){
	for(int i = 0; i<4; i++){
		button = button_digitalRead(obj->but[i]);
	}
	
	return button;
}
