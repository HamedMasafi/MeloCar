#include "Adafruit_NeoPixel.h"
#include "light_dancer.h"
#include "led.h"

// basic_light_dancer
basic_light_dancer::~basic_light_dancer() {}

void basic_light_dancer::step() {
}

// sequence_light_dancer
sequence_light_dancer::sequence_light_dancer()
  : _step(0) {
}

void sequence_light_dancer::step() {
  _step = (_step + 1) % size;
  Led::set_color(array[_step]);
}

// police_light_dancer
police_light_dancer::police_light_dancer() {
  array = new uint32_t[12]{
    Adafruit_NeoPixel::Color(0, 0, 150),
    Adafruit_NeoPixel::Color(0, 0, 0),
    Adafruit_NeoPixel::Color(0, 0, 150),
    Adafruit_NeoPixel::Color(0, 0, 0),
    Adafruit_NeoPixel::Color(0, 0, 150),
    Adafruit_NeoPixel::Color(0, 0, 0),

    Adafruit_NeoPixel::Color(150, 0, 0),
    Adafruit_NeoPixel::Color(0, 0, 0),
    Adafruit_NeoPixel::Color(150, 0, 0),
    Adafruit_NeoPixel::Color(0, 0, 0),
    Adafruit_NeoPixel::Color(150, 0, 0),
    Adafruit_NeoPixel::Color(0, 0, 0)
  };
  size = 12;
}

void blinker_dancer::step() {
  _step = (_step + 1) % NUM_LEDS;
  Led::set_just_one_led(Adafruit_NeoPixel::Color(255, 255, 255), _step);
}

void rainbow_dancer::step() {

  for (byte i = 0; i < NUM_LEDS; i++) {
    pixels->setPixelColor(i, Adafruit_NeoPixel::Color(random(40, 220), random(40, 220), random(40, 220)));
  }
}