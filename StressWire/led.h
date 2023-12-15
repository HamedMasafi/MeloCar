#include "pins.h"
#include <Adafruit_NeoPixel.h>

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

void set_led_color(uint32_t color, int count = NUM_LEDS, int start = 0) {
  pixels.fill(color, start, count);
  pixels.show();
}


void set_led_colors(uint32_t color, int count = NUM_LEDS, uint32_t color2 = color_black) {
  pixels.fill(color, 0, count);

  if (count < NUM_LEDS)
    pixels.fill(color2, count, NUM_LEDS - count);

  pixels.show();
}

void start_light_dance() {
  for (int i = 0; i <= 7; i++) {
    pixels.fill(color_black, 0, 7);
    pixels.fill(color_green, 0, i);
    pixels.show();
    delay(300);
  }
}