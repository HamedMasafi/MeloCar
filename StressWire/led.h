#include "pins.h"
#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 8

Adafruit_NeoPixel pixels(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

auto color_red = Adafruit_NeoPixel::Color(255, 0, 0);
auto color_green = Adafruit_NeoPixel::Color(0, 255, 0);
auto color_gray = Adafruit_NeoPixel::Color(80, 80, 80);
auto color_white = Adafruit_NeoPixel::Color(255, 255, 255);
auto color_black = Adafruit_NeoPixel::Color(0, 0, 0);
auto color_yellow = Adafruit_NeoPixel::Color(255, 255, 0);

void led_clear() {
  pixels.fill(color_black, 0, NUM_LEDS);
}

void set_led_color(uint32_t color, uint8_t count = NUM_LEDS, int start = 0) {
  pixels.fill(color, start, count);
  pixels.show();
}


void set_led_colors(uint32_t color, uint8_t count = NUM_LEDS, uint32_t color2 = color_black) {
  pixels.fill(color, 0, count);

  if (count < NUM_LEDS)
    pixels.fill(color2, count, NUM_LEDS - count);

  pixels.show();
}

void start_light_dance(uint8_t from, uint8_t to, uint32_t color = color_green, unsigned long ms = 100) {

  if (to == from) {
    set_led_colors(color_green, from);
    return;
  }
  if (to > from)
    for (int i = from; i <= to; ++i) {
      set_led_colors(color, i);
      delay(ms);
    }
  else
    for (int i = from; i >= to; --i) {
      set_led_colors(color, i);
      delay(ms);
    }
}