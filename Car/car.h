#pragma once

// #include <Servo.h>
#include <SPI.h>
#include <Arduino.h>
#include <Servo.h> 

#include "utility.h"
#include "pins.h"

#define ACCEL_MIN 60
#define ACCEL_MAX 220

class Car {
public:
  enum class Status {
    Stopped,
    Forward,
    Backward
  };
  void setup();
  void forward();
  void stop();
  void backward();
  void shift(int angle);
  void setAccel(int accel);
  bool stepAccel();
  void setStatus(Status status);

private:
  Servo servo;
  Status _status{ Status::Stopped };
  int _lastAngle{ -1 };
  int _realAccel{ 0 };
  int _goalAccel{ 0 };
};

inline void Car::setup() {
  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);
  pinMode(PIN_SERVO, OUTPUT);
  pinMode(PIN_ACCEL, OUTPUT);

  servo.attach(PIN_SERVO);

  analogWrite(PIN_ACCEL, 60);
}

inline void Car::forward() {
  setStatus(Status::Forward);
}

inline void Car::stop() {
  setStatus(Status::Stopped);
}

inline void Car::backward() {
  setStatus(Status::Backward);
}

inline void Car::setStatus(Status status) {
  if (status == _status)
    return;

  Utility::print("Set status to: ", (int)status);
  _realAccel = _goalAccel = ACCEL_MIN;
  // analogWrite(PIN_ACCEL, _realAccel);
  switch (status) {
    case Car::Status::Stopped:
      digitalWrite(PIN_MOTOR_1, LOW);
      digitalWrite(PIN_MOTOR_2, LOW);
      delay(15);
      break;
    case Car::Status::Forward:
      digitalWrite(PIN_MOTOR_1, LOW);
      delay(15);
      digitalWrite(PIN_MOTOR_2, HIGH);
      delay(15);
      break;
    case Car::Status::Backward:
      digitalWrite(PIN_MOTOR_1, HIGH);
      delay(15);
      digitalWrite(PIN_MOTOR_2, LOW);
      delay(15);
      break;
  }
  delay(90);
  _status = status;
}

inline void Car::shift(int angle) {
  if (angle == _lastAngle)
    return;
  // Utility::bound(60, angle, 120);
  // if (angle < 50)
  //   angle = 50;
  // else if (angle > 129)
  //   angle = 120;
  Utility::print("Shift to ", angle);
  servo.write(angle);
  delay(110);
  _lastAngle = angle;
}

inline void Car::setAccel(int accel) {
  _goalAccel = accel;
  analogWrite(PIN_ACCEL, 200);
}


inline bool Car::stepAccel() {
  return ;
  constexpr int accel_step{ 3 };

  if (_goalAccel - _realAccel > accel_step + 1) {
    _realAccel += accel_step;
    analogWrite(PIN_ACCEL, _realAccel);
    Utility::print("accel++", _realAccel, "=>", _goalAccel);
    return true;
  }

  if (_goalAccel - _realAccel < -accel_step - 1) {
    _realAccel -= accel_step;
    analogWrite(PIN_ACCEL, _realAccel);
    Utility::print("accel--", _realAccel, "=>", _goalAccel);
    return true;
  }

  return false;
}
