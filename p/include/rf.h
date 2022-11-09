#ifndef RF_H
#define RF_H

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "pins.h"
#include "commands.h"

const uint64_t pipeIn = 0x662266;

namespace Rf {
extern RF24 radio;

void setup();
bool read(rf_command *cmd);

};

#endif // RF_H