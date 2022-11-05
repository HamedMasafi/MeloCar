#define RF_COMMAND_SHIF 104
#define RF_COMMAND_START 167
#define RF_COMMAND_STOP 201
#define RF_COMMAND_SET_LED_BRIGHTNESS 54
#define RF_COMMAND_SET_LED_OFF 97
#define RF_COMMAND_SET_LED_OFF 21

struct rf_command {
  byte test;
  byte type;
  byte param1;
  byte param2;
  byte terminate;
};
