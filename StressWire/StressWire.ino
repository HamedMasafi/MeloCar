#include "music_player.h"
#include "utility.h"
#include "pins.h"
#include "led.h"

#define DEBUG

// Types ================================
enum class WireState {
  Free,
  Start,
  End,
  Contact
};

enum class GameState {
  Playing,
  Over,
  Win
};

// Variables ================================
WireState last_state = WireState::Free;
GameState game_state = GameState::Playing;
int fault = 0;

// Methods ================================
void print_pins_state() {
  Utility::print("Start pin:   ", digitalRead(PIN_START_POS));
  Utility::print("End pin:     ", digitalRead(PIN_END_POS));
  Utility::print("Contact pin: ", digitalRead(PIN_WIRE_CONTACT));
}

WireState get_state() {
  auto ch = (char)Serial.read();

#ifdef DEBUG
  if (ch == 'c')
    return WireState::Contact;
  if (ch == 's')
    return WireState::Start;
  if (ch == 'e')
    return WireState::End;
#else
  if (digitalRead(PIN_START_POS) == LOW)
    return WireState::Start;
  if (digitalRead(PIN_END_POS) == LOW)
    return WireState::End;
  if (digitalRead(PIN_WIRE_CONTACT) == LOW)
    return WireState::Contact;
#endif

  return WireState::Free;
}

void buzz(int freq, int duration) {
  tone(PIN_BEEP, 1000);
  delay(duration);
  noTone(PIN_BEEP);
}

void setFault(int f) {
  if (f < 0 || f > 8)
    return;

  fault = f;
  set_led_colors(color_red, f);
}

void start_new_game() {
  start_light_dance(fault, 0, color_red, 170);
  game_state = GameState::Playing;
  fault = 0;
}

void contact() {
  // led_clear();
  if (game_state != GameState::Playing)
    return;

  tone(PIN_BEEP, 3000);

  setFault(++fault);
  if (fault >= 8)
    GameState::Over;

  delay(400);
  noTone(PIN_BEEP);
  delay(400);
}

void finish() {
  if (game_state != GameState::Playing)
    return;
  game_state = GameState::Win;
  set_led_colors(color_red, fault, color_green);
  sing(1);
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

  set_led_color(color_white);
  delay(400);
  set_led_color(color_black);

  start_light_dance(0, 8);

  Utility::print("Setup done.");
#ifdef DEBUG
  print_pins_state();
#endif

  start_new_game();
}

void loop() {
  auto state = get_state();

  if (state == last_state)
    return;

  switch (state) {
    case WireState::Free:
      Utility::print("Free");
      break;
    case WireState::Start:
      Utility::print("Start");
      start_new_game();
      break;
    case WireState::End:
      Utility::print("End");
      finish();
      break;
    case WireState::Contact:
      Utility::print("Contact");
      contact();
      break;
  }

  last_state = state;
}
