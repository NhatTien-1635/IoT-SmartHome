#ifndef TASK_TEMP_HUMID_MONITOR_H
#define TASK_TEMP_HUMID_MONITOR_H

#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHT_DATA_PIN 18
#define DHT_TYPE DHT22

SemaphoreHandle_t dht_semaphore;

static float temperature = 0.0;
static float humid = 0.0;

void TaskMonitorDHT(void*);

#endif