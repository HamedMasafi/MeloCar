#pragma once

#include <Arduino.h>

class Beep {

public:
  Beep(int port)
    : _port(port) {
    pinMode(port, OUTPUT);
  }

  void toggle(bool on) {
    if (on == _isOn)
      return;

    digitalWrite(_port, on ? HIGH : LOW);
    _isOn = on;
  }
private:
  int _port;
  bool _isOn{ false };
};