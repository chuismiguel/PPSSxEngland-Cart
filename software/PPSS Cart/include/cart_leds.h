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

class CartSectionHandler {
  static constexpr int balconyOnTime = 20;
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
  unsigned long balconyPrevTickMillis_;
  unsigned long currentBalconyLedOn_;
  std::vector<unsigned long> fadePrevTickMillis_;
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
