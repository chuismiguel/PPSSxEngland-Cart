#include "cart_leds.h"

CartLeds::CartLeds(uint16_t numPixels, uint8_t pin, neoPixelType type)
    : strip(numPixels, pin, type) {
}

void CartLeds::begin() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void CartLeds::setPixelColor(uint16_t n, uint32_t color) {
    strip.setPixelColor(n, color);
}

void CartLeds::show() {
    strip.show();
}

void CartLeds::clear() {
    strip.clear();
}

void CartLeds::setBrightness(uint8_t brightness) {
    strip.setBrightness(brightness);
    strip.show();
}

uint32_t CartLeds::Color(uint8_t r, uint8_t g, uint8_t b) {
    return strip.Color(r, g, b);
}

void CartLeds::setEnglandFlagConfig(){
    for (int i = 0; i < 33; i++) {
        setPixelColor(i, Color(255, 0, 0));
    }
    for (int i = 33; i < 66; i++) {
        setPixelColor(i, Color(255, 255, 255));
    }

    for (int i = 66; i < 99; i++) {
        setPixelColor(i, Color(255, 0, 0));
    }
    strip.show();
}