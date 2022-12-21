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

  int read();
  bool read(int *n, bool print_details = false);
};

inline JoystickReader::JoystickReader(uint8_t pin, int min, int max)
  : _pin(pin), _min(min), _max(max) {
  _r_min = min(_min, _max);
  _r_max = max(_min, _max);
}

// inline int JoystickReader::read()
// {
//     auto tmp = analogRead(_pin);
//     auto mapped =  map(tmp, 0, 1023, _min, _max);
//     Serial.print("JoystickReader::read");
//     Serial.print(tmp);
//     Serial.print("=>");
//     Serial.println(mapped);
// }

inline bool JoystickReader::read(int *n, bool print_details) {
  auto tmp = analogRead(_pin);

  *n = map(tmp, 0, 1023, _min, _max);

  if (*n < _r_min)
    *n = _r_min;
  if (*n > _r_max)
    *n = _r_max;

  if (print_details)
    Utility::print("JoystickReader::read: ", tmp, "=>", *n);

  if (*n == _lastValue)
    return false;
  _lastValue = *n;
  return true;
}