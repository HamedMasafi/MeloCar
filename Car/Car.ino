#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include <Adafruit_NeoPixel.h>

#include "common.h"
#include "pins.h"
#include "led.h"
#include "commands.h"
#include "rf.h"

#define MOTOR_START 0
#define MOTOR_STOP 2
#define MOTOR_REVERSE 1

Servo servo;

unsigned long lastRecvTime = 0;
void recvData() {
  MyData data;
  if (radio.available())  //Check whether there are bytes available to be read
  {
    radio.read(&data, sizeof(MyData));  //Read payload data from the RX FIFO buffer(s).
    lastRecvTime = millis();            //here we receive the data
  }
}

void shift(int angle) {
  servo.write(angle);
  delay(15);
}

void motor_command(int command) {
  switch (command) {
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

void setup() {
  Led::setup();
  set_color(255, 255, 255);

  servo.attach(PIN_SERVO);
  shift(90);

  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);

  Rf::setup();

  Serial.begin(9600);

  shift(90);
  turn_off_leds();
}


#define LED_SLEEP_TIME 150
void loop() {
  Serial.println("Starting");


  for (int i = 0; i < 3; i++) {
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
  delay(2000);

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