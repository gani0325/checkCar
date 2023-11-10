#pragma once
struct button_t;
#ifdef __cplusplus // avr-gcc컴파일러가 c++를 컴파일 할 때 다음과 같이 해라.
extern "C"         // 컴파일러에서 C언어가 컴파일 되도록 하는 코드
{
#endif
    void *button_4new(); // button_t 객체할당
    void button_4ctor(struct button_t *, int16_t, int16_t);
    int16_t clicked_button(struct button_t*);
#ifdef __cplusplus
}
#endif