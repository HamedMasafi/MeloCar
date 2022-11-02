#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define PIN_CSN 10
#define PIN_CE  9

const uint64_t pipeIn = 0x662266;
#define PIN_MOTOR_1 8
#define PIN_MOTOR_2 7
#define PIN_SERVO 9
#define MOTOR_START 0
#define MOTOR_STOP 2
#define MOTOR_REVERSE 1


Servo servo;
RF24 radio(PIN_CE, PIN_CSN); 


struct MyData {
  byte test;
};

void shift(int angle) {
  servo.write(angle);
  delay(15);
}

void motor_command(int command) {
  switch (command) {
    case MOTOR_START:
      digitalWrite(PIN_MOTOR_1, LOW);
      digitalWrite(PIN_MOTOR_2, HIGH);
      break;
    case MOTOR_STOP:
      digitalWrite(PIN_MOTOR_1, LOW);
      digitalWrite(PIN_MOTOR_2, LOW);
      break;
    case MOTOR_REVERSE:
      digitalWrite(PIN_MOTOR_1, HIGH);
      digitalWrite(PIN_MOTOR_2, LOW);
      break;
  }
}

void setup() {
  servo.attach(PIN_SERVO);
  shift(90);
  
  pinMode(PIN_MOTOR_1, OUTPUT);
  pinMode(PIN_MOTOR_2, OUTPUT);

  radio.begin();
  radio.setDataRate(RF24_250KBPS); //speed  RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
  radio.openWritingPipe(pipeIn);//Open a pipe for writing
  radio.openReadingPipe(1, pipeIn);//Open a pipe for reading
  radio.openReadingPipe(2, pipeIn);//Open a pipe for reading
  radio.openReadingPipe(3, pipeIn);//Open a pipe for reading
  radio.openReadingPipe(4, pipeIn);//Open a pipe for reading
  radio.openReadingPipe(5, pipeIn);//Open a pipe for reading
  radio.setAutoAck(true); // Ensure autoACK is enabled
  radio.setChannel(108);// Set RF communication channel.
  radio.setPALevel(RF24_PA_MAX); //translate to: RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_MED=-6dBM, and RF24_PA_HIGH=0dBm.
  radio.enableDynamicPayloads(); //This way you don't always have to send large packets just to send them once in a while. This enables dynamic payloads on ALL pipes.
  //radio.disableDynamicPayloads();//This disables dynamic payloads on ALL pipes. Since Ack Payloads requires Dynamic Payloads, Ack Payloads are also disabled. If dynamic payloads are later re-enabled and ack payloads are desired then enableAckPayload() must be called again as well.
  radio.setCRCLength(RF24_CRC_16); // Use 8-bit or 16bit CRC for performance. CRC cannot be disabled if auto-ack is enabled. Mode :RF24_CRC_DISABLED  ,RF24_CRC_8 ,RF24_CRC_16
  radio.setRetries(10, 15);//Set the number of retry attempts and delay between retry attempts when transmitting a payload. The radio is waiting for an acknowledgement (ACK) packet during the delay between retry attempts.Mode: 0-15,0-15
  radio.startListening();//Start listening on the pipes opened for reading.

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Starting");
  shift(0);
  motor_command(MOTOR_START);
  delay(1000);

  Serial.println("Stopping");
  shift(90);
  motor_command(MOTOR_STOP);
  delay(1000);

  Serial.println("Reversing");
  shift(180);
  motor_command(MOTOR_REVERSE);
  delay(1000);
}
