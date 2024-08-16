#include "led_control.h"

LEDControl::LEDControl(uint16_t numPixels, uint8_t pin, neoPixelType type)
    : strip(numPixels, pin, type) {
}

void LEDControl::begin() {
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void LEDControl::setPixelColor(uint16_t n, uint32_t color) {
    strip.setPixelColor(n, color);
}

void LEDControl::show() {
    strip.show();
}

void LEDControl::clear() {
    strip.clear();
}

void LEDControl::setBrightness(uint8_t brightness) {
    strip.setBrightness(brightness);
    strip.show();
}

uint32_t LEDControl::Color(uint8_t r, uint8_t g, uint8_t b) {
    return strip.Color(r, g, b);
}

void LEDControl::setEnglandFlagConfig(){
    for (int i = 0; i < 30; i++) {
        setPixelColor(i, Color(255, 0, 0));
    }
    for (int i = 30; i < 60; i++) {
        setPixelColor(i, Color(255, 255, 255));
    }

    for (int i = 60; i < 90; i++) {
        setPixelColor(i, Color(255, 0, 0));
    }
    strip.show();
}