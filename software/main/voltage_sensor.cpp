#include "voltage_sensor.h"

VoltageSensor::VoltageSensor(int sensorPin, float voltageDividerRatio, float calibrationFactor)
  : _sensorPin(sensorPin), _voltageDividerRatio(voltageDividerRatio), _calibrationFactor(calibrationFactor) {
  // Assuming the ESP32 ADC is 12-bit with a reference voltage of 3.3V
  _maxAdcValue = 4095.0;
  _adcReferenceVoltage = 3.3;
  pinMode(_sensorPin, INPUT);
}

float VoltageSensor::readVoltage() {
  int sensorValue = analogRead(_sensorPin);  // Read the ADC value from the sensor
  float voltage = sensorValue * (_adcReferenceVoltage / _maxAdcValue);  // Convert ADC value to voltage
  
  float batteryVoltage = voltage * _voltageDividerRatio * _calibrationFactor;  // Calculate the actual battery voltage
  return batteryVoltage;
}
