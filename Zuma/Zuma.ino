#include <Arduino.h>
#include "pins.h"
#include "utility.h"


enum class RemoteKey {
  None,
  A,
  B,
  C,
  D
};

enum class MotorCommand {
  Stop,
  Walk,
  Bark
};

MotorCommand last_motor_command{ MotorCommand::Stop };
bool is_active{ true };

RemoteKey get_remote() {
  // auto nn = digitalRead(PIN_REMOTE_A);
  // Utility::print("pin:", nn);

  if (digitalRead(PIN_REMOTE_A) == HIGH)
    return RemoteKey::A;
  if (digitalRead(PIN_REMOTE_B) == HIGH)
    return RemoteKey::B;
  if (digitalRead(PIN_REMOTE_C) == HIGH)
    return RemoteKey::C;
  if (digitalRead(PIN_REMOTE_D) == HIGH)
    return RemoteKey::D;

  return RemoteKey::None;
}

void set_motor_status(MotorCommand cmd) {
  switch (cmd) {
    case MotorCommand::Walk:
      digitalWrite(PIN_MOTOR_1, LOW);
      delay(100);
      digitalWrite(PIN_MOTOR_2, HIGH);
      break;
    case MotorCommand::Bark:
      digitalWrite(PIN_MOTOR_1, HIGH);
      delay(100);
      digitalWrite(PIN_MOTOR_2, LOW);
      break;
    case MotorCommand::Stop:
      digitalWrite(PIN_MOTOR_1, LOW);
      digitalWrite(PIN_MOTOR_2, LOW);
      break;
  }
}

void setup() {
  Serial.begin(9600);

  pinMode(PIN_REMOTE_A, INPUT_PULLUP);
  pinMode(PIN_REMOTE_B, INPUT_PULLUP);
  pinMode(PIN_REMOTE_C, INPUT_PULLUP);
  pinMode(PIN_REMOTE_D, INPUT_PULLUP);

  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);

  Utility::print("Setup done.");
}

void loop() {
  // put your main code here, to run repeatedly:

  auto rem = get_remote();

  if (rem == RemoteKey::None)
    return;

  Utility::print("Remote: ", (int)rem);

  switch (rem) {
    case RemoteKey::None:
      break;
    case RemoteKey::A:
      is_active = true;
      last_motor_command = MotorCommand::Walk;
      set_motor_status(MotorCommand::Walk);
      break;
    case RemoteKey::B:
      is_active = true;
      last_motor_command = MotorCommand::Bark;
      set_motor_status(MotorCommand::Bark);
      break;
    case RemoteKey::C:
      is_active = false;
      set_motor_status(MotorCommand::Stop);
      break;
    case RemoteKey::D:
      is_active = true;
      set_motor_status(last_motor_command);
      break;
  }
//  delay(200);
}
