#pragma once
typedef struct button_t
{					   // button 구조체
	uint8_t digitalpin; // digitalpin 변수
	uint8_t pin_status;
	char button_name;
} button_t;

    void *button_4new(); // button_t 객체할당
    void button_4ctor(struct button_t *, uint8_t, uint8_t);
    int clicked_button(struct button_t*);
