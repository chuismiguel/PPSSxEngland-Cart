#include "web_server.h"
#include "led_control.h"
#include <WiFi.h>

// Define the number of LEDs and the pin they are connected to
#define LED_PIN    25
#define NUM_LEDS   90

LEDControl ledControl(NUM_LEDS, LED_PIN);

WebServerHandler::WebServerHandler() : server(80) {}

void WebServerHandler::begin() {
    registerRoutes();
    server.begin();
    ledControl.begin();
}


void WebServerHandler::startAP(const char* ssid, const char* password) {
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    ledControl.setBrightness(255);

    begin();  // Start the web server
}

void WebServerHandler::registerRoutes() {
    server.on("/config1", HTTP_GET, [](AsyncWebServerRequest *request){
        ledControl.setEnglandFlagConfig();
        request->send(200, "text/plain", "Bandera inglaterra god");
    });

    server.on("/config2", HTTP_GET, [](AsyncWebServerRequest *request){
        ledControl.setPixelColor(0, ledControl.Color(255, 0, 0));
        request->send(200, "text/plain", "Loaded Configuration 2");
    });

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        String html = "<html><body><h1>LED Control</h1><button onclick=\"location.href='/config1'\">Bandera Inglaterra</button>";
        html += "<button onclick=\"location.href='/config2'\">Config 2</button></body></html>";
        request->send(200, "text/html", html);
    });
}
