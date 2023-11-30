#pragma once       // h파일 반복 제어

#ifdef __cplusplus // 컴파일러가 g++이면 다음과 같이 해라.
extern "C"         // g++컴파일러에서 C언어가 컴파일 되도록 하는 코드, arduino.ino 에서 동작함.
{
#endif
    void *joystick_new();                    // : joystick객체 할당
    void joystick_ctor(struct joystick_t *); // 조이스틱 객체생성자, pin과 pinMode 할당이 함수 실행.
    void joystick_control(struct joystick_t *);
    void joystick_lcd_print(struct joystick_t *);
#ifdef __cplusplus // 컴파일러가 g++이면 다음과 같이 해라.
}
#endif

// button
char joystick_digitalRead(struct joystick_t *);
// XYstick
int *joystick_get_XYaxisvalue(struct joystick_t *);
// LED
void joystick_XYstick_forward();
void joystick_XYstick_back();
void joystick_XYstick_forward_left();
void joystick_XYstick_back_left();
void joystick_XYstick_forward_right();
void joystick_XYstick_back_right();
void joystick_XYstick_fixed();
// lcd
void lcd_ctor(uint8_t, uint8_t, uint8_t);
