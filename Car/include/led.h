#ifndef LED_H
#define LED_H

#include "simulate.h"

#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 7
#include "pins.h"

namespace Led {

extern Adafruit_NeoPixel pixels;

void setup();
void set_color(uint8_t r, uint8_t g, uint8_t b);
void turn_off();
void step();
void change_dancer();

};

#endif // LED_H