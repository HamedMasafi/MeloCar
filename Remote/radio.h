#ifndef RF_H
#define RF_H

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "utility.h"

#include "pins.h"

//const uint64_t pipeIn = 0x662266;
uint8_t pipeIn[6] = "MELCAR";

class Radio {
public:
  enum class RadioType {
    Server,
    Client
  };
  struct Command {
    int left_v;
    int left_h;
    int right_v;
    int right_h;
    int extra_1;
    int extra_2;
  };
  Radio(RadioType type, int ce = PIN_CE, int csn = PIN_CSN);

  void setup();
  bool send(Command *cmd);
  bool read(Command *cmd);

private:
  RF24 radio;
  RadioType _type;
};


Radio::Radio(RadioType type, int ce, int csn)
  : _type(type), radio(ce, csn) {
}

void Radio::setup() {
  if (!radio.begin()) {
    Utility::fatal("Unable to connect to NRF");
  }

  radio.setDataRate(RF24_1MBPS);
  radio.setAutoAck(false);        // Ensure autoACK is enabled
  radio.setChannel(108);          // Set RF communication channel.
  radio.setPALevel(RF24_PA_MIN);  //translate to: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.setRetries(10, 3);        //Set the number of retry attempts and delay between retry attempts when transmitting a payload. The radio is waiting for an acknowledgement (ACK) packet during the delay between retry attempts.Mode: 0-15,0-15
  radio.setPayloadSize(sizeof(Command));

  if (_type == RadioType::Server)
    radio.openWritingPipe(pipeIn);  //Open a pipe for writing

  if (_type == RadioType::Client) {
    radio.openReadingPipe(0, pipeIn);  //Open a pipe for reading
    // radio.openReadingPipe(2, pipeIn);  //Open a pipe for reading
    // radio.openReadingPipe(3, pipeIn);  //Open a pipe for reading
    // radio.openReadingPipe(4, pipeIn);  //Open a pipe for reading
    // radio.openReadingPipe(5, pipeIn);  //Open a pipe for reading
  }

  switch (_type) {
    case RadioType::Server:
      radio.stopListening();  //Start listening on the pipes opened for reading.
      break;
    case RadioType::Client:
      radio.startListening();  //Start listening on the pipes opened for reading.
      break;
  }
  Serial.print("Connected to NRF successfuly; payload size=");
  Serial.println(sizeof(Command));
}

bool Radio::send(Command *cmd) {
  return radio.write(cmd, sizeof(Command));
}
bool Radio::read(Command *cmd) {
  if (radio.available()) {
    radio.read(cmd, sizeof(Command));
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