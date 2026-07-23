#include "Task_WebServer.h"

static WebServer web_server(80);
static DNSServer dns_server;

void TaskWebServer(void* parameter) {
    SetUpAP();

    while (1) {
        web_server.handleClient();
        vTaskDelay(10);
    }

}

void SetUpAP() {
    if (!LittleFS.begin(true)) {
        Serial.println("Error: LittleFS is not mounted!");
    }
    else {
        Serial.println("LittleFS mounted successfully!");
    }

    ListLittleFSFiles();

    WiFi.onEvent(HandleWiFiEvent);

    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);

    web_server.on("/", HandleRoot);
    web_server.begin();

    Serial.println("\nAccess Point mode activated! Default IP: " + WiFi.softAPIP().toString());
}

void HandleWiFiEvent(WiFiEvent_t event) {
    switch (event) {
    case ARDUINO_EVENT_WIFI_AP_STACONNECTED:
        Serial.println("\nA device has connected to the WiFi");
        break;

    case ARDUINO_EVENT_WIFI_AP_STADISCONNECTED:
        Serial.println("\nA device has disconnected to the WiFi");
        break;
    }
}

void HandleRoot() {
    if (LittleFS.exists("/index.html")) {
        File file = LittleFS.open("/index.html", "r");
        web_server.streamFile(file, "text/html");
        file.close();
    }
    else {
        web_server.send(404, "text/plain", "File not found");
    }
}

void ListLittleFSFiles() {
    Serial.println("--- Danh sách file trên LittleFS ---");
    File root = LittleFS.open("/");
    File file = root.openNextFile();
    while (file) {
        Serial.printf("File: %s | Size: %d bytes\n", file.name(), file.size());
        file = root.openNextFile();
    }
    Serial.println("-----------------------------------");
}