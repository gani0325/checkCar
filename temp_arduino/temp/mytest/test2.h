// test2.h
#pragma once
int count = 0;

extern "C" void printCountTest3(int count);

#ifdef __cplusplus
extern "C" {
#endif    
int LCDmessage(int num);
#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
extern "C" {
#endif 
int flagCommand();
#ifdef __cplusplus
}
#endif