#include "utility.h"
#include <stdint.h>
#include "Arduino.h"
class JoystickReader {
private:
  uint8_t _pin;
  int _min, _max;
  int _r_min, _r_max;
  int _lastValue{ -1 };

public:
  JoystickReader(uint8_t pin, int min, int max);

  int read(int *buffer = nullptr);
  bool read(int *n, bool print_details = false);
};

inline JoystickReader::JoystickReader(uint8_t pin, int min, int max)
  : _pin(pin), _min(min), _max(max) {
  _r_min = min(_min, _max);
  _r_max = max(_min, _max);
}

inline int JoystickReader::read(int *buffer) {
  auto tmp = analogRead(_pin);
  auto mapped = map(tmp, 0, 1023, _min, _max);

  if (mapped < _r_min)
    mapped = _r_min;
  if (mapped > _r_max)
    mapped = _r_max;

  if (buffer)
    *buffer = tmp;
  return mapped;
}

inline bool JoystickReader::read(int *n, bool print_details) {
  int tmp;
  *n = read(&tmp);

  if (print_details)
    Utility::print("JoystickReader::read: ", tmp, "=>", *n);

  if (*n == _lastValue)
    return false;
  _lastValue = *n;
  return true;
}