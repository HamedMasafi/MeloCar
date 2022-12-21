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
}

void loop() {
  int wheel, g;
  if (steeringWheel.read(&wheel)) {

    cmd.type = RF_COMMAND_SHIF;
    cmd.param = wheel;
    radio.send(&cmd);
    // Serial.println("Unable to send command");
  }

  if (gas.read(&g)) {
    Utility::print("gas is", g);
    switch (g) {
      case 2:
        cmd.type = RF_COMMAND_START;
        break;
      case 0:
        cmd.type = RF_COMMAND_REVERSE;
        break;
      default:
        cmd.type = RF_COMMAND_STOP;
        break;
    }

    radio.send(&cmd);
  }

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