#include <Arduino.h>
#include "xystick.h"
#include "led.h"

 void *xystick_new(){
   return (void*)malloc(sizeof(xystick_t));
}

 int xstick_analogRead(xystick_t *xystick_obj){
    xystick_obj->axisX_value=analogRead(X_PIN_INDEX);
    return xystick_obj->axisX_value;
 }

 int ystick_analogRead(xystick_t *xystick_obj){
    xystick_obj->axisY_value=analogRead(Y_PIN_INDEX);
    return xystick_obj->axisY_value;
 }

void joystick_XYstick_forward(xystick_t* xystick_obj){
         led_BLUE_on();
}
void joystick_XYstick_back(xystick_t* xystick_obj){
         led_RED_on();
}
void joystick_XYstick_forward_left(xystick_t* xystick_obj){
         led_BLUE_GREEN_on();
}
void joystick_XYstick_back_left(xystick_t* xystick_obj){
         led_RED_GREEN_on();
}
void joystick_XYstick_forward_right(xystick_t* xystick_obj){
         led_BLUE_GREEN_on();
}
void joystick_XYstick_back_right(xystick_t* xystick_obj){
         led_RED_GREEN_on();
}
void joystick_XYstick_fixed(xystick_t* xystick_obj){
         led_off();
}