#define DEBUG

#include "pins.h"
#include "utility.h"
#include "radio.h"

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
  pinMode(PIN_SW_RIGHT, INPUT_PULLUP);
  pinMode(PIN_SW_LEFT, INPUT_PULLUP);
  Utility::print("Start");
}

void loop() {
  cmd.left_h = analogRead(PIN_H_LEFT);
  cmd.left_v = analogRead(PIN_V_LEFT);
  cmd.right_h = analogRead(PIN_H_RIGHT);
  cmd.right_v = analogRead(PIN_V_RIGHT);
  cmd.sw_left = !digitalRead(PIN_SW_LEFT);
  cmd.sw_right = !digitalRead(PIN_SW_RIGHT);
  auto r = radio.send(&cmd);
  // if (!r)
    // Utility::print("Unable to send command");

  Utility::print("Send command: " , r,
                 " ; left h:", cmd.left_h,
                 " ; left v:", cmd.left_v,
                 " ; right h:", cmd.right_h,
                 " ; right v:", cmd.right_v,
                 " ; left:", cmd.sw_left,
                 " ; right:", cmd.sw_right);
  delay(1000);
}