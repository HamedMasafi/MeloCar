#include "utility.h"
#include "DRV8833.h"

#define PIN_HUM_D 4
#define PIN_HUM_A 18

#define PIN_POMP 5

DRV8833 pomp;
;

void setup() {
  Serial.begin(9600);

  pomp.attachMotorA(PIN_POMP, 6);
  pinMode(PIN_HUM_A, INPUT);

  pomp.motorAStop();
}

void loop() {
  auto hum = analogRead(PIN_HUM_A);

  if (hum < 970) {
    pomp.motorAForward();
    Utility::print("Pomp");
    delay(1000);
  } else
    pomp.motorAForward();
  Utility::print("Hum:", hum);
}
