#include "pins.h"
#include "led.h"
#include "radio.h"
#include "car.h"
#include "utility.h"
#include "beep.h"

Car car;
Radio radio(Radio::RadioType::Client);
Radio::Command cmd;
Beep beep{ PIN_BEEP };
int invalidCmdCount{ 0 };

#define LED_SLEEP_TIME 150

constexpr int accel_min{ 60 };
constexpr int accel_max{ 255 };

void step_light() {
  static unsigned long lastLedTime = 0;
  unsigned long now = millis();
  if (now - lastLedTime > 100) {
    Led::step();
    lastLedTime = now;
  }
}

void run_command() {
  int wheel = map(cmd.left_h, 1023, 0, 70, 120);
  Utility::print("Data from nrf is: lh= ", cmd.left_h, " value=", cmd.right_v);

  // wheel
  car.shift(wheel);
  // horn
  beep.toggle(cmd.left_v < 10);

  constexpr int gas_min{ 500 };
  constexpr int gas_max{ 560 };
  // engine
  if (cmd.right_v > gas_max) {
    auto accel = map(cmd.right_v, gas_max, 1023, accel_min, accel_max);
    // Utility::print("Accel is=", accel);
    car.setAccel(accel);
    car.forward();
  } else if (cmd.right_v < gas_min) {
    auto accel = map(cmd.right_v, gas_min, 0, accel_min, accel_max);
    // Utility::print("Accel is=", accel);
    car.setAccel(accel);
    car.backward();
  } else {
    car.stop();
  }
  delay(30);
}

void step_read_command_from_serial() {
  auto line = Serial.readStringUntil('\n');

  if (!line.length()) {
    delay(200);
    return;
  }

  auto space_index = line.indexOf(' ');

  cmd.left_h = line.substring(0, space_index).toInt();
  cmd.right_v = line.substring(space_index + 1, line.length()).toInt();
  Utility::print("Data from serial; lh=", cmd.left_h, " rv=", cmd.right_v);

  run_command();
}

void step_read_command() {
  if (radio.read(&cmd)) {
    run_command();
    invalidCmdCount = 0;
  } else {
    invalidCmdCount++;

    if (invalidCmdCount >= 40000) {
      car.stop();
      invalidCmdCount = 0;
    }
    // if (invalidCmdCount % 30 == 0) 
    // Utility::print("Invalid ", invalidCmdCount, " command(s)");
  }
}

void test() {
  car.setAccel(200);
  car.forward();
  delay(200);
  car.backward();
  delay(200);
  car.stop();
}
void setup() {
  Serial.begin(9600);
  Utility::print("Starting");
  Led::setup();
  Led::set_color(255, 0, 0, 0);

  car.setup();
  Led::set_color(255, 0, 0, 1);

  radio.setup();
  Led::set_color(255, 0, 0, 2);
  delay(200);

  car.shift(90);
  Led::set_color(255, 0, 0, 3);

  Utility::print("Start...");
  Led::set_color(255, 0, 0, 4);

  Led::turn_off();
}

int n = 0;
void loop() {
  // Utility::print("Read command");
  step_read_command();
  // step_read_command_from_serial();

  // Utility::print("Done");
  // step_light();
  // n++;
  // if (n > 3) {
  //   car.stepAccel();
  //   n = 0;
  // }
}