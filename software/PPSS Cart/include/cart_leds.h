#ifndef CartLeds_H
#define CartLeds_H

#include <Adafruit_NeoPixel.h>
#include <map>
#include <vector>
#include <utility>
#include <memory>

using CartLedSection = std::vector<std::pair<int, int>>;

enum CartSectionName {
  leftSide,
  frontSide,
  balcony,
  rightSide
};

enum SectionStatus {
  fade,
  fixedColor,
  dispensing,
  off
};

CartLedSection leftSideStripSections  = {{0, 11}, {66, 90}};
CartLedSection rightSideStripSections  = {{19, 53}};
CartLedSection balconyStripSections  = {{54, 65}};
CartLedSection frontStripSections  = {{12, 18}};

class CartSectionHandler {
  public:
    CartSectionHandler(const CartLedSection& section, Adafruit_NeoPixel* strip);

    void setStatus(SectionStatus status);
    void setFixedColor( uint32_t color);
    void tick();

private:
  // vector of pairs pixelN, pixelStart that define the different strip sections of an area
  CartLedSection ledPixels_;
  Adafruit_NeoPixel* strip_;
  SectionStatus status_;
  uint32_t fixedColor_;

};

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
    void setSectionStatus(CartSectionName section, SectionStatus status);
    void allOff();
    void setSidesFade();

private:
    std::shared_ptr<Adafruit_NeoPixel> strip_;

    CartSectionHandler leftSideHandler_;
    CartSectionHandler rightSideHandler_;
    CartSectionHandler bottomSideHandler_;
    CartSectionHandler balconyHandler_;
    
};

#endif
