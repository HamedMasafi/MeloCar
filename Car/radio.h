#ifndef RF_H
#define RF_H

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "pins.h"

const uint8_t PIPE_IN[6] = "MELCAR";
// const uint64_t pipeIn = 0x662266;

#define RF_COMMAND_SHIF 104
#define RF_COMMAND_START 167
#define RF_COMMAND_REVERSE 67
#define RF_COMMAND_STOP 201
#define RF_COMMAND_SET_LED_BRIGHTNESS 54
#define RF_COMMAND_SET_LED_ON 97
#define RF_COMMAND_SET_LED_OFF 21
#define RF_COMMAND_SET_LED_CHANGE_DANCER 187

void fatal(char *msg) {
  Serial.print("FATAL ERROR: ");
  Serial.println(msg);
  while (true) {
  }
}

class Radio {
public:
  enum class RadioType {
    Server,
    Client
  };
  struct Command {
    byte type;
    byte param;
  };
  Radio(RadioType type, int ce = PIN_CE, int csn = PIN_CSN);

  void setup();
  bool send(Command *cmd);
  bool read(Command *cmd);

private:
  RF24 radio;
  RadioType _type;
  bool _inited{ false };
};


Radio::Radio(RadioType type, int ce, int csn)
  : _type(type), radio(ce, csn) {
}

void Radio::setup() {
  if (!radio.begin()) {
    fatal("radio hardware is not responding!!");
  }
  radio.setPALevel(RF24_PA_LOW);  //translate to: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.setPayloadSize(sizeof(Command));

  // radio.setDataRate(RF24_250KBPS);  //speed  RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps

  // if (_type == RadioType::Server)
  radio.openWritingPipe(PIPE_IN);  //Open a pipe for writing

  // if (_type == RadioType::Client)
  {
    radio.openReadingPipe(0, PIPE_IN);  //Open a pipe for reading
    // radio.openReadingPipe(2, pipeIn);  //Open a pipe for reading
    // radio.openReadingPipe(3, pipeIn);  //Open a pipe for reading
    // radio.openReadingPipe(4, pipeIn);  //Open a pipe for reading
    // radio.openReadingPipe(5, pipeIn);  //Open a pipe for reading
  }
  // radio.setAutoAck(false);  // Ensure autoACK is enabled
  // radio.setChannel(108);          // Set RF communication channel.
  // radio.enableDynamicPayloads();  //This way you don't always have to send large packets just to send them once in a while. This enables dynamic payloads on ALL pipes.
  //radio.disableDynamicPayloads();//This disables dynamic payloads on ALL pipes. Since Ack Payloads requires Dynamic Payloads, Ack Payloads are also disabled. If dynamic payloads are later re-enabled and ack payloads are desired then enableAckPayload() must be called again as well.
  // radio.setCRCLength(RF24_CRC_16);  // Use 8-bit or 16bit CRC for performance. CRC cannot be disabled if auto-ack is enabled. Mode :RF24_CRC_DISABLED  ,RF24_CRC_8 ,RF24_CRC_16
  // radio.setRetries(10, 15);         //Set the number of retry attempts and delay between retry attempts when transmitting a payload. The radio is waiting for an acknowledgement (ACK) packet during the delay between retry attempts.Mode: 0-15,0-15

  switch (_type) {
    case RadioType::Server:
      Serial.print("Starting nrf server");
      radio.stopListening();  //Start listening on the pipes opened for reading.
      break;
    case RadioType::Client:
      Serial.print("Starting nrf client");
      radio.startListening();  //Start listening on the pipes opened for reading.
      break;
  }

  if (radio.isChipConnected())
    Serial.println(": connected");
  else
    Serial.println(": Disconnected");
  _inited = true;
}

bool Radio::send(Command *cmd) {

  if (!_inited)
    fatal("Radio is not inited");

  if (_type != RadioType::Server)
    fatal("Radio is not server");
  if (!radio.write(cmd, sizeof(Command))) {
    Serial.println("Error sending command");
    return false;
  }
  return true;
}
bool Radio::read(Command *cmd) {

  if (!_inited)
    fatal("Radio is not inited");

  if (_type != RadioType::Client)
    fatal("Radio is not client");

  if (radio.available()) {
    if (radio.getDynamicPayloadSize() < 1) {
      return false;
    }

    radio.read(cmd, sizeof(Command));

    if (!cmd->type) {
      radio.flush_rx();
    }

    Serial.print("Command read inside; type = ");
    Serial.print(cmd->type);
    Serial.print("  ; param = ");
    Serial.print(cmd->param);
    Serial.println();


    return true;
  }

  return false;
}

class RadioServer : public Radio {
public:
  RadioServer()
    : Radio(RadioType::Server) {}
};

class RadioClient : public Radio {
public:
  RadioClient()
    : Radio(RadioType::Client) {}
};

#endif  // RF_H