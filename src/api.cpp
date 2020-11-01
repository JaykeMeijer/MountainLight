#include "api.h"

AsyncWebServer server(80);
DNSServer dnsServer;
bool as_ap = false;

void init_api(void* parameter) {
    delay(100);
    bool eeprom_success = init_EEPROM();

    load_state();

    init_connection(eeprom_success);
    init_webserver();
    init_mdns();

    init_spiffs();

    serve();
}

void init_connection(bool eeprom_loaded) {
    // Start WiFi mode. First, check if password in storage
    bool connected = true;

    // If EEPROM is loaded, use that to get WiFi credentials and try with that
    if (eeprom_loaded) {
        String ssid = eeprom_readString(EEPROM_SSID);
        String password = eeprom_readString(EEPROM_PASS);

        Serial.print("Trying to connect to ");
        Serial.println(ssid);

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
        WiFi.mode(WIFI_MODE_APSTA);

        WiFi.softAP(AP_SSID);
        as_ap = true;

        IPAddress myIP = WiFi.softAPIP();
        Serial.print("AP IP address: ");
        Serial.println(myIP);

        /* Setup the DNS server redirecting all the domains to the apIP */
        // dnsServer.setErrorReplyCode(DNSReplyCode::NoError);
        // dnsServer.start(DNS_PORT, "*", myIP);
    } else {
        Serial.print("Connected to existing WiFi at: ");
        Serial.println(WiFi.localIP());
    }
}

void init_webserver() {
    Serial.println("Initializing webserver");
    server.serveStatic("/", SPIFFS, "/");
    server.serveStatic("/config", SPIFFS, "/config.htm");
    server.on("/api/network", HTTP_GET, handleGetNetworkConfig);
    server.on("/api/network", HTTP_PUT, handleNetworkConfig);
    server.on("/api/restart", HTTP_POST, handleRestart);
    server.on("/api/state", HTTP_GET, handleGetState);
    server.on("/api/state", HTTP_PUT, handleSetState);

    // FS Browser
    server.on("/list", HTTP_GET, handleFileList);
    server.serveStatic("/edit", SPIFFS, "/edit.htm");
    server.on("/edit", HTTP_PUT, handleFileCreate);
    server.on("/edit", HTTP_DELETE, handleFileDelete);
    server.on("/edit", HTTP_POST, [](AsyncWebServerRequest *request){},
            [](AsyncWebServerRequest *request, const String& filename,
                size_t index, uint8_t *data, size_t len, bool final) {
        handleFileUpload(request, filename, index, data, len, final);
    });

    server.onNotFound([](AsyncWebServerRequest *request) {
        /* Try if there is a file with that name first */
        if (!handleFileRead(request->url(), request)) {
            handleNotFound(request);
        }
    });
    server.begin();
    Serial.println("Webserver is live");
}

void init_mdns() {
    //initialize mDNS service
    esp_err_t err = mdns_init();
    if (err) {
        printf("MDNS Init failed: %d\n", err);
        return;
    }

    //set hostname
    mdns_hostname_set(MDNS_NAME);
    //set default instance
    mdns_instance_name_set(MDNS_DESC);

    mdns_service_add(NULL, "_http", "_tcp", 80, NULL, 0);
    mdns_service_instance_name_set("_http", "_tcp", MDNS_DESC);
}

void serve() {
    // If running as AP, answer DNS requests. If outside of loop to limit
    // branching statement to once instead of every loop
    if (as_ap) {
        while(1) {
            // dnsServer.processNextRequest();

            delay(50);
        }
    } else {
        while(1) {
            delay(50);
        }
    }
}

void handleGetState(AsyncWebServerRequest *request) {
    String output = "{";
    output += "\"program\": " + String(read_program()) + "\"";
    output += "}";

    request->send(200, "application/json", output);
}

void handleSetState(AsyncWebServerRequest *request) {
    if (request->hasParam("program", true)) {
        set_program(request->getParam("program", true)->value().toInt());
    }
    request->send(200);
}

void handleNotFound(AsyncWebServerRequest *request) {
    if (as_ap) {
        request->redirect("/config");
    } else {
        request->send(404, "text/html", "<html><head><title>MountainLight</title></head><body><h1>Oops.. That does not exist</h1><a href=\"/\">Back home</a></body></html>");
    }
}

void handleGetNetworkConfig(AsyncWebServerRequest *request) {
    String output = "{";
    output += "\"is_ap\": " + String(as_ap ? "true" : "false") + ",";
    output += "\"stored\": \"" + eeprom_readString(EEPROM_SSID) + "\",";
    output += "\"connected\": " + String(WiFi.status() == WL_CONNECTED ? "true" : "false") + ",";
    output += "\"networks\": [";

    int numberOfNetworks = WiFi.scanNetworks();
    for (int i = 0; i < numberOfNetworks; i++) {
        output += "{\"ssid\": \"" + WiFi.SSID(i) + "\",";
        output += "\"rssi\": " + String(WiFi.RSSI(i));
        output += "}";
        if (i < numberOfNetworks - 1) {
            output += ',';
        }
    }

    output += "]}";

    request->send(200, "application/json", output);
}

void handleNetworkConfig(AsyncWebServerRequest *request) {
    if (request->hasParam("ssid", true)) {
        String ssid = request->getParam("ssid", true)->value();
        eeprom_writeString(EEPROM_SSID, ssid);
    }

    if (request->hasParam("pass", true)) {
        String pass = request->getParam("pass", true)->value();
        eeprom_writeString(EEPROM_PASS, pass);
    }

    request->send(200);
}

void handleRestart(AsyncWebServerRequest *request) {
    request->send(200);
    ESP.restart();
}