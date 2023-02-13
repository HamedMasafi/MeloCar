#ifndef MOTOR_H
#define MOTOR_H

#include <Servo.h>
#include <SPI.h>
#include <Arduino.h>

#include "utility.h"
#include "pins.h"

class Car {
  Servo servo;
  int _lastAngle{ -1 };
  int _realAccel{0};
  int _goalAccel{0};

public:
  void setup();
  void forward();
  void stop();
  void backward();
  void shift(int angle);
  void setAccel(int accel);
  bool stepAccel();
};

inline void Car::setup() {
  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);
  pinMode(PIN_SERVO, OUTPUT);

  servo.attach(PIN_SERVO);
}

inline void Car::forward() {
  digitalWrite(PIN_MOTOR_1, LOW);
  delay(15);
  digitalWrite(PIN_MOTOR_2, HIGH);
  delay(15);
}

inline void Car::stop() {
  digitalWrite(PIN_MOTOR_1, LOW);
  delay(15);
  digitalWrite(PIN_MOTOR_2, LOW);
  delay(15);
}

inline void Car::backward() {
  digitalWrite(PIN_MOTOR_2, LOW);
  delay(15);
  digitalWrite(PIN_MOTOR_1, HIGH);
  delay(15);
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
  _lastAngle = angle;
}

inline void Car::setAccel(int accel)
{
  _goalAccel = accel;
}


inline bool Car::stepAccel()
{
  if (_goalAccel > _realAccel) {
    _realAccel++;
    analogWrite(PIN_ACCEL, _realAccel);
    return true;
  }
  
  if (_goalAccel < _realAccel) {
    _realAccel--;
    analogWrite(PIN_ACCEL, _realAccel);
    return true;
  }

  return false;
}

#endif  // MOTOR_H