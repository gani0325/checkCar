#include <Arduino.h>
#include "xystick.h"

 void *xystick_new(){
   return (void*)malloc(sizeof(xystick_t));
}

 int xstick_analogRead(xystick_t *xystick_obj, uint8_t analogpin){
    xystick_obj->axis_value->axisX_value=analogRead(analogpin);
    return xystick_obj->axis_value->axisX_value;
 }

 int ystick_analogRead(xystick_t *xystick_obj, uint8_t analogpin){
    xystick_obj->axis_value->axisY_value=analogRead(analogpin);
    return xystick_obj->axis_value->axisY_value;
 }
