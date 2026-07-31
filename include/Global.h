#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>

#include <LittleFS.h>

#include <WiFi.h>
#include <Preferences.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>

#define LED_PIN 2

#define DHT_DATA_PIN 18
#define DHT_TYPE DHT22

#define AP_SSID "ESP32-AccessPoint"
#define AP_PASS "12345678"

#define FAN_STATE_OFF 0
#define FAN_STATE_ON 1
#define FAN_STATE_AUTO 2

constexpr int next_fan_state[3] = {FAN_STATE_ON, FAN_STATE_AUTO, FAN_STATE_OFF};
extern const char* fan_state_string[3];

extern volatile int fan_state;

extern int read_pointer;
extern float temperature[2];
extern float humid[2];

extern int log_timer;

extern float inference;

#endif