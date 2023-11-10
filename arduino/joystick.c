#include <stdint.h> //int x비트 같은 자료형을 쓰기위해서
#include <Arduino.h>
#include "joystick.h"
#include "button.h"

typedef struct joystick_t
{
	struct button_t *but[5]; // 버튼 4개의 주소 배열에 할당. 마지막index는 빈 return 값을 받기위함.
	char button_name;
} joystick_t;

char selected_button;
int16_t pin_status;

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
			joystick_obj->button_name = 'A';
		}
		else if (index == 1)
		{
			joystick_obj->button_name = 'B';
		}
		else if (index == 2)
		{
			joystick_obj->button_name = 'C';
		}
		else if (index == 3)
		{
			joystick_obj->button_name = 'D';
		}
		button_4ctor(joystick_obj->but[index], pin, INPUT_PULLUP); // button객체에 pin과 pinMode할당
	}
}

char joystick_digitalRead(joystick_t *joystick_obj)
{

	// digitalWrite(13, clicked_button(joystick_obj->but[0]));
	// digitalWrite(11, clicked_button(joystick_obj->but[1]));
	// digitalWrite(9, clicked_button(joystick_obj->but[2]));  //동작확인

	// digitalWrite(9, clicked_button(joystick_obj->but[3]));

		pin_status=clicked_button(joystick_obj->but[0]);
		pin_status=clicked_button(joystick_obj->but[1]);
		pin_status=clicked_button(joystick_obj->but[2]);
		pin_status=clicked_button(joystick_obj->but[3]);
		if(pin_status==LOW){
			//Serial.print("LOW");
			digitalWrite(13, LOW);
			return joystick_obj->button_name;
		}
		else if(pin_status==HIGH){
			digitalWrite(13, HIGH);
			joystick_obj->button_name = 'E';
		}
	return joystick_obj->button_name;
}
