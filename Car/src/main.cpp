#include <Servo.h>

#include "common.h"
#include "pins.h"
#include "led.h"
#include "commands.h"
#include "rf.h"

#define MOTOR_START 0
#define MOTOR_STOP 2
#define MOTOR_REVERSE 1

Servo servo;

void shift(int angle)
{
  servo.write(angle);
  delay(15);
}

void motor_command(int command)
{
  switch (command)
  {
  case MOTOR_START:
    digitalWrite(PIN_MOTOR_1, LOW);
    digitalWrite(PIN_MOTOR_2, HIGH);
    break;
  case MOTOR_STOP:
    digitalWrite(PIN_MOTOR_1, LOW);
    digitalWrite(PIN_MOTOR_2, LOW);
    break;
  case MOTOR_REVERSE:
    digitalWrite(PIN_MOTOR_1, HIGH);
    digitalWrite(PIN_MOTOR_2, LOW);
    break;
  }
}

void setup()
{
  Led::setup();
  Led::set_color(255, 0, 0);

  servo.attach(PIN_SERVO);
  shift(90);

  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);
  pinMode(PIN_SERVO, OUTPUT);

  Rf::setup();

  Serial.begin(9600);

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
    // process cmd

    switch (cmd.type)
    {
    case RF_COMMAND_SHIF:
      shift(cmd.param1);
      break;

    case RF_COMMAND_START:
      motor_command(MOTOR_START);
      break;

    case RF_COMMAND_REVERSE:
      motor_command(MOTOR_REVERSE);
      break;

    case RF_COMMAND_STOP:
      motor_command(MOTOR_STOP);
      break;

    case RF_COMMAND_SET_LED_OFF:
      Led::turn_off();
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