#include "Arduino.h"
class JoystickReader
{
private:
    int _pin, _min, _max;
    int _lastValue{-1};

public:
    JoystickReader(int pin, int min, int max);

    int read();
    bool read(int *n);
};

inline JoystickReader::JoystickReader(int pin, int min, int max)
    : _pin(pin)
    , _min(min)
    , _max(max)
{}

inline int JoystickReader::read()
{
    auto tmp = analogRead(_pin);
    return map(tmp, 0, 1023, _min, _max);
}

inline bool JoystickReader::read(int *n)
{
    auto tmp = analogRead(_pin);
    if (tmp == _lastValue)
        return false;

    n = map(tmp, 0, 1023, _min, _max);
    return true;
}
