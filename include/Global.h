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

#define LED_PIN 2

#define DHT_DATA_PIN 18
#define DHT_TYPE DHT22

#define AP_SSID "ESP32-AccessPoint"
#define AP_PASS "12345678"

extern SemaphoreHandle_t dht_semaphore;
extern float temperature;
extern float humid;

extern int debug_timer;


#endif