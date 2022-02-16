#include <Arduino.h>
#include <FastLED.h>

#define CLOCK_PIN 25
#define DATA_PIN 26

#define LED_LENGTH 8
#define DELAY 42
#define DELTA_HSV_SHIFT 1

CRGB leds[LED_LENGTH];

void setup()
{
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, LED_LENGTH);
  FastLED.setBrightness(0x10);
}

void update_color()
{
  static uint8_t hue = 0;

  hue += DELTA_HSV_SHIFT;
  if (hue > 360)
  {
    hue = hue % 360;
  }

  fill_solid(leds, LED_LENGTH, CHSV(hue, 0xFF, 0xFF));
  FastLED.show();
}

void loop()
{
  static bool do_update;
  static uint32_t last_updated;

  if (do_update)
  {
    update_color();

    last_updated = millis();
    do_update = false;
  }

  if (millis() - last_updated > DELAY)
  {
    do_update = true;
  }
}
