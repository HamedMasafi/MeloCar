#include <Arduino.h>

#include "task.h"

void AbstractTask::setCallback(void *(cb)()) {
  _cb = cb;
}

Elapsed::Elapsed(int timeout)
  : _timeout{ timeout } {}

void Elapsed::check() {
  if (_startTime + _timeout <= millis())
    _cb();
}

void Elapsed::reset() {
  _startTime = millis();
}

CommandWithSpace::CommandWithSpace(int timeout)
  : _timeout{ timeout } {
  _lastExec = millis();
}

void CommandWithSpace::tryExec() {
  if (_lastExec + _timeout <= millis()) {
    _cb();
    _lastExec = millis();

    Serial.println("runed");
  } else {
    Serial.println("Not runned");
  }
}