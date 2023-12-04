#include <Adafruit_NeoPixel.h>
#include "music_player.h"

#define NUM_LEDS 7
#define PIN_LED 5
#define PIN_START_POS 8
#define PIN_END_POS 7
#define PIN_WIRE_CONTACT 6
#define PIN_BEEP 2

Adafruit_NeoPixel pixels(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

auto color_red = Adafruit_NeoPixel::Color(255, 0, 0);
auto color_green = Adafruit_NeoPixel::Color(0, 255, 0);
auto color_white = Adafruit_NeoPixel::Color(255, 255, 255);
auto color_black = Adafruit_NeoPixel::Color(0, 0, 0);
auto color_yellow = Adafruit_NeoPixel::Color(255, 255, 0);

enum class State {
  Free,
  Start,
  End,
  Contact
};

State get_state() {
  if (digitalRead(PIN_START_POS))
    return State::Start;
  if (digitalRead(PIN_END_POS))
    return State::End;
  if (digitalRead(PIN_WIRE_CONTACT))
    return State::Contact;
  return State::Free;
}

void set_led_color(uint32_t color) {
  pixels.fill(color, 0, 7);
  pixels.show();
}

void setup() {
  Serial.begin(9600);

  pixels.begin();
  pixels.setBrightness(120);
  pixels.show();

  pinMode(PIN_BEEP, OUTPUT);
  pinMode(PIN_START_POS, INPUT_PULLUP);
  pinMode(PIN_END_POS, INPUT_PULLUP);
  pinMode(PIN_WIRE_CONTACT, INPUT_PULLUP);
}

State last_state = State::Free;
bool game_lost = false;
int fault = 0;

void start_new_game() {
  set_led_color(color_yellow);
  game_lost = false;
  fault = 0;
}

void contact() {
  set_led_color(color_red);
  tone(PIN_BEEP, 1000);
  fault++;
  if (fault = >= 3)
    game_lost = true;
  delay(100);
  noTone(PIN_BEEP);
  set_led_color(color_black);
}

void loop() {
  auto state = get_state();

  if (state == last_state)
    return;

  if (game_lost && state != State::Start)
    return;

  switch (state) {
    case State::Free:
      set_led_color(color_black);
      break;
    case State::Start:
      start_new_game();
      break;
    case State::End:
      game_lost = true;
      set_led_color(color_green);
      sing(1);
      break;
    case State::Contact:
      contact();
      break;
  }

  last_state = state;
}
