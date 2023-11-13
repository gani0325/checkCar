#pragma once

#define X_PIN_INDEX 0
#define Y_PIN_INDEX 1

typedef struct xystick_t
{
    int axisX_value;
    int axisY_value;
} xystick_t;

int xstick_analogRead(xystick_t*);
int ystick_analogRead(xystick_t*);
void joystick_XYstick_forward(struct xystick_t*);
void joystick_XYstick_back(struct xystick_t*);
void joystick_XYstick_forward_left(struct xystick_t*);
void joystick_XYstick_back_left(struct xystick_t*);
void joystick_XYstick_forward_right(struct xystick_t*);
void joystick_XYstick_back_right(struct xystick_t*);
void joystick_XYstick_fixed(struct xystick_t*);