#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

#ifndef FILESYSTEM_H
#define FILESYSTEM_H

void init_spiffs();

void handleFileList(AsyncWebServerRequest *request);
bool handleFileRead(String path, AsyncWebServerRequest *request);
void handleFileCreate(AsyncWebServerRequest *request);
void handleFileDelete(AsyncWebServerRequest *request);
void handleFileUpload(AsyncWebServerRequest *request, String filename,
    size_t index, uint8_t *data, size_t len, bool final);

String getContentType(String filename);
bool exists(String path);


#endif