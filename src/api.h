#include <WiFi.h>
#include <esp_task_wdt.h>
#include <ESPAsyncWebServer.h>
#include <DNSServer.h>
#include <mdns.h>
#include <ArduinoOTA.h>
#include "state.h"
#include "eeprom_func.h"
#include "filesystem.h"
#include "programs.h"

#ifndef API_H
#define API_H

#define WIFI_ATTEMPTS 20

#define AP_SSID "MountainLightSetup"
#define AP_PASS "mountain1"

#define MDNS_NAME "mountainlight"
#define MDNS_DESC "Mountain Light Control Interface"

#define DNS_PORT 53


void init_api(void* parameter);
bool init_EEPROM();
void init_connection(bool eeprom_loaded);
void init_webserver();
void init_mdns();
void init_ota();

void serve();
void handle_extra();
void handleNotFound(AsyncWebServerRequest *request);
void handleGetNetworkConfig(AsyncWebServerRequest *request);
void handleNetworkConfig(AsyncWebServerRequest *request);
void handleGetOptions(AsyncWebServerRequest *request);
void handleGetState(AsyncWebServerRequest *request);
void handleSetState(AsyncWebServerRequest *request);
void handleRestart(AsyncWebServerRequest *request);
void handleOTA(AsyncWebServerRequest *request);
void handleGetDebug(AsyncWebServerRequest *request);

#endif