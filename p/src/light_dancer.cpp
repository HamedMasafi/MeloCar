#include "light_dancer.h"
#include "led.h"

basic_light_dancer::~basic_light_dancer()
{}

void basic_light_dancer::step()
{
}

void police_light_dancer::step()
{
    if (_step)
    {
        Led::set_color(0, 0, 150);
        _step = 0;
    }
    else
    {
        Led::set_color(150, 0, 0);
        _step = 1;
    }
}

void stepper_dancer::step()
{
    _step = (_step + 1) % NUM_LEDS; 
    for (byte i = 0; i < NUM_LEDS; i++) {
        pixels->setPixelColor(i, i == _step ? Adafruit_NeoPixel::Color(255, 255, 255) : Adafruit_NeoPixel::Color(0, 0, 0));
    }
}