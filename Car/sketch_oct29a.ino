#include <Servo.h>

Servo servo;
int servoPin = 9;

#define PIN_MOTOR_1 8
#define PIN_MOTOR_2 7
#define MOTOR_START 0
#define MOTOR_STOP 2
#define MOTOR_REVERSE 1

void shift(int angle) {
  servo.write(angle);
  delay(15);
}

void motor_command(int command) {
  switch (command) {
    case MOTOR_START:
      digitalWrite(PIN_MOTOR_1, HIGH);
      digitalWrite(PIN_MOTOR_2, LOW);
      break;
    case MOTOR_STOP:
      digitalWrite(PIN_MOTOR_1, LOW);
      digitalWrite(PIN_MOTOR_2, LOW);
      break;
    case MOTOR_REVERSE:
      digitalWrite(PIN_MOTOR_1, LOW);
      digitalWrite(PIN_MOTOR_2, HIGH);
      break;
  }
}

void setup() {
  servo.attach(servoPin);
  shift(0);
  
  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
    int angle;
    for(angle = 0; angle < 180; angle++) {
        shift(angle);
        delay(15);
    }
     
    motor_command(MOTOR_START);
    // now scan back from 180 to 0 degrees
    for(angle = 180; angle > 0; angle--) {
        shift(angle);
        delay(15);
    }
    motor_command(MOTOR_STOP);
}
