#ifndef LIGHT_DANCER_H
#define LIGHT_DANCER_H

#include "simulate.h"
#include <Adafruit_NeoPixel.h>

class basic_light_dancer
{
public:
  Adafruit_NeoPixel *pixels;

  virtual ~basic_light_dancer();
  virtual void step();
};

class police_light_dancer : public basic_light_dancer
{
  uint8_t _step;

public:
  void step() override;
};

class stepper_dancer : public basic_light_dancer
{
  uint8_t _step;

public:
  void step() override;
};


#endif // LIGHT_DANCER_H
