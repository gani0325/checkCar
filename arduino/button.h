#pragma once
struct button_t;
#ifdef __cplusplus
extern "C" {
#endif
void* button_4new(); // button_t 객체할당
void button_4ctor(struct button_t*, int8_t, int8_t);
// 동반자 함수
char button_digitalRead(struct button_t*);

//bool_t joystick_button_click(button_t* , bool_t , bool_t , bool_t , bool_t , bool_t );
#ifdef __cplusplus
}
#endif