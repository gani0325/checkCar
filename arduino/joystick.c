#include <stdint.h> //int x비트 같은 자료형을 쓰기위해서
#include <Arduino.h>
#include "joystick.h"
#include "button.h"
#include "xystick.h"
#include "led.h"
#include "lcd.h"

typedef struct joystick_t
{
	struct button_t *but[5]; // 버튼 4개의 주소 배열에 할당. 마지막index는 빈 return 값을 받기위함.
	struct xystick_t *xystick;
} joystick_t;

char selected_button;
uint8_t pin_status[4];
int *joystick_XYaxis_value[2];
char data[COLUMN + 1];

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
	lcd_init();
}

void joystick_lcd_print(joystick_t *joystick_obj)
{
	char clicked_button = 'E'; // 초기화
	clicked_button = joystick_digitalRead(joystick_obj);
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