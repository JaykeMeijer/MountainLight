#include "api.h"

WebServer server(80);

void init_api(void* parameter) {
    delay(100);
    bool eeprom_success = init_EEPROM();

    load_state();

    init_connection(eeprom_success);
    init_webserver();

    serve();
}


void init_connection(bool eeprom_loaded) {
    // Start WiFi mode. First, check if password in storage
    bool connected = true;

    // If EEPROM is loaded, use that to get WiFi credentials and try with that
    if (eeprom_loaded) {
        String ssid = eeprom_readString(EEPROM_SSID);
        String password = eeprom_readString(EEPROM_PASS);

        WiFi.begin(ssid.c_str(), password.c_str());
        int attempt = 0;

        while (WiFi.status() != WL_CONNECTED) {
            if (WiFi.status() == WL_CONNECT_FAILED) {
                Serial.println("Connect failed, resetting WiFi connection");
                WiFi.disconnect(true);
                delay(100);
                WiFi.begin(ssid.c_str(), password.c_str());
            }

            if (attempt > WIFI_ATTEMPTS) {
                connected = false;
                break;
            }
            delay(500);
            Serial.println("Connecting to WiFi..");
            attempt++;
        }
    }

    // If failed to connect, start up access point instead.
    if(!connected) {
        Serial.println("Configuring access point...");
        WiFi.softAP(AP_SSID, AP_PASS);

        IPAddress myIP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(myIP);
    } else {
        Serial.print("Connected to existing WiFi at: ");
        Serial.println(WiFi.localIP());
    }
}

void init_webserver() {
    Serial.println("Initializing webserver");
    server.on("/", handleHome);
    server.on("/config", handleConfig);
    // server.on("/api", handleAPICall);
    server.on("/api/network", HTTP_PUT, handleNetworkConfig);
    server.on("/api/restart", HTTP_POST, handleRestart);
    server.on("/api/state", HTTP_PUT, handleSetState);

    server.onNotFound(handleNotFound);
    server.begin();
    Serial.println("Webserver is live");
}

void serve() {
    while(1) {
        server.handleClient();
        delay(50);
    }
}

void handleHome() {
    server.send(200, "text/html", "<html><head><title>MountainLight</title></head><body><a href=\"/config\">Config</a></body></html>");
}

void handleConfig() {
    server.send(200, "text/html", "<html><head><title>MountainLight</title></head><body>hi</body></html>");
}

void handleSetState() {
    if (server.hasArg("program")) {
        set_state(server.arg("program").toInt());
    }
    server.send(200);
}

void handleNotFound() {
    server.send(404, "text/html", "<html><head><title>MountainLight</title></head><body><h1>Oops.. That does not exist</h1><a href=\"/\">Back home</a></body></html>");
}

void handleNetworkConfig() {
    if (server.hasArg("ssid")) {
        String ssid = server.arg("ssid");
        eeprom_writeString(EEPROM_SSID, ssid);
    }

    if (server.hasArg("pass")) {
        String pass = server.arg("pass");
        eeprom_writeString(EEPROM_PASS, pass);
    }

    server.send(200);
}

void handleRestart() {
    server.send(200);
    ESP.restart();
}