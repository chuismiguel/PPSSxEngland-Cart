#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <ESPAsyncWebServer.h>
#include "cart_leds.h"

class WebServerHandler {
public:
    WebServerHandler(CartLeds& cartLeds);
    void begin();
    void startAP(const char* ssid, const char* password);
    void registerRoutes();
    
private:
    AsyncWebServer server_;
    CartLeds cartLeds_;
};

#endif
