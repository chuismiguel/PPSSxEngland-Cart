#ifndef LEDS_H
#define LEDS_H

#include <Adafruit_NeoPixel.h>

class LEDs {
  public:
    LEDs(int pin, int numPixels);
    void begin();
    void setLedsOn(int numLeds);
    void setLedColor(uint32_t color);
    void turnOff();  // Function to turn off all LEDs
    void setDispensing(unsigned long interval);
    Adafruit_NeoPixel strip;
    
  private:
    int maxLedsOn;
    unsigned long previousMillis;
    int currentPosition;
};

#endif
