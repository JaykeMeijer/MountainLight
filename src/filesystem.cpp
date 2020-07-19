#include "filesystem.h"


File fsUploadFile;

void init_spiffs() {
    if (!SPIFFS.begin(true)) {
        Serial.println("confInit: Failed to mount file system");

        if (!SPIFFS.format()) {
            Serial.println("confInit: Format filesystem error");
            return;
        } else {
            Serial.println("confInit: Filesystem formatted");
        }
    }
}

void handleFileList(AsyncWebServerRequest *request) {
    if (!request->hasParam("dir")) {
        request->send(500, "text/plain", "BAD ARGS");
        return;
    }

    String path = request->getParam("dir")->value().c_str();

    File root = SPIFFS.open(path);
    path = String();

    String output = "[";
    if(root.isDirectory()){
        File file = root.openNextFile();
        while(file){
            if (output != "[") {
                output += ',';
            }
            output += "{\"type\":\"";
            output += (file.isDirectory()) ? "dir" : "file";
            output += "\",\"name\":\"";
            output += String(file.name()).substring(1);
            output += "\"}";
            file = root.openNextFile();
        }
    }
    output += "]";
    request->send(200, "text/json", output);
}

bool handleFileRead(String path, AsyncWebServerRequest *request) {
    // server->send(200, "text/html", "<form method=\"post\" enctype=\"multipart/form-data\"><input type=\"file\" name=\"name\"><input class=\"button\" type=\"submit\" value=\"Upload\"></form>");
    // return true;
    if (path.endsWith("/")) {
        path += "index.htm";
    }

    String contentType = getContentType(path);
    String pathWithGz = path + ".gz";
    if (exists(pathWithGz) || exists(path)) {
        if (exists(pathWithGz)) {
            path += ".gz";
        }
        // File file = SPIFFS.open(path, "r");
        Serial.println("File opened, streaming now");
        // server->streamFile(file, contentType);
        request->send(SPIFFS, path, contentType);

        Serial.println("Streaming done, closing");
        // file.close();
        Serial.println("Done streaming");
        return true;
    }
    Serial.println("No file");
    return false;
}

void handleFileCreate(AsyncWebServerRequest *request) {
    if (request->args() == 0) {
        return request->send(500, "text/plain", "BAD ARGS");
    }
    String path = request->arg((size_t)0).c_str();
    if (path == "/") {
        return request->send(500, "text/plain", "BAD PATH");
    }
    if (exists(path)) {
        return request->send(500, "text/plain", "FILE EXISTS");
    }
    File file = SPIFFS.open(path, "w");
    if (file) {
        file.close();
    } else {
        return request->send(500, "text/plain", "CREATE FAILED");
    }
    request->send(200, "text/plain", "");
    path = String();
}

void handleFileDelete(AsyncWebServerRequest *request) {
    if (request->args() == 0) {
        return request->send(500, "text/plain", "BAD ARGS");
    }
    String path = request->arg((size_t)0).c_str();
    if (path == "/") {
        return request->send(500, "text/plain", "BAD PATH");
    }
    if (!exists(path)) {
        return request->send(404, "text/plain", "FileNotFound");
    }
    SPIFFS.remove(path);
    request->send(200, "text/plain", "");
    path = String();
}

void handleFileUpload(AsyncWebServerRequest *request, String filename,
        size_t index, uint8_t *data, size_t len, bool final) {

    if (!index) {
        if (!filename.startsWith("/")) {
            filename = "/" + filename;
        }
        request->_tempFile = SPIFFS.open(filename, "w");
        filename = String();
    }

    if (len) {
        request->_tempFile.write(data, len);
    }

    if (final) {
        request->_tempFile.close();
        request->send(200, "text/plain", "OK!");
    }
}

/* Handling functions below */
bool exists(String path){
    bool yes = false;
    File file = SPIFFS.open(path, "r");
    if(!file.isDirectory()){
        yes = true;
    }
    file.close();
    return yes;
}

String getContentType(String filename) {
    if (filename.endsWith(".htm")) return "text/html";
    else if (filename.endsWith(".html")) return "text/html";
    else if (filename.endsWith(".css")) return "text/css";
    else if (filename.endsWith(".js")) return "application/javascript";
    else if (filename.endsWith(".png")) return "image/png";
    else if (filename.endsWith(".gif")) return "image/gif";
    else if (filename.endsWith(".jpg")) return "image/jpeg";
    else if (filename.endsWith(".ico")) return "image/x-icon";
    else if (filename.endsWith(".xml")) return "text/xml";
    else if (filename.endsWith(".pdf")) return "application/x-pdf";
    else if (filename.endsWith(".zip")) return "application/x-zip";
    else if (filename.endsWith(".gz")) return "application/x-gzip";
    return "text/plain";
}