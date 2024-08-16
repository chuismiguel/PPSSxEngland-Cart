#ifndef DispenseLeds_H
#define DispenseLeds_H

#include <Adafruit_NeoPixel.h>

class DispenseLeds {
  public:
    DispenseLeds(int pin, int numPixels);
    void begin();
    void setDispenseLedsOn(int numDispenseLeds);
    void setLedColor(uint32_t color);
    void turnOff();  // Function to turn off all DispenseLeds
    void setDispensing(unsigned long interval);
    Adafruit_NeoPixel strip;
    
  private:
    int maxDispenseLedsOn;
    unsigned long previousMillis;
    int currentPosition;
};

#endif
