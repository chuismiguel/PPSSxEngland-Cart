#ifndef VOLTAGESENSOR_H
#define VOLTAGESENSOR_H

#include <Arduino.h>

class VoltageSensor {
  public:
    VoltageSensor(int sensorPin, float voltageDividerRatio,  float calibrationFactor);
    float readVoltage();
  
  private:
    int _sensorPin;
    float _voltageDividerRatio;
    int _maxAdcValue;
    float _adcReferenceVoltage;
    float _calibrationFactor;
};

#endif
