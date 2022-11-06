#ifndef LIGHT_DANCER_H
#define LIGHT_DANCER_H
#include <Adafruit_NeoPixel.h>



class basic_light_dancer {
public:
  Adafruit_NeoPixel *pixels;
  virtual void step();
};

class police_light_dancer : public basic_light_dancer {
  uint8_t _step;
public:
  void step() override {
    if (_step) {
      pixels->Color(0, 0, 150);
      _step = 0;
    } else {
      pixels->Color(150, 0, 0);
      _step = 1;
    }
  }
};

#endif  // LIGHT_DANCER_H