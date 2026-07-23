#include "Task_BlinkingLED.h"
#include "Task_TempHumidMonitor.h"
#include "Task_FanControl.h"

/**
 *  Initialize global variables 
 **/
SemaphoreHandle_t dht_semaphore = NULL;
float temperature = 0.0;
float humid = 0.0;
int timer = 0;

void setup() {
  Serial.begin(115200);
  dht_semaphore = xSemaphoreCreateBinary();

  xTaskCreate(TaskBlinkLED, "Blinking LED", 2048, NULL, 2, NULL);
  xTaskCreate(TaskMonitorDHT, "Monitor Temperature & Humidity", 2048, NULL, 2, NULL);
  xTaskCreate(TaskFanControl, "Fan Control", 2048, NULL, 3, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}