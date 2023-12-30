#include "led.h"
#include "light_dancer.h"

namespace Led {
Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

basic_light_dancer *_dancer{ nullptr };
auto color_red = Adafruit_NeoPixel::Color(255, 0, 0);
auto color_green = Adafruit_NeoPixel::Color(0, 255, 0);
auto color_gray = Adafruit_NeoPixel::Color(80, 80, 80);
auto color_white = Adafruit_NeoPixel::Color(255, 255, 255);
auto color_black = Adafruit_NeoPixel::Color(0, 0, 0);
auto color_yellow = Adafruit_NeoPixel::Color(255, 255, 0);

void setup() {
  _dancer = new police_light_dancer;
  pixels.begin();
  pixels.setBrightness(120);
  pixels.show();
  _dancer->pixels = &pixels;
}
void set_color(uint8_t r, uint8_t g, uint8_t b) {
  set_color(Adafruit_NeoPixel::Color(r, g, b));
}
void set_color(uint8_t r, uint8_t g, uint8_t b, int n) {
  pixels.setPixelColor(n, r, g, b);
  pixels.show();
}

void set_color(uint32_t color) {
  // if (!color) {
  //   pixels.clear();
  //   return;
  // }
  pixels.fill(color, 0, 7);
  pixels.show();
}

void set_led_color(uint32_t color, int n) {
  pixels.setPixelColor(n, color);
  pixels.show();
}

void turn_off() {
  set_color(0, 0, 0);
}

void turn_on() {
}

void step() {
  _dancer->step();
}

void change_dancer() {
  static int index = 0;
  const int max = 1;

  index = (index + 1) % max;

  if (_dancer)
    delete _dancer;

  switch (index) {
    case 1:
      _dancer = new police_light_dancer;

      break;

    default:
      break;
  }

  _dancer->pixels = &pixels;
}

};