#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>
#include <TM1637Display.h>

#include "utility.h"

// Pin definitions
#define LED_PIN 5      // Pin for WS2812B strip
#define DS18B20_PIN 6  // Pin for DS18B20 data
#define PIN_CLK 7
#define PIN_DIO 8

#define NUM_LEDS 7  // Number of LEDs in the strip

// Temperature sensor setup
OneWire oneWire{ DS18B20_PIN };
DallasTemperature sensors{ &oneWire };
TM1637Display disp{ PIN_CLK, PIN_DIO };
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


void showTemp(float temp) {
  int integerPart = (int)temp;
  int decimalPart = (int)((temp - integerPart) * 100);

  disp.showNumberDecEx(integerPart * 100 + decimalPart, 0b01000000, true, 4, 0);
}

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Initialize the temperature sensor
  sensors.begin();

  // Initialize the LED strip
  strip.begin();
  strip.show();

  disp.setBrightness(0x0f);

  Utility::print("Setup done");
}


void set_color(uint32_t color) {
  strip.fill(color, 0, 7);
  strip.show();
}

void loop() {
  // Request temperature readings
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);

  Utility::print("Temperature: ", temperatureC, " °C");

  // Determine color based on temperature
  uint32_t color = getColorFromTemperature(temperatureC);
  showTemp(temperatureC);

  set_color(color);

  delay(1000);
}

// Function to determine color based on temperature
uint32_t getColorFromTemperature(float tempC) {
  // Define temperature range for color transitions
  const float normalTemp = 27.0;
  const float minTemp = 15.0;  // Temperature for maximum blue
  const float maxTemp = 35.0;  // Temperature for maximum red

  uint8_t red, green, blue;

  if (tempC < normalTemp) {
    // Temperature is colder than normal, gradient towards blue
    float t = constrain((normalTemp - tempC) / (normalTemp - minTemp), 0, 1);
    red = (1 - t) * 0;  // No red for cold
    green = (1 - t) * 255;
    blue = t * 255;  // More blue for colder
  } else if (tempC > normalTemp) {
    // Temperature is warmer than normal, gradient towards red
    float t = constrain((tempC - normalTemp) / (maxTemp - normalTemp), 0, 1);
    red = t * 255;  // More red for warmer
    green = (1 - t) * 255;
    blue = (1 - t) * 0;  // No blue for warm
  } else {
    // Temperature is normal, set color to green
    red = 0;
    green = 255;
    blue = 0;
  }

  return Adafruit_NeoPixel::Color(red, green, blue);
}
