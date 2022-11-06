#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 7

Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
// Thread thread_led = Thread();

#include "light_dancer.h"

namespace Led {

basic_light_dancer *_dancer;

void setup() {
  _dancer = new police_light_dancer;
  pixels.begin();
  pixels.setBrightness(120);
  pixels.show();
  _dancer->pixels = &pixels;
}
void set_color(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++)
    pixels.setPixelColor(i, pixels.Color(g, r, b));
  pixels.show();
}
void turn_off() {
  set_color(0, 0, 0);
}

void step() {
  _dancer->step();
}

};

void setup_leds() {
  pixels.begin();
  pixels.setBrightness(120);
  pixels.show();
}

void set_color(uint32_t c) {
  for (int i = 0; i < NUM_LEDS; i++)
    pixels.setPixelColor(i, c);
  pixels.show();
}
void set_color(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++)
    pixels.setPixelColor(i, pixels.Color(g, r, b));
  pixels.show();
}

void turn_off_leds() {
  for (int i = 0; i < NUM_LEDS; i++)
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  pixels.show();
}
