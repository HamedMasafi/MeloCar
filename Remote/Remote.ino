#define DEBUG

#include "pins.h"
#include "utility.h"
#include "radio.h"
#include "JoystickReader.h"

JoystickReader steeringWheel(PIN_H_LEFT, 200, 0);
JoystickReader gas(PIN_V_RIGHT, 3, -2);

Radio::Command cmd;
Radio radio(Radio::RadioType::Server);

void setup() {
  Serial.begin(9600);
  // while (!Serial) {}

  delay(900);

  radio.setup();

  pinMode(PIN_V_LEFT, INPUT);
  pinMode(PIN_H_LEFT, INPUT);
  pinMode(PIN_V_RIGHT, INPUT);
  pinMode(PIN_H_RIGHT, INPUT);
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
  int wheel, g;
  if (steeringWheel.read(&wheel)) {

    cmd.type = RF_COMMAND_SHIF;
    cmd.param = wheel;
    radio.send(&cmd);
      // Serial.println("Unable to send command");
  }

  /*if (gas.read(&g)) {

#ifdef DEBUG
    // Utility::print_impl("Gas: ", tmp);
#endif
    if (g > 0) {
      cmd.type = RF_COMMAND_START;
    } else if (g < 0) {
      cmd.type = RF_COMMAND_REVERSE;
    } else {
      cmd.type = RF_COMMAND_STOP;
    }
    
    radio.send(&cmd);
  }*/
  delay(600);

#ifdef DEBUG
    // Utility::print_impl("Wheel: ", wheel, " gas:", g);
#endif
  // Serial.print("x1=");
  // Serial.print(x);
  // Serial.print("\t\t");
  // Serial.print("y=");
  // Serial.print(y);
  // Serial.println();
  // delay(600);
}