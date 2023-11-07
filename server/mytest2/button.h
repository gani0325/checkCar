#pragma once
struct button_t;
typedef int bool_t;
char button;
#ifdef __cplusplus
extern "C" {
#endif
void* button_4new(int); // button_t 객체할당
void button_4ctor(struct button_t*, int, int);
// 동반자 함수
void button_clear(struct button_t*);
void button_press(struct button_t*);
char button_digitalRead(struct button_t*);


#ifdef __cplusplus
}
#endif