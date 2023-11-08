#include <Arduino.h>

extern "C" int16_t get_input_pullup(){
    return INPUT_PULLUP;
}
