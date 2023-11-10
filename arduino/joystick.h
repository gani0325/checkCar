#pragma once       // h파일 반복 제어
struct joystick_t; // joystick 객체 전방선언

#ifdef __cplusplus // 컴파일러가 g++이면 다음과 같이 해라.
extern "C"         // g++컴파일러에서 C언어가 컴파일 되도록 하는 코드
{
#endif
    void *joystick_new();                    // : joystick객체 할당
    void joystick_ctor(struct joystick_t *); // 조이스틱 객체생성자, pin과 pinMode 할당이 함수 실행.
    char joystick_digitalRead(struct joystick_t* );


#ifdef __cplusplus                           // 컴파일러가 g++이면 다음과 같이 해라.
}
#endif