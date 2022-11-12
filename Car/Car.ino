#include "common.h"
#include "pins.h"
#include "led.h"
#include "commands.h"
#include "rf.h"
#include "car.h"

Car car;

void setup() {
  Serial.begin(9600);

  Led::setup();
  Led::set_color(255, 0, 0);

  car.setup();
  Rf::setup();

  Led::turn_off();

  car.shift(90);
}

#define LED_SLEEP_TIME 150

void step_light() {
  static unsigned long lastLedTime = 0;
  unsigned long now = millis();
  if (now - lastLedTime > 100) {
    Led::step();
    lastLedTime = now;
  }
}

void step_read_command() {
  static rf_command cmd;
  if (Rf::read(&cmd)) {
    switch (cmd.type) {
      case RF_COMMAND_SHIF:
        car.shift(cmd.param1);
        break;

      case RF_COMMAND_START:
        car.forward();
        break;

      case RF_COMMAND_REVERSE:
        car.backward();
        break;

      case RF_COMMAND_STOP:
        car.stop();
        break;

      case RF_COMMAND_SET_LED_OFF:
        Led::turn_off();
        break;

      case RF_COMMAND_SET_LED_CHANGE_DANCER:
        Led::change_dancer();
        break;
    }

    cmd.type = 0;
    delay(100);
  }
}

void loop() {
  step_read_command();
  step_light();

  // rf_command cmd;
  // cmd.type  = 1;
  // Rf::send(&cmd);
  // delay(1000);

  /*car.shift(60);
  delay(1000);

  car.shift(90);
  delay(1000);

  car.shift(120);
  delay(1000);*/
}