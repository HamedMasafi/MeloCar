#ifndef MOTOR_H
#define MOTOR_H

#include <Servo.h>

class Car
{
    Servo servo;

public:
    void setup();
    void forward();
    void stop();
    void backward();
    void shift(int angle);
};

#endif // MOTOR_H