#include "pins.h"
#include "smooth_reader.h"
#include "avg_list.h"
#include "utility.h"
#include "commands.h"
#include "rf.h"

smooth_reader x1(120, 70);
smooth_reader x2(1, -1);
smooth_reader y1(-100, 100);
smooth_reader y2(-100, 100);

int x1_value, x2_value, y1_value, y2_value;

void setup() {
  Serial.begin(9600);

  x1.attach(PIN_X_1);
  x2.attach(PIN_X_2);
  y1.attach(PIN_Y_1);
  y2.attach(PIN_Y_2);

  Rf::setup();
}

rf_command cmd;
void loop() {

 /* if (x1.read(x1_value)) {
    // cmd.type = RF_COMMAND_SHIF;
    // cmd.param1 = map(x1_value, 0, 1023, 120, 70);//Utility::map(x1_value, 0, 1024, -100, 100);
    // Serial.println(cmd.param1);
    // Rf::send(&cmd);
  }

  if (x2.read(x2_value)) {
    if (x2_value > 10) {
      cmd.type = RF_COMMAND_START;
      Rf::send(&cmd);
    }
    else if (x2_value < -10) {
      cmd.type = RF_COMMAND_REVERSE;
      Rf::send(&cmd);
    } else {
      cmd.type = RF_COMMAND_STOP;
      Rf::send(&cmd);
    }
  }*/

  auto x = map(x1.read(), 0, 1023, 120, 70);
  auto y = map(y1.read(), 0, 1023, 1, -1);

  cmd.type = RF_COMMAND_SHIF;
  cmd.param1 = x;
  Serial.println(cmd.param1);
  Rf::send(&cmd);
  delay(100);
  
  // map_t<int>(0, 0, 0, 0, 0);
  Serial.print("x=");
  Serial.print(x);
  Serial.print("\t\t");
  Serial.print("y=");
  Serial.print(y);
  Serial.println();
}