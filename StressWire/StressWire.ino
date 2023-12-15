#include "music_player.h"
#include "utility.h"
#include "pins.h"
#include "led.h"


enum class State {
  Free,
  Start,
  End,
  Contact
};

void print_pins_state() {
  Utility::print("Start pin:   ", digitalRead(PIN_START_POS));
  Utility::print("End pin:     ", digitalRead(PIN_END_POS));
  Utility::print("Contact pin: ", digitalRead(PIN_WIRE_CONTACT));
}

State get_state() {
  if (digitalRead(PIN_START_POS) == LOW)
    return State::Start;
  if (digitalRead(PIN_END_POS) == LOW)
    return State::End;
  if (digitalRead(PIN_WIRE_CONTACT) == LOW)
    return State::Contact;
  return State::Free;
}

void buzz(int freq, int duration) {
  tone(PIN_BEEP, 1000);
  delay(duration);
  noTone(PIN_BEEP);
}

void setup() {
  Serial.begin(9600);
  Utility::print("Starting...");

  pinMode(PIN_BEEP, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_START_POS, INPUT_PULLUP);
  pinMode(PIN_END_POS, INPUT_PULLUP);
  pinMode(PIN_WIRE_CONTACT, INPUT_PULLUP);

  pixels.begin();
  pixels.setBrightness(30);
  pixels.show();

  set_led_color(color_white);
  // tone(PIN_BEEP, 500);
  delay(400);
  set_led_color(color_black);
  // noTone(PIN_BEEP);

  start_light_dance();

  Utility::print("Setup done.");
  print_pins_state();

  // sing(1);
}

State last_state = State::Free;
bool game_lost = false;
int fault = 0;

void start_new_game() {
  set_led_color(color_gray);
  game_lost = false;
  fault = 0;
}

void contact() {
  // led_clear();
  tone(PIN_BEEP, 3000);
  fault++;
  set_led_colors(color_red, fault);
  game_lost = fault >= 7;
  delay(400);
  noTone(PIN_BEEP);
  delay(400);
}

void finish() {
  game_lost = true;
  // for (int i = fault; i <= NUM_LEDS; ++i) {
    // set_led_color(color_green, i - fault, fault);
    // buzz(2000, 200);
  // }
  set_led_colors(color_red, fault, color_green);
  sing(1);
}
void loop() {
  auto state = get_state();

  if (state == last_state)
    return;

  if (game_lost && state != State::Start)
    return;

  switch (state) {
    case State::Free:
      Utility::print("Free");
//      if (!game_lost)
  //      set_led_color(color_black);
      break;
    case State::Start:
      Utility::print("Start");
      start_new_game();
      break;
    case State::End:
      Utility::print("End");
      finish();
      break;
    case State::Contact:
      Utility::print("Contact");
      if (!game_lost)
        contact();
      break;
  }

  last_state = state;
}
