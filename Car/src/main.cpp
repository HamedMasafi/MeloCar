#include "common.h"
#include "pins.h"
#include "led.h"
#include "commands.h"
#include "rf.h"
#include "car.h"

#define MOTOR_START 0
#define MOTOR_STOP 2
#define MOTOR_REVERSE 1

Car car;

void setup()
{
  Serial.begin(9600);

  Led::setup();
  Led::set_color(255, 0, 0);

  car.setup();
  Rf::setup();

  Led::turn_off();
}

#define LED_SLEEP_TIME 150

void step_light()
{
  static unsigned long lastLedTime = 0;
  unsigned long now = millis();
  if (now - lastLedTime > 100)
  {
    Led::step();
    lastLedTime = now;
  }
}

void step_read_command()
{
  static rf_command cmd;
  if (Rf::read(&cmd))
  {
    switch (cmd.type)
    {
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

void loop()
{
  Serial.println("Starting");

  step_read_command();
  step_light();

  /*for (int i = 0; i < 3; i++) {
    Led::set_color(150, 0, 0);
    delay(LED_SLEEP_TIME);

    Led::turn_off();
    delay(LED_SLEEP_TIME);
  }

  for (int i = 0; i < 3; i++) {
    Led::set_color(0, 0, 150);
    delay(LED_SLEEP_TIME);

    Led::turn_off();
    delay(LED_SLEEP_TIME);
  }

  motor_command(MOTOR_START);
  delay(2000);*/

  /*
  motor_command(MOTOR_STOP);
  delay(500);

  motor_command(MOTOR_REVERSE);
  delay(2000);

  motor_command(MOTOR_STOP);
  delay(500);*/
  /*  shift(0);
  motor_command(MOTOR_START);
  delay(1000);

  Serial.println("Stopping");
  shift(90);
  motor_command(MOTOR_STOP);
  delay(1000);

  Serial.println("Reversing");
  shift(180);
  motor_command(MOTOR_REVERSE);
  delay(1000);
*/
}