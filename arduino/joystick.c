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
	
<<<<<<< HEAD:server/mytest2/joystick.c
	for(int i = 0 ; i<5; i++){
	obj->but = button_4new(i); //버튼 1개에 대한 하나의 객체 메모리할당
=======
	for(signed int i = 2 ; i<6; i++){
	obj->but = button_4new(); //버튼 1개에 대한 하나의 객체 메모리할당
>>>>>>> 06f1ec22470af0ae50e059118e759e0c73a2bb7d:arduino/joystick.c
	int16_t input_pullup = get_input_pullup();
	button_4ctor(obj->but, i, input_pullup);
	//버튼 1개에 대한 하나의 객체 생성.
	}

	//obj->xy = xy_new();
	//xy_ctor(obj->xy);
}

<<<<<<< HEAD:server/mytest2/joystick.c
char joystick_digitalRead(joystick_t* obj){
	return button_digitalRead(obj->but);
}
=======
>>>>>>> 06f1ec22470af0ae50e059118e759e0c73a2bb7d:arduino/joystick.c
