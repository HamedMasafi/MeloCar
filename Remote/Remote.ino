#include "pins.h"
#include "smooth_reader.h"
#include "avg_list.h"
#include "utility.h"
#include "commands.h"

smooth_reader x1;
smooth_reader x2;
smooth_reader y1;
smooth_reader y2;

int x1_value, x2_value, y1_value, y2_value;

void setup() {
  Serial.begin(9600);

  x1.attach(PIN_X_1);
  x2.attach(PIN_X_2);
  y1.attach(PIN_Y_1);
  y2.attach(PIN_Y_2);
}

rf_command cmd;
void loop() {

  if (x1.read(x1_value)) {
    cmd.type = RF_COMMAND_SHIF;
    cmd.param1 = Utility::map(x1_value, 0, 1024, -100, 100);
  }
  auto x = Utility::map(x1.read(), 0, 1024, -100, 100);
  auto y = Utility::map(y1.read(), 0, 1024, -100, 100);

  // map_t<int>(0, 0, 0, 0, 0);
  Serial.print("x=");
  Serial.print(x);
  Serial.print("\t\t");
  Serial.print("y=");
  Serial.print(y);
  Serial.print("x=");
  Serial.println();
}