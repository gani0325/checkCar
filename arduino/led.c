#include <Arduino.h>
#include "led.h"


void led_RED_on()
{
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, HIGH);
}

void led_GREEN_on()
{
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);
}

void led_BLUE_on()
{
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, HIGH);
    digitalWrite(RED, LOW);
}

void led_BLUE_GREEN_on()
{
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
    digitalWrite(RED, LOW);
}

void led_RED_GREEN_on()
{
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, HIGH);
}
void led_off(){
    digitalWrite(GREEN, LOW);
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, LOW);
};