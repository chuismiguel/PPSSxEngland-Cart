#include "web_server.h"
#include <WiFi.h>

WebServerHandler::WebServerHandler(CartLeds& cartLeds) : server_(80), cartLeds_(cartLeds) {}

void WebServerHandler::begin() {
    registerRoutes();
    server_.begin();
    cartLeds_.begin();
}


void WebServerHandler::startAP(const char* ssid, const char* password) {
    WiFi.softAP(ssid, password);
    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);
    cartLeds_.setBrightness(255);

    begin();  // Start the web server_
}

void WebServerHandler::registerRoutes() {
    server_.on("/config1", HTTP_GET, [this](AsyncWebServerRequest *request){
        cartLeds_.setEnglandFlagConfig();
        request->send(200, "text/plain", "Bandera inglaterra god");
    });

    server_.on("/config2", HTTP_GET, [this](AsyncWebServerRequest *request){
        cartLeds_.setPixelColor(0, cartLeds_.Color(255, 0, 0));
        request->send(200, "text/plain", "Loaded Configuration 2");
    });

    server_.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        String html = "<html><body><h1>LED Control</h1><button onclick=\"location.href='/config1'\">Bandera Inglaterra</button>";
        html += "<button onclick=\"location.href='/config2'\">Config 2</button></body></html>";
        request->send(200, "text/html", html);
    });
}
