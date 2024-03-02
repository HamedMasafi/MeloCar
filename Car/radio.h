// https://codeload.github.com/nRF24/RF24/zip/refs/heads/master

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
    int left_v{};
    int left_h{};
    int right_v{};
    int right_h{};
    bool sw_left{};
    bool sw_right{};
    int checksum{};
  };
  Radio(RadioType type, int ce = PIN_CE, int csn = PIN_CSN);

  void setup();
  bool send(Command *cmd);
  bool read(Command *cmd);

private:
  RF24 radio;
  RadioType _type;
  int checksum(Command *cmd);
};


Radio::Radio(RadioType type, int ce, int csn)
  : _type(type), radio(ce, csn) {
}

void Radio::setup() {
  if (!radio.begin()) {
    Utility::fatal("Unable to connect to NRF");
  }

  radio.setDataRate(RF24_250KBPS);
  radio.setAutoAck(true);        // Ensure autoACK is enabled
  radio.setChannel(140);           // Set RF communication channel.
  radio.setPALevel(RF24_PA_MAX);  //translate to: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.setRetries(10, 3);        //Set the number of retry attempts and delay between retry attempts when transmitting a payload. The radio is waiting for an acknowledgement (ACK) packet during the delay between retry attempts.Mode: 0-15,0-15
  radio.setPayloadSize(sizeof(Command));

  if (_type == RadioType::Server)
    radio.openWritingPipe(pipeIn);  //Open a pipe for writing

  if (_type == RadioType::Client) {
    radio.openReadingPipe(1, pipeIn);  //Open a pipe for reading
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
  Serial.print("Is chip connected: ");
  Serial.println(radio.isChipConnected() ? "yes" : "no");
}

bool Radio::send(Command *cmd) {
  cmd->checksum = checksum(cmd);
  return radio.write(cmd, sizeof(Command));
}
bool Radio::read(Command *cmd) {
  if (radio.available()) {
    // auto n = radio.getDynamicPayloadSize();
    // if (n < 1) {
    //   // Corrupt payload has been flushed
    //     Serial.print("Invalid data: ");
    //     Serial.println(n);

    //   return false;
    // }
    radio.read(cmd, sizeof(Command));

    // auto sum = checksum(cmd);
    // if (cmd->checksum != sum)
      // Utility::print("Check sums are not equal, radio=", cmd->checksum, "; calculated:", sum);
    return true;
  }

  auto n = radio.getDynamicPayloadSize();

  return false;
}

int Radio::checksum(Command *cmd) {
  return (654632 + cmd->left_h + cmd->left_v + cmd->right_h + cmd->sw_right + cmd->sw_left + cmd->sw_right) % 1024;
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