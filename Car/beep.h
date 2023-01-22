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

    //digitalWrite(_port, on ? HIGH : LOW);
    if (on)
      tone(_port, 1000);
    else
      noTone(_port);
    _isOn = on;
  }
private:
  int _port;
  bool _isOn{ false };
};