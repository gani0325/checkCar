#include <stdint.h> //int x비트 같은 자료형을 쓰기위해서
#include <Arduino.h>
// #include "joystick_model.h"

typedef struct joystick_t
{
	struct button_t *but[5]; // 버튼 4개의 주소 배열에 할당. 마지막index는 빈 return 값을 받기위함.
	struct xystick_t *xystick;
	//char data[16];
} joystick_t;

char selected_button;
uint8_t pin_status[4];
int *joystick_XYaxis_value[2];
char data[COLUMN + 1];

joystick_t *joystick;  
joystick_t* model(){
    joystick=(joystick_t*)joystick_new();
    joystick_ctor(joystick) // joystick 객체를 시그니처로 받음 받은 객체는 모두 obj로 명칭
    return joystick;
}

