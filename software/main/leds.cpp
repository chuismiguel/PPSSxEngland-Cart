#include "leds.h"

LEDs::LEDs(int pin, int numPixels)
  : strip(numPixels, pin, NEO_GRB + NEO_KHZ800), maxLedsOn(numPixels) {}

void LEDs::begin() {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
}

void LEDs::setLedsOn(int numLeds) {
  if (numLeds > strip.numPixels()) {
    maxLedsOn = strip.numPixels();
  } else {
    maxLedsOn = numLeds;
  }
}

void LEDs::setLedColor(uint32_t color) {
  for (int i = 0; i < strip.numPixels(); i++) {
    if (i < maxLedsOn) {
      strip.setPixelColor(i, color);
    } else {
      strip.setPixelColor(i, 0);  // Turn off the LED
    }
  }
  strip.show();
}

void LEDs::turnOff() {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0);  // Set each LED to 'off'
    }
    strip.show();  // Update the strip to turn off all LEDs
}

void LEDs::setDispensing(unsigned long interval) {
  unsigned long currentMillis = millis();
  uint32_t purple = strip.Color(128, 0, 128);  // Define the purple color

  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      // Shift all the LEDs one position forward
      for (int i = strip.numPixels() - 1; i > 0; i--) {
          strip.setPixelColor(i, strip.getPixelColor(i - 1));
      }

      // Set the first LED to the specified color (purple in this case)
      strip.setPixelColor(0, purple);

      // Update the LED strip to show the changes
      strip.show();

      // Increment the position, and reset if it exceeds the number of LEDs
      currentPosition++;
      if (currentPosition >= strip.numPixels()) {
          currentPosition = 0;
          turnOff();
      }
  }
}