#define DEBUG

#include "pins.h"
#include "utility.h"
#include "radio.h"
#include "JoystickReader.h"

JoystickReader steeringWheel(PIN_H_LEFT, 200, 0);
JoystickReader gas(PIN_V_RIGHT, 2, -1);

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
  // delay(900);
}

void loop() {
  int wheel, g;
  cmd.wheel = steeringWheel.read();
 
  if (steeringWheel.read(&wheel)) {

    cmd.type = RF_COMMAND_SHIF;
    cmd.param = wheel;
    if (!radio.send(&cmd))
      Utility::print("Unable to send command");
  }

  if (gas.read(&g)) {
    cmd.type = RF_COMMAND_GAS;
    switch (g) {
      case 2:
        cmd.param = RF_GAS_PARAM_START;
        break;
      case 0:
        cmd.param = RF_GAS_PARAM_REVERSE;
        break;
      default:
        cmd.param = RF_GAS_PARAM_STOP;
        break;
    }

    if (!radio.send(&cmd))
      Utility::print("Unable to send command");
  }

  Utility::print("wheel is: ", wheel, " ;  gas is: ", g);
  delay(30);

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