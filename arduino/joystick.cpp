#include <Arduino.h> //C소스코드에서는 돌지 않고 CPP에서 도는 헤더파일

extern "C" int16_t get_input_pullup() // CPP에서 선언과 정의한뒤 C로 사용할 수 있도록 선언해주는 코드
{
    return INPUT_PULLUP; // INPUT_PULLUP 리턴
}
