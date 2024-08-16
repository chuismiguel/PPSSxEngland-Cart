#ifndef CartLeds_H
#define CartLeds_H

#include <Adafruit_NeoPixel.h>

class CartLeds {
public:
    CartLeds(uint16_t numPixels, uint8_t pin, neoPixelType type = NEO_GRB + NEO_KHZ800);

    void begin();
    void setPixelColor(uint16_t n, uint32_t color);
    void show();
    void clear();
    void setBrightness(uint8_t brightness);
    uint32_t Color(uint8_t r, uint8_t g, uint8_t b);

public:
    void setEnglandFlagConfig();
private:
    Adafruit_NeoPixel strip;
};

#endif
