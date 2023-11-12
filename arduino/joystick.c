#include <stdint.h> //int x비트 같은 자료형을 쓰기위해서
#include <Arduino.h>
#include "joystick.h"
#include "button.h"
#include "xystick.h"
#include "led.h"

typedef struct joystick_t
{
	struct button_t *but[5]; // 버튼 4개의 주소 배열에 할당. 마지막index는 빈 return 값을 받기위함.
	struct xystick_t *xystick;
} joystick_t;

char selected_button;
uint8_t pin_status[4];
int* joystick_XYaxis_value[2];

void joystick_control(joystick_t* joystick_obj){
	joystick_XYaxis_value[X_PIN_INDEX]=xstick_analogRead(joystick_obj->xystick);
	joystick_XYaxis_value[Y_PIN_INDEX]=ystick_analogRead(joystick_obj->xystick);

	if(joystick_XYaxis_value[X_PIN_INDEX]==493){
		if(joystick_XYaxis_value[Y_PIN_INDEX]>515){
			joystick_XYstick_forward(joystick_obj->xystick);
		}
	}
	if(joystick_XYaxis_value[X_PIN_INDEX]==493){
		if(joystick_XYaxis_value[Y_PIN_INDEX]<515){
			joystick_XYstick_back(joystick_obj->xystick);
		}
	}
	if(joystick_XYaxis_value[X_PIN_INDEX]<493){
		joystick_XYstick_left(joystick_obj->xystick);
	}
	if(joystick_XYaxis_value[X_PIN_INDEX]>493){
		joystick_XYstick_right(joystick_obj->xystick);
	} 
	if(joystick_XYaxis_value[X_PIN_INDEX]==493){
		if(joystick_XYaxis_value[Y_PIN_INDEX]==515){
			joystick_XYstick_fixed(joystick_obj->xystick);
		}
	} 
}

void *joystick_new()
{
	return (void *)malloc(sizeof(joystick_t));
}

void joystick_ctor(joystick_t *joystick_obj) // joystick 객체를 시그니처로 받음 받은 객체는 모두 obj로 명칭
{
	for (uint8_t pin = 2, index = 0; pin < 6; pin++, index++) // 배열을 하나씩 반복하며 pin과 pinMode 초기화
	{
		joystick_obj->but[index] = button_4new(); // 배열 하나에 버튼 1개에 대한 하나의 button객체 메모리할당. button객체 생성
		if (index == 0)
		{
			joystick_obj->but[index]->button_name = 'A';
		}
		else if (index == 1)
		{
			joystick_obj->but[index]->button_name = 'B';
		}
		else if (index == 2)
		{
			joystick_obj->but[index]->button_name = 'C';
		}
		else if (index == 3)
		{
			joystick_obj->but[index]->button_name = 'D';
		}
		button_4ctor(joystick_obj->but[index], pin, INPUT_PULLUP); // button객체에 pin과 pinMode할당
	}
	joystick_obj->xystick = xystick_new();
	
}

char joystick_digitalRead(joystick_t *joystick_obj)
{
	for (int index = 0; index < 4; index++)
	{
		pin_status[index] = clicked_button(joystick_obj->but[index]);
	}
	if (pin_status[0] == LOW)
	{
		 return joystick_obj->but[0]->button_name;
	}
	else if (pin_status[1] == LOW)
	{
		 return joystick_obj->but[1]->button_name;
	}
	else if (pin_status[2] == LOW)
	{
		 return joystick_obj->but[2]->button_name;
	}
	else if (pin_status[3] == LOW)
	{
		 return joystick_obj->but[3]->button_name;
	}

	return 'E';
}
int* joystick_get_XYaxisvalue(joystick_t* joystick_obj){
	joystick_XYaxis_value[X_PIN_INDEX]=xstick_analogRead(joystick_obj->xystick);
	joystick_XYaxis_value[Y_PIN_INDEX]=ystick_analogRead(joystick_obj->xystick);
	return joystick_XYaxis_value;
}
