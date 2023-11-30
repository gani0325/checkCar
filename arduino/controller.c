#include "controller.h"

char joystick_controller(joystick_t *joystick_obj){
    char clicked_button = 'E';
    clicked_button = joystick_digitalRead(joystick_obj);
    return clicked_button;
}