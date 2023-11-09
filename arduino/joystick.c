#include <stdint.h> //int x비트 같은 자료형을 쓰기위해서
#include "joystick.h"
#include "button.h"

typedef struct joystick_t
{
	struct button_t *but[5]; // 버튼 4개의 주소 배열에 할당. 마지막index는 빈 return 값을 받기위함.
} joystick_t;

void *joystick_new()
{
	return (void *)malloc(sizeof(joystick_t));
}

void joystick_ctor(joystick_t *obj) // joystick 객체를 시그니처로 받음 받은 객체는 모두 obj로 명칭
{
	for (int8_t pin = 2, index = 0; pin < 6; pin++, index++) // 배열을 하나씩 반복하며 pin과 pinMode 초기화
	{
		obj->but[index] = button_4new();				  // 배열 하나에 버튼 1개에 대한 하나의 button객체 메모리할당. button객체 생성
		int16_t input_pullup = get_input_pullup();		  // input_pullup에 대한 값을 get하는 함수.
		button_4ctor(obj->but[index], pin, input_pullup); // button객체에 pin과 pinMode할당
	}
}
