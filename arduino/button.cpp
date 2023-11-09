#include <Arduino.h>
#include <stdint.h>
#include "button.h"
typedef struct button_t
{
	int8_t digitalpin;
	int8_t pin_mode;
} button_t; // 선언

#ifdef __cplusplus // 컴파일러가 g++이면 다음과 같이 해라.
extern "C"		   // g++컴파일러에서 C언어가 컴파일 되도록 하는 코드
{
#endif
	void pinMode_CPP(int8_t digitalpin, int8_t pin_mode)
	{
		pinMode(digitalpin, pin_mode);
	}

	int16_t get_LOW_CPP()
	{
		return LOW;
	}

	int16_t get_HIGH_CPP()
	{
		return HIGH;
	}

#ifdef __cplusplus
}
#endif