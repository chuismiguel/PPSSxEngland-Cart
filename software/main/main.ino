#include "voltage_sensor.h"
#include "leds.h"
#include "web_server.h"

namespace voltage_sensor {
const int pin = 35;
const int divideRatio = 5.0;
const float calibrationFactor = 1.0399;

unsigned long lastReadT = 0;
const int readingTime = 5 * 1000;
}

namespace water_control {
const int ledPin = 27;
const int buttonPin = 33;
}

namespace battery {
    const float min = 9.0;
    const float max = 12.6;
}

VoltageSensor batterySensor(voltage_sensor::pin, voltage_sensor ::divideRatio, voltage_sensor ::calibrationFactor);
LEDs ledController(water_control::ledPin, 8);  // Pin 5, 8 LEDs]
WebServerHandler webServer;

void setup() {
  // Start the serial communication for debugging purposes
  Serial.begin(115200);
  pinMode(water_control::buttonPin, INPUT_PULLDOWN);
  ledController.begin();  // Initialize the LEDs controller

  const char* ap_ssid = "PPSScarro";     // Set your desired AP SSID UNCOMMENT WHEN LEDS ARRIVE
  const char* ap_password = "chemayguilli"; // Set your desired AP password
  webServer.startAP(ap_ssid, ap_password);  // Start the Access Point and web server
}

void loop() {
    unsigned long currentMillis = millis();
  
  if (currentMillis - voltage_sensor ::lastReadT >= voltage_sensor ::readingTime) {
    voltage_sensor ::lastReadT = currentMillis;
    
    int numLedsOn = map(batterySensor.readVoltage(), battery::min, battery::max, 1, ledController.strip.numPixels());
    ledController.setLedsOn(numLedsOn);
  }

  int buttonState = digitalRead(water_control::buttonPin);
  if (buttonState == LOW) {  // Button is pressed (assuming active LOW)
    ledController.turnOff();
  } else {  // Button is not pressed
    ledController.setLedsOn(8);
    ledController.setDispensing(50);  // Green color
  }
}
