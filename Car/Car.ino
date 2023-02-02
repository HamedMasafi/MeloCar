#include "pins.h"
#include "led.h"
#include "radio.h"
#include "car.h"
#include "utility.h"
#include "beep.h"

Car car;
Radio radio(Radio::RadioType::Client);
Radio::Command cmd;
Beep beep{PIN_BEEP};

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
  if (radio.read(&cmd)) {
    int wheel = map(cmd.left_h, 0, 1023, 60, 120);
 
    
    // wheel
    car.shift(wheel);

    // horn
    beep.toggle(cmd.left_v < 10);

    // engine
 
      car.setAccel(accel);
      car.backward();
 
      car.setAccel(accel);
      car.forward();
    } else {
      car.stop();
 

    /*
    switch (cmd.type) {
      case RF_COMMAND_SHIF:
        car.shift(map(cmd.param, 0, 200, 120, 60));
        break;

      case RF_COMMAND_GAS:
        if (cmd.param == RF_GAS_PARAM_START)
          car.forward();
        else if (cmd.param == RF_GAS_PARAM_REVERSE)
          car.backward();
        else
          car.stop();
        break;

      case RF_COMMAND_SET_LED_OFF:
        Led::turn_off();
        break;

      case RF_COMMAND_SET_LED_ON:
        Led::turn_on();
        break;

      case RF_COMMAND_SET_LED_CHANGE_DANCER:
        Led::change_dancer();
        break;
    }

    cmd.type = cmd.param = 0;
    */
  } else {
    //  Utility::print("No command");
  }
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

void loop() {
  step_read_command();
  step_light();
  car.stepAccel();
  delay(15);