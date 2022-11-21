#include "Arduino.h"
#pragma once

class JoystickReader {

public:
  JoystickReader(uint8_t pin);
  JoystickReader(uint8_t pin, int min, int max, int telo = 1);
  int read();
private:
  uint8_t _pin;
  int _min;
  int _max;
};

JoystickReader::JoystickReader(uint8_t pin)
  : _pin(pin) {
  pinMode(pin, INPUT);
  auto avg = analogRead(pin);
  _max = 2 * avg;
  _min = 0;
}

JoystickReader::JoystickReader(uint8_t pin, int min, int max, int telo)
  : _pin(pin), _min(min), _max(max) {
  pinMode(pin, INPUT);
}

int JoystickReader::read() {
  constexpr int max{ 666 };

  auto tmp = analogRead(_pin);
  auto ret = map(tmp, 0, max, _min, _max);

  // Serial.print("read(); port=");
  // Serial.print(_pin);
  // Serial.print(" // ");
  // Serial.print(tmp);
  // Serial.print("=>");
  // Serial.print(ret);
  // Serial.println();
  return ret;
}