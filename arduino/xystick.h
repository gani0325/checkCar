#pragma once

#define X_PIN_INDEX 0
#define Y_PIN_INDEX 1
typedef union axis_value{
        int axisX_value;
        int axisY_value;
    }axis_value;

typedef struct xystick_t
{
    axis_value* axis_value;
} xystick_t;

int xstick_analogRead(xystick_t*, uint8_t);
int ystick_analogRead(xystick_t*, uint8_t);