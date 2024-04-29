#ifndef LED_H
#define LED_H

#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 7
#include "pins.h"

namespace Led {

extern Adafruit_NeoPixel pixels;

void setup();
void set_color(uint8_t r, uint8_t g, uint8_t b);
void set_color(uint8_t r, uint8_t g, uint8_t b, int n);
void set_just_one_led(uint32_t color, int n);

void set_color(uint32_t color);
void turn_off();
void turn_on();
void step();
void change_dancer();

};

#endif  // LED_H