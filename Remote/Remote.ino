#include "pins.h"
#include "utility.h"
#include "radio.h"
#include "JoystickReader.h"

JoystickReader steeringWheel(PIN_H_LEFT, 0, 120);
JoystickReader gas(PIN_V_RIGHT, -1, 1);

Radio::Command cmd;
Radio radio(Radio::RadioType::Server);

void setup() {
  Serial.begin(9600);
  while (!Serial) {}

  delay(900);

  radio.setup();

  pinMode(PIN_X_1, INPUT);
  pinMode(PIN_Y_1, INPUT);
}

#define READ(x) \
  Serial.print("Read from:"); \
  Serial.print(x); \
  Serial.print("("); \
  Serial.print(#x); \
  Serial.print(")="); \
  Serial.println(analogRead(x));

#define PRINT(x) \
  Serial.print(#x); \
  Serial.print("="); \
  Serial.println(x);

#define PRINT_X(x, title) \
  Serial.print(title); \
  Serial.print("="); \
  Serial.println(x);

void loop() {
  // READ(PIN_V_LEFT);
  // READ(PIN_H_LEFT);
  // READ(PIN_V_RIGHT);
  // READ(PIN_H_RIGHT);
  // delay(1000);
  // return;

  int tmp;
  if (steeringWheel.read(&tmp)) {
    PRINT_X(tmp, steeringWheel);
    cmd.type = RF_COMMAND_SHIF;
    cmd.param = x;  //map(x1_value, 0, 1024, -100, 100);
    radio.send(&cmd);
    delay(90);
  }

  if (gas.read(&tmp)) {
    PRINT_X(tmp, gas);
    if (tmp > 0) {
      cmd.type = RF_COMMAND_START;
      radio.send(&cmd);
    } else if (tmp < 0) {
      cmd.type = RF_COMMAND_REVERSE;
      radio.send(&cmd);
    } else {
      cmd.type = RF_COMMAND_STOP;
      radio.send(&cmd);
    }
    delay(90);
  }


  // Serial.print("x1=");
  // Serial.print(x);
  // Serial.print("\t\t");
  // Serial.print("y=");
  // Serial.print(y);
  // Serial.println();
  // delay(600);
}