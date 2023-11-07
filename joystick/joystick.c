#include "button/button.h"

typedef struct joystick_t{
	button_t* but;
	//joystick_xy_t* xy; 
}joystick_t;

int* joystick_button[4];//digital pin: 4개
int* joystick_xy[2];//analog pin : 2개

void* joystick_new(){
	return (void*)malloc(sizeof(joystick_t));
}// joystick_t 객체할당

void joystick_ctor(joystick_t* obj){
	obj->but = button_new();//버튼 1개에 대한 하나의 객체 메모리할당
	button_ctor(obj->but);//버튼 1개에 대한 하나의 객체 생성.

	//obj->xy = xy_new();
	//xy_ctor(obj->xy);
};

void joystick_pin_delete(joystick_t* obj){
free(obj->but);
//free(obj->xy);
free(obj);
} //할당제거

void joystick_dtor(joystick_t* obj){

}; //소멸자 파일 생성때 구현 고민 현재는 안쓰임.p663쪽 파일 닫는데 쓰임
