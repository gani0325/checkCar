#include "joystick_model.h"
// typedef struct joystick_t
// {
// 	struct button_t *but[5]; // 버튼 4개의 주소 배열에 할당. 마지막index는 빈 return 값을 받기위함.
// 	struct xystick_t *xystick;
// 	//char data[16];
// } joystick_t;

void* joystick_new()
{
	return (void *)malloc(sizeof(joystick_t));
}

void joystick_ctor(joystick_t* joystick_obj) // joystick 객체를 시그니처로 받음 받은 객체는 모두 obj로 명칭
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
	// 	joystick_obj->xystick = xystick_new();
	// controller쪽으로	lcd_init();
}