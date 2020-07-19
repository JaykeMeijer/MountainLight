#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <mdns.h>
#include "state.h"
#include "eeprom_func.h"
#include "filesystem.h"

#ifndef API_H
#define API_H

#define WIFI_ATTEMPTS 50

#define AP_SSID "MountainLightSetup"
#define AP_PASS "mountain1"

#define MDNS_NAME "mountainlight"
#define MDNS_DESC "Mountain Light Control Interface"

void init_api(void* parameter);
bool init_EEPROM();
void init_connection(bool eeprom_loaded);
void init_webserver();
void init_mdns();

void serve();
void handleNotFound(AsyncWebServerRequest *request);
void handleGetNetworkConfig(AsyncWebServerRequest *request);
void handleNetworkConfig(AsyncWebServerRequest *request);
void handleGetState(AsyncWebServerRequest *request);
void handleSetState(AsyncWebServerRequest *request);
void handleRestart(AsyncWebServerRequest *request);

#endif