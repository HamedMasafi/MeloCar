#define DEBUG

#include "pins.h"
#include "utility.h"
#include "radio.h"

Radio::Command cmd;
Radio radio(Radio::RadioType::Server);

int cmd_left_h{ 0 };
int cmd_left_v{ 0 };
int cmd_right_h{ 0 };
int cmd_right_v{ 0 };
bool cmd_sw_left{ 0 };
bool cmd_sw_right{ 0 };

void setup() {
  Serial.begin(9600);
  // while (!Serial) {}

  delay(100);

  radio.setup();

  pinMode(PIN_V_LEFT, INPUT);
  pinMode(PIN_H_LEFT, INPUT);
  pinMode(PIN_V_RIGHT, INPUT);
  pinMode(PIN_H_RIGHT, INPUT);
  pinMode(PIN_SW_RIGHT, INPUT_PULLUP);
  pinMode(PIN_SW_LEFT, INPUT_PULLUP);
  Serial.println("Start");
}

void loop() {
  cmd_left_h = analogRead(PIN_H_LEFT);
  cmd_left_v = analogRead(PIN_V_LEFT);
  cmd_right_h = analogRead(PIN_H_RIGHT);
  cmd_right_v = analogRead(PIN_V_RIGHT);
  cmd_sw_left = !digitalRead(PIN_SW_LEFT);
  cmd_sw_right = !digitalRead(PIN_SW_RIGHT);

  if (cmd_left_h != cmd.left_h || cmd_left_v != cmd.left_v || cmd_right_h != cmd.right_h || cmd_right_v != cmd.right_v || cmd_sw_left != cmd.sw_left || cmd_sw_right != cmd.sw_right) {
    cmd.left_h = cmd_left_h;
    cmd.left_v = cmd_left_v;
    cmd.right_h = cmd_right_h;
    cmd.right_v = cmd_right_v;
    cmd.sw_left = cmd_sw_left;
    cmd.sw_right = cmd_sw_right;

    auto r = radio.send(&cmd);
    // if (!r)
    // Utility::print("Unable to send command");

    Utility::print("Send command:", FixedSize(r, 6),
                   " ; left h:", FixedSize(cmd.left_h, 5),
                   " ; left v:", FixedSize(cmd.left_v, 5),
                   " ; right h:", FixedSize(cmd.right_h, 5),
                   " ; right v:", FixedSize(cmd.right_v, 5),
                   " ; left:", cmd.sw_left,
                   " ; right:", cmd.sw_right);
    // delay(50);
  }
}