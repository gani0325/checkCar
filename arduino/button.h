#pragma once
typedef struct button_t
{					   // button 구조체
	uint8_t digitalpin; // digitalpin 변수
	uint8_t pin_status;
	char button_name;
} button_t;

#ifdef __cplusplus // avr-gcc컴파일러가 c++를 컴파일 할 때 다음과 같이 해라.
extern "C"         // 컴파일러에서 C언어가 컴파일 되도록 하는 코드
{
#endif
    void *button_4new(); // button_t 객체할당
    void button_4ctor(struct button_t *, uint8_t, uint8_t);
    int clicked_button(struct button_t*);
#ifdef __cplusplus
}
#endif