#include <stdint.h> //int x비트 같은 자료형을 쓰기위해서
#include <Arduino.h>
#include "joystick_view.h"


void joystick_lcd_print(joystick_t *joystick_obj, char clicked_button)
{
	// if(joystick_obj->data!=NULL){
	// 	lcd_print(joystick_obj->data);
	// } 서버용 데이터
	if (clicked_button == 'A')
	{ // if문을 이용하여 각 버튼이 눌리면 알파벳이 시리얼모니터에 출력되도록 설정
		char data[COLUMN + 1] = "front car!";
		lcd_print(data);
	}
	if (clicked_button == 'B')
	{
		char data[COLUMN + 1] = "front animal!";
		lcd_print(data);
	}
	if (clicked_button == 'C')
	{
		char data[COLUMN + 1] = "baby in car";
		lcd_print(data);
	}
	if (clicked_button == 'D')
	{
		char data[COLUMN + 1] = "broken car";
		lcd_print(data);
	}
};



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