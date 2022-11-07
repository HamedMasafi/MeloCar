#include "led.h"
#include "light_dancer.h"

namespace Led {
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

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