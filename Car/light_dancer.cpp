#include "Adafruit_NeoPixel.h"
#include "light_dancer.h"
#include "led.h"

basic_light_dancer::~basic_light_dancer()
{}

void basic_light_dancer::step()
{
}

sequence_light_dancer::sequence_light_dancer() : _step(0)
{

}

void sequence_light_dancer::step()
{
  _step = (_step + 1) % size;
  Led::set_color(array[_step]);
  Serial.println("step");
}

police_light_dancer::police_light_dancer()
{
  array = new uint32_t[4] {
    Adafruit_NeoPixel::Color(0, 0, 150),
    Adafruit_NeoPixel::Color(0, 0, 0),
    Adafruit_NeoPixel::Color(150, 0, 0), 
    Adafruit_NeoPixel::Color(0, 0, 0)
  };
  size = 4;
}

void stepper_dancer::step()
{
    _step = (_step + 1) % NUM_LEDS; 
    for (byte i = 0; i < NUM_LEDS; i++) {
        pixels->setPixelColor(i, i == _step ? Adafruit_NeoPixel::Color(255, 255, 255) : Adafruit_NeoPixel::Color(0, 0, 0));
    }
}