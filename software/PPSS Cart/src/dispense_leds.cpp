#include "dispense_leds.h"

DispenseLeds::DispenseLeds(int pin, int numPixels)
  : strip(numPixels, pin, NEO_GRB + NEO_KHZ800), maxDispenseLedsOn(numPixels) {}

void DispenseLeds::begin() {
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
}

void DispenseLeds::setDispenseLedsOn(int numDispenseLeds) {
  if (numDispenseLeds > strip.numPixels()) {
    maxDispenseLedsOn = strip.numPixels();
  } else {
    maxDispenseLedsOn = numDispenseLeds;
  }
}

void DispenseLeds::setLedColor(uint32_t color) {
  for (int i = 0; i < strip.numPixels(); i++) {
    if (i < maxDispenseLedsOn) {
      strip.setPixelColor(i, color);
    } else {
      strip.setPixelColor(i, 0);  // Turn off the LED
    }
  }
  strip.show();
}

void DispenseLeds::turnOff() {
    for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0);  // Set each LED to 'off'
    }
    strip.show();  // Update the strip to turn off all DispenseLeds
}

void DispenseLeds::setDispensing(unsigned long interval) {
  unsigned long currentMillis = millis();
  uint32_t purple = strip.Color(128, 0, 128);  // Define the purple color

  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      // Shift all the DispenseLeds one position forward
      for (int i = strip.numPixels() - 1; i > 0; i--) {
          strip.setPixelColor(i, strip.getPixelColor(i - 1));
      }

      // Set the first LED to the specified color (purple in this case)
      strip.setPixelColor(0, purple);

      // Update the LED strip to show the changes
      strip.show();

      // Increment the position, and reset if it exceeds the number of DispenseLeds
      currentPosition++;
      if (currentPosition >= strip.numPixels()) {
          currentPosition = 0;
          turnOff();
      }
  }
}