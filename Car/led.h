#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 7

Adafruit_NeoPixel pixels(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
// Thread thread_led = Thread();

namespace Led {
void setup() {
  pixels.begin();
  pixels.setBrightness(120);
  pixels.show();
}
void set_color(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++)
    pixels.setPixelColor(i, pixels.Color(g, r, b));
  pixels.show();
}
void turn_off() {
  set_color(0, 0, 0);
}
};

void setup_leds() {
  pixels.begin();
  pixels.setBrightness(120);
  pixels.show();

  // thread_led.setInterval(100);
  // thread_led.onRun(dancerCallback)
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

class basic_light_dancer {
public:
  virtual void step();
};

class police_light_dancer : public basic_light_dancer {
  uint8_t _step;


public:
  void step() override {
    if (_step) {
      pixels.Color(0, 0, 150);
      _step = 0;
    } else {
      pixels.Color(150, 0, 0);
      _step = 1;
    }
  }
};

basic_light_dancer *_dancer = new police_light_dancer;
void dancerCallback() {
  _dancer->step();
}