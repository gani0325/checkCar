#pragma once
struct joystick_t;
#ifdef __cplusplus
extern "C" {
#endif
void* joystick_new(); // : pin 번호 할당 + pin mode 설정(상속받아서 이용할 것 pin은 직접 쓰고, 
//pinMode는 input_pullup) 할당자
void joystick_ctor(struct joystick_t*); // 조이스틱 객체생성자
<<<<<<< HEAD:server/mytest2/joystick.h
char joystick_digitalRead(struct joystick_t*);

=======
>>>>>>> 06f1ec22470af0ae50e059118e759e0c73a2bb7d:arduino/joystick.h

#ifdef __cplusplus
}
#endif