#include "cart_leds.h"

CartSectionHandler::CartSectionHandler(const CartLedSection& section, Adafruit_NeoPixel* strip)
    : ledPixels_(section), strip_(strip) {
}

void CartSectionHandler::tick() {
    switch (status_)
    {
    case SectionStatus::dispensing:
        /* code */
        break;
    case SectionStatus::fade:
        /* code */
        break;
    default:
        break;
    }
}

void CartSectionHandler::setFixedColor(uint32_t color) {
    fixedColor_ = color;
}

void CartSectionHandler::setStatus(SectionStatus status) {
    status_ = status;

    switch (status_)
    {
    case SectionStatus::off:
        for (auto pair : ledPixels_) {
            for (int i = pair.first; i < pair.second; i++) {
              strip_->setPixelColor(i, strip_->Color(0, 0, 0));  // Set pixel to off (black)
            }
        }
        strip_->show();
        break;

    case SectionStatus::fixedColor:
        for (auto pair : ledPixels_) {
            for (int i = pair.first; i < pair.second; i++) {
              strip_->setPixelColor(i, fixedColor_);  // Set pixel to off (black)
            }
        }
        strip_->show();
        break;
    default:
        break;
    }
}

// CART LEDS

CartLeds::CartLeds(uint16_t numPixels, uint8_t pin, neoPixelType type)
    : strip_(std::make_shared<Adafruit_NeoPixel>(numPixels, pin, type)), 
    leftSideHandler_(CartSectionHandler(leftSideStripSections, strip_.get())), 
    rightSideHandler_(CartSectionHandler(rightSideStripSections, strip_.get())),
    bottomSideHandler_(CartSectionHandler(frontStripSections, strip_.get())),
    balconyHandler_(CartSectionHandler(balconyStripSections, strip_.get()))
{

}

void CartLeds::begin() {
    strip_->begin();
    strip_->show(); // Initialize all pixels to 'off'
}

void CartLeds::setPixelColor(uint16_t n, uint32_t color) {
    strip_->setPixelColor(n, color);
}

void CartLeds::show() {
    strip_->show();
}

void CartLeds::clear() {
    strip_->clear();
}

void CartLeds::setBrightness(uint8_t brightness) {
    strip_->setBrightness(brightness);
    strip_->show();
}

uint32_t CartLeds::Color(uint8_t r, uint8_t g, uint8_t b) {
    return strip_->Color(r, g, b);
}

void CartLeds::setSectionStatus(CartSectionName section, SectionStatus status){
    switch (section)
    {
    case CartSectionName::leftSide:
        leftSideHandler_.setStatus(status);
        break;
    case CartSectionName::rightSide:
        rightSideHandler_.setStatus(status);
        break;
    case CartSectionName::balcony:
        balconyHandler_.setStatus(status);
        break;
    case CartSectionName::frontSide:
        bottomSideHandler_.setStatus(status);
        break;
    }
}