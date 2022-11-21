#include <stdint.h>
#include "Arduino.h"
class JoystickReader
{
private:
    uint8_t _pin;
    int _min, _max;
    int _lastValue{-1};

public:
    JoystickReader(uint8_t pin, int min, int max);

    int read();
    bool read(int *n);
};

inline JoystickReader::JoystickReader(uint8_t pin, int min, int max)
    : _pin(pin)
    , _min(min)
    , _max(max)
{}

inline int JoystickReader::read()
{
    auto tmp = analogRead(_pin);
    auto mapped =  map(tmp, 0, 1023, _min, _max);
    Serial.print("JoystickReader::read");
    Serial.print(tmp);
    Serial.print("=>");
    Serial.println(mapped);
}

inline bool JoystickReader::read(int *n)
{
    auto tmp = analogRead(_pin);
    if (tmp == _lastValue)
        return false;

    *n = map(tmp, 0, 1023, _min, _max);

#ifdef DEBUG
    Serial.print("JoystickReader::read: ");
    Serial.print(tmp);
    Serial.print("=>");
    Serial.println(*n);
#endif

    return true;
}
