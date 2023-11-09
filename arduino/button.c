#include <stdint.h> //int8_t 사용할 수 있는 h파일.
#include "button.h"

typedef struct button_t
{					   // button 구조체
	int8_t digitalpin; // digitalpin 변수
	int8_t pin_mode;   // pin_mode 변수
} button_t;
void *button_4new()
{											 // 4개의 버튼의 객체가 생성되었다.
	return (void *)malloc(sizeof(button_t)); // 메모리 할당
}

void button_4ctor(button_t *obj, int8_t digitalpin, int8_t pin_mode)
{								   // button객체, pin번호, pinMode시그니처
	obj->digitalpin = digitalpin;  // button객체 digitalpin멤버변수에 pin번호 초기화
	obj->pin_mode = pin_mode;	   // button객체 digitalpin 멤버변수에 pin_mode 초기화
	pinMode(digitalpin, pin_mode); // wiring_digital.c소스코드에서 가져옴. arduino.h파일과는 달리 CPP이 필요없음.
	// wiring_digital.c는 Path에 파일 형태로 있다. user에게 권한을 안준다면 소스코드가 실행이 될까?
	pinMode_CPP(digitalpin, pin_mode); // 예제 코드
}
