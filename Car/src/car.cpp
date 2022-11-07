#include "car.h"
#include "pins.h"
#include <Servo.h>
#include <SPI.h>
#include <Arduino.h>


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
    servo.write(angle);
}