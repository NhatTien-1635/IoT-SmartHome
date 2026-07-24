#include "Task_WebServer.h"

static WebServer web_server(80);
static DNSServer dns_server;

static bool dns_active = false;
static bool pending_connect = false;

static String ssid;
static String pass;

static Preferences preference;

void TaskWebServer(void* parameter) {
    if (LoadWifiCredentials()) {
        Serial.println("\nWifi found! Attempting to connect to: " + ssid);
        SetUpSTA();
    }
    else {
        Serial.println("\nWifi not found! Starting Access Point mode at: " + String(AP_SSID) + ", Password: " + String(AP_PASS));
        SetUpAP();
    }

    while (1) {
        if (dns_active) {
            dns_server.processNextRequest();
        }

        web_server.handleClient();

        if (pending_connect) {
            vTaskDelay(500);
            SetUpSTA();
            pending_connect = false;
        }

        vTaskDelay(10);
    }

}

void SetUpAP() {
    WiFi.onEvent(HandleWiFiEvent);

    WiFi.mode(WIFI_AP);
    WiFi.softAP(AP_SSID, AP_PASS);

    SetUpServerModeAP();

    Serial.println("\nStarting ACCESS POINT mode! Default IP: " + WiFi.softAPIP().toString());
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

void HandleSave() {
    if (web_server.hasArg("ssid")) {
        ssid = web_server.arg("ssid");
        pass = web_server.hasArg("pass") ? web_server.arg("pass") : "";

        web_server.send(200, "text/plain", "Credential recieved! Attempting to connect...");

        //Wait for response
        pending_connect = true;
    }
    else {
        web_server.send(404, "text/plain", "Missing SSID!");
    }
}

void SetUpSTA() {
    Serial.printf("\nStarting STATION Mode...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), pass.c_str());

    //10 second timeout
    int timeout = 1000;
    while (WiFi.status() != WL_CONNECTED && timeout > 0) {
        vTaskDelay(10);
        --timeout;
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi Connected!");
        Serial.println("\nLocal IP: " + WiFi.localIP().toString());

        SaveWifiCredentials();

        SetUpServerModeSTA();

        if (MDNS.begin("ESP32-StationMode")) {
            MDNS.addService("http", "tcp", 80);
            Serial.println("\nmDNS responder started!");
            Serial.println("Access at: http://ESP32-StationMode.local");
        }
    }
    else {
        Serial.println("\nConnection failed! Reverting to AP Mode");

        ClearWifiCredentials();

        SetUpAP();
    }
}

void SaveWifiCredentials() {
    preference.begin("wifi_config", false);
    preference.putString("ssid", ssid);
    preference.putString("pass", pass);
    preference.end();
}

bool LoadWifiCredentials() {
    preference.begin("wifi_config", true);
    ssid = preference.getString("ssid", "");
    pass = preference.getString("pass", "");
    preference.end();

    return ssid.length() > 0;
}

void ClearWifiCredentials() {
    preference.begin("wifi_config", false);
    preference.clear();
    preference.end();
}

void SetUpServerModeAP() {
    MountLittleFS();
    
    dns_server.start(53, "*", WiFi.softAPIP());
    dns_active = true;

    web_server.on("/", HandleRoot);
    web_server.on("/save", HandleSave);
    web_server.begin();

    //DNS send back here
    web_server.onNotFound(HandleRoot);
}

void SetUpServerModeSTA() {
    MountLittleFS();

    if (dns_active) {
        dns_server.stop();
        dns_active = false;
    }

    web_server.on("/", HandleRoot);
    web_server.on("/save", HandleSave);
    web_server.begin();

    //DNS send back here
    web_server.onNotFound(HandleRoot);
}

void MountLittleFS() {
    if (!LittleFS.begin(true)) {
        Serial.println("Error: LittleFS is not mounted!");
    }
    else {
        Serial.println("LittleFS mounted successfully!");
    }
}