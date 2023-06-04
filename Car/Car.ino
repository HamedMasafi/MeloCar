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

#define LED_SLEEP_TIME 150

constexpr int accel_min{ 10 };
constexpr int accel_max{ 80 };

void step_light() {
  static unsigned long lastLedTime = 0;
  unsigned long now = millis();
  if (now - lastLedTime > 100) {
    Led::step();
    lastLedTime = now;
  }
}

void step_read_command() {
  if (radio.read(&cmd)) {
    int wheel = map(cmd.left_h, 0, 1023, 60, 120);
    Utility::print("Data from nrf is: lh= ", cmd.right_v, " value=", cmd.left_h);

    // wheel
    car.shift(wheel);

    // horn
    beep.toggle(cmd.left_v < 10);

    constexpr int gas_min{ 650 };
    constexpr int gas_max{ 800 };
    // engine
    if (cmd.right_v > gas_max) {
      auto accel = map(cmd.right_v, gas_max, 1023, accel_min, accel_max);
      car.setAccel(accel);
      car.backward();
      delay(30);
      // Utility::print("Backward: ", cmd.right_v, "Accel: ", accel);
    } else if (cmd.right_v < gas_min) {
      auto accel = map(cmd.right_v, gas_min, 0, accel_min, accel_max);
      car.setAccel(accel);
      car.forward();
      delay(30);
      // Utility::print("Forward:  ", cmd.right_v, "Accel: ", accel);
    } else {
      car.stop();
      delay(30);
      // Utility::print("Stop:     ", cmd.right_v);
    }

  } else {
    //  Utility::print("No command");
  }
}

void test()
{
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
  Led::set_color(255, 0, 0);

  car.setup();
  radio.setup();


  delay(200);
  car.shift(90);
  // cmd.param = cmd.type = 0;

  Utility::print("Start...");
  Led::turn_off();
}

int n = 0;
void loop() {
  step_read_command();
  step_light();
  n++;
  if (n > 3) {
    car.stepAccel();
    n = 0;
  }
}