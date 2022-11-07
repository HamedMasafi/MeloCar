#include "rf.h"

namespace Rf {

RF24 radio(PIN_CE, PIN_CSN);

void setup() {
  radio.begin();
  radio.setDataRate(RF24_250KBPS);   //speed  RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
  radio.openWritingPipe(pipeIn);     //Open a pipe for writing
  radio.openReadingPipe(1, pipeIn);  //Open a pipe for reading
  radio.openReadingPipe(2, pipeIn);  //Open a pipe for reading
  radio.openReadingPipe(3, pipeIn);  //Open a pipe for reading
  radio.openReadingPipe(4, pipeIn);  //Open a pipe for reading
  radio.openReadingPipe(5, pipeIn);  //Open a pipe for reading
  radio.setAutoAck(true);            // Ensure autoACK is enabled
  radio.setChannel(108);             // Set RF communication channel.
  radio.setPALevel(RF24_PA_MAX);     //translate to: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.enableDynamicPayloads();     //This way you don't always have to send large packets just to send them once in a while. This enables dynamic payloads on ALL pipes.
  //radio.disableDynamicPayloads();//This disables dynamic payloads on ALL pipes. Since Ack Payloads requires Dynamic Payloads, Ack Payloads are also disabled. If dynamic payloads are later re-enabled and ack payloads are desired then enableAckPayload() must be called again as well.
  radio.setCRCLength(RF24_CRC_16);  // Use 8-bit or 16bit CRC for performance. CRC cannot be disabled if auto-ack is enabled. Mode :RF24_CRC_DISABLED  ,RF24_CRC_8 ,RF24_CRC_16
  radio.setRetries(10, 15);         //Set the number of retry attempts and delay between retry attempts when transmitting a payload. The radio is waiting for an acknowledgement (ACK) packet during the delay between retry attempts.Mode: 0-15,0-15
  radio.startListening();           //Start listening on the pipes opened for reading.
}

bool read(rf_command *cmd) {
  if (radio.available()) {
    radio.read(&cmd, sizeof(rf_command));
    return true;
  }

  return false;
}

};