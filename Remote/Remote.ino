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
  Utility::print("Start");
}

void loop() {
  cmd.left_h = analogRead(PIN_H_LEFT);
  cmd.left_v = analogRead(PIN_V_LEFT);
  cmd.right_h = analogRead(PIN_H_RIGHT);
  cmd.right_v = analogRead(PIN_V_RIGHT);
  cmd.extra_1 = digitalRead(PIN_SW_LEFT);
  cmd.extra_2 = digitalRead(PIN_SW_RIGHT);
  Utility::print("Send command ",  radio.send(&cmd), cmd.left_h);
  delay(30);
}