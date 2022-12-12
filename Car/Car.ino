#include "pins.h"
#include "led.h"
#include "radio.h"
#include "car.h"

Car car;
Radio radio(Radio::RadioType::Client);
// Radio::Command cmd;

void setup() {
  Serial.begin(9600);
  // while (!Serial) {}

  Led::setup();
  Led::set_color(255, 0, 0);

  car.setup();
  radio.setup();


  Led::turn_off();

  car.shift(90);

  // cmd.param = cmd.type = 0;
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

Radio::Command cmd;
void step_read_command() {

  if (radio.read(&cmd)) {
    Serial.print("Command read; type = ");
    Serial.print(cmd.type);
    Serial.print("  ; param = ");
    Serial.print(cmd.param);
    Serial.println();
    switch (cmd.type) {
      case RF_COMMAND_SHIF:
        car.shift(map(cmd.param, 0, 200, 120, 60));
        break;

      // case RF_COMMAND_START:
      //   car.forward();
      //   break;

      // case RF_COMMAND_REVERSE:
      //   car.backward();
      //   break;

      // case RF_COMMAND_STOP:
      //   car.stop();
      //   break;

      // case RF_COMMAND_SET_LED_OFF:
      //   Led::turn_off();
      //   break;
        
      // case RF_COMMAND_SET_LED_ON:
      //   Led::turn_on();
      //   break;

      // case RF_COMMAND_SET_LED_CHANGE_DANCER:
      //   Led::change_dancer();
      //   break;
    }
    cmd.type = cmd.param = 0;
  } else {
    // Serial.println("No command");
  }
}

void loop() {
  step_read_command();
 // step_light();
 delay(30);
}