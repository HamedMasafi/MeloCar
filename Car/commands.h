#include "simulate.h"

#ifndef COMMANDS_H
#define COMMANDS_H

#define RF_COMMAND_SHIF 104
#define RF_COMMAND_START 167
#define RF_COMMAND_REVERSE 67
#define RF_COMMAND_STOP 201
#define RF_COMMAND_SET_LED_BRIGHTNESS 54
#define RF_COMMAND_SET_LED_ON 97
#define RF_COMMAND_SET_LED_OFF 21
#define RF_COMMAND_SET_LED_CHANGE_DANCER 187

struct rf_command {
  byte test;
  byte type = 0;
  byte param1;
  byte param2;
  byte terminate;
};

#endif // COMMANDS_H
