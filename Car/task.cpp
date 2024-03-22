#include <Arduino.h>

#include "task.h"

Elapsed::Elapsed(int timeout)
  : _timeout{ timeout } {}

void Elapsed::setCallback(void *(cb)()) {
  _cb = cb;
}

void Elapsed::check() {
  if (_startTime + _timeout <= millis())
    _cb();
}

void Elapsed::reset() {
  _startTime = millis();
}