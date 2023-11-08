#pragma once
struct button_t;
typedef int bool_t;

#ifdef __cplusplus
extern "C" {
#endif

void* button_4new(); // button_t 객체할당
void button_4ctor(struct button_t*, int, int);

#ifdef __cplusplus
}
#endif