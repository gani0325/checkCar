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
	
	for(int i = 0 ; i<5; i++){
	obj->but = button_4new(); //버튼 1개에 대한 하나의 객체 메모리할당
	int16_t input_pullup = get_input_pullup();
	button_4ctor(obj->but, i, input_pullup);
	//버튼 1개에 대한 하나의 객체 생성.
	}

	//obj->xy = xy_new();
	//xy_ctor(obj->xy);
}

void joystick_delete(joystick_t* obj){
	button_pin_delete(obj->but);
	free(obj->but);
	//free(obj->xy);
	free(obj);
} //할당제거

void joystick_dtor(joystick_t* obj){

} //소멸자 파일 생성때 구현 고민 현재는 안쓰임.p663쪽 파일 닫는데 쓰임
