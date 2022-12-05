#include "car.h"
#include "pins.h"
#include <Servo.h>
#include <SPI.h>
#include <Arduino.h>
#include "utility.h"

void Car::setup()
{
    pinMode(PIN_MOTOR_1, OUTPUT);
    pinMode(PIN_MOTOR_2, OUTPUT);
    pinMode(PIN_SERVO, OUTPUT);

    servo.attach(PIN_SERVO);
    shift(90);
}

void Car::forward() 
{
    digitalWrite(PIN_MOTOR_1, LOW);
    digitalWrite(PIN_MOTOR_2, HIGH);
}

void Car::stop()
{
    digitalWrite(PIN_MOTOR_1, LOW);
    digitalWrite(PIN_MOTOR_2, LOW);
}

void Car::backward() 
{
    digitalWrite(PIN_MOTOR_1, HIGH);
    digitalWrite(PIN_MOTOR_2, LOW);
}

void Car::shift(int angle)
{
    if (angle == _lastAngle)
      return;
    // Utility::bound(60, angle, 120);
    // if (angle < 70)
    //   angle = 70;
    // else if (angle > 129)
    //   angle = 120;
    Serial.print("Shift to");
    Serial.print(angle);
    Serial.println();
    servo.write(angle);
    _lastAngle = angle;
}