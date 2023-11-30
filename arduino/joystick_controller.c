#include <stdint.h> //int x비트 같은 자료형을 쓰기위해서
#include <Arduino.h>
#include "joystick_controller.h"
typedef struct joystick_t
{
	struct button_t *but[5]; // 버튼 4개의 주소 배열에 할당. 마지막index는 빈 return 값을 받기위함.
	struct xystick_t *xystick;
	//char data[16];
} joystick_t;

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




void joystick_control(joystick_t *joystick_obj)
{
	joystick_XYaxis_value[X_PIN_INDEX] = xstick_analogRead(joystick_obj->xystick);
	joystick_XYaxis_value[Y_PIN_INDEX] = ystick_analogRead(joystick_obj->xystick);

	if (joystick_XYaxis_value[X_PIN_INDEX] == 493 || joystick_XYaxis_value[X_PIN_INDEX] == 492)
	{
		if (joystick_XYaxis_value[Y_PIN_INDEX] > 514)
		{
			joystick_XYstick_forward(joystick_obj->xystick);
		}
	}
	if (joystick_XYaxis_value[X_PIN_INDEX] == 493 || joystick_XYaxis_value[X_PIN_INDEX] == 492)
	{
		if (joystick_XYaxis_value[Y_PIN_INDEX] < 514)
		{
			joystick_XYstick_back(joystick_obj->xystick);
		}
	}
	if (joystick_XYaxis_value[Y_PIN_INDEX] > 514)
	{
		if (joystick_XYaxis_value[X_PIN_INDEX] < 492)
		{
			joystick_XYstick_forward_left(joystick_obj->xystick);
		}
		if (joystick_XYaxis_value[X_PIN_INDEX] > 493)
		{
			joystick_XYstick_forward_right(joystick_obj->xystick);
		}
	}
	if (joystick_XYaxis_value[Y_PIN_INDEX] < 514)
	{
		if (joystick_XYaxis_value[X_PIN_INDEX] > 493)
		{
			joystick_XYstick_back_right(joystick_obj->xystick);
		}
		if (joystick_XYaxis_value[X_PIN_INDEX] < 492)
		{
			joystick_XYstick_back_left(joystick_obj->xystick);
		}
	}
	if (joystick_XYaxis_value[X_PIN_INDEX] == 493 || joystick_XYaxis_value[X_PIN_INDEX] == 492)
	{
		if (joystick_XYaxis_value[Y_PIN_INDEX] == 514)
		{
			joystick_XYstick_fixed(joystick_obj->xystick);
		}
	}
}