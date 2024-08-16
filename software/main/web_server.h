#ifndef WEBSERVERHANDLER_H
#define WEBSERVERHANDLER_H

#include <ESPAsyncWebServer.h>

class WebServerHandler {
public:
    WebServerHandler();
    void begin();
    void startAP(const char* ssid, const char* password);
    void registerRoutes();
    
private:
    AsyncWebServer server;
};

#endif
