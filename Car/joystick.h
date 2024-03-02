template<int MIN = 500, int MAX = 524>
class Joystick {
  int _min;
  int _medium;
  int _max;
public:
  Joystick(int min, int medium, int max);
  void value(int d, char* sign = nullptr);
}

template<int MIN = 500, int MAX = 524>
Joystick<MIN, MAX>::Joystick(int min, int medium, int max)
  : _min{ min },
    _medium{ medium },
    _max{ max } {}

template<int MIN = 500, int MAX = 524>
Joystick<MIN, MAX>::value(int d, char* sign = nullptr) {
  if (n < MIN) {
    if (sign)
      *sign = -1;
    return map(n, 0, MIN, _min, _medium);
  }

  if (n > MAX) {
    if (sign)
      *sign = 1;
    return map(n, MAX, 1024, _medium, _max);
  }
  
  if (sign)
    *sign = 0;
  return _medium;
}