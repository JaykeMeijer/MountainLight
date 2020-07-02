#include <WiFi.h>
#include <WebServer.h>
#include "state.h"
#include "eeprom_func.h"

#ifndef API_H
#define API_H

#define WIFI_ATTEMPTS 50

#define AP_SSID "MountainLightSetup"
#define AP_PASS "mountain1"

void init_api(void* parameter);
bool init_EEPROM();
void init_connection(bool eeprom_loaded);
void init_webserver();

void serve();
void handleHome();
void handleConfig();
void handleNotFound();
void handleNetworkConfig();
void handleSetState();
void handleRestart();

#endif