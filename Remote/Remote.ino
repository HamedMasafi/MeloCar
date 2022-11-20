#include "pins.h"
#include "utility.h"
#include "radio.h"
#include "JoystickReader.h"

JoystickReader x1(PIN_X_1, 120, 70);
JoystickReader y1(PIN_Y_1, -1, 1);
// JoystickReader x2(PIN_X_2, 0, 100);
// JoystickReader y2(PIN_Y_2, 0, 100);

int x1_value, x2_value, y1_value, y2_value;
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

void loop() {
// auto x = analogRead(PIN_X_1);
// auto y = analogRead(PIN_Y_1);

  auto x = x1.read();
  auto y = y1.read();
  // if (x1.read(x1_value)) {
    cmd.type = RF_COMMAND_SHIF;
    cmd.param = x;//map(x1_value, 0, 1024, -100, 100);
    radio.send(&cmd);
    delay(90);
  // }

  // if (x2.read(x2_value)) {
    if (y > 0) {
      cmd.type = RF_COMMAND_START;
      radio.send(&cmd);
    } else if (y < 0) {
      cmd.type = RF_COMMAND_REVERSE;
      radio.send(&cmd);
    } else {
      cmd.type = RF_COMMAND_STOP;
      radio.send(&cmd);
    }
  // }
  delay(90);


  Serial.print("x1=");
  Serial.print(x);
  Serial.print("\t\t");
  Serial.print("y=");
  Serial.print(y);
  Serial.println();
  delay(600);
}