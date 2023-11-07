#pragma once
struct button_t;
typedef int bool_t;
#ifdef __cplusplus
extern "C" {
#endif
void* button_4new(); // button_t 객체할당
void button_4ctor(struct button_t*, int, int);
void button_pin_delete(struct button_t*);//할당제거
void button_pin_dtor(struct button_t*); //소멸자 파일 생성때 구현 고민 현재는 안쓰임.p663쪽 파일 닫는데 쓰임
// 동반자 함수
void button_clear(struct button_t*);
void button_press(struct button_t*, int);                      
#ifdef __cplusplus
}
#endif