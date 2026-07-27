#include "Task_BlinkingLED.h"
#include "Task_TempHumidMonitor.h"
#include "Task_FanControl.h"
#include "Task_WebServer.h"


void setup() {
  Serial.begin(115200);

  xTaskCreate(TaskBlinkLED, "Blinking LED", 2048, NULL, 0, NULL);
  xTaskCreate(TaskMonitorDHT, "Monitor Temperature & Humidity", 2048, NULL, 2, NULL);
  xTaskCreate(TaskFanControl, "Fan Control", 2048, NULL, 3, NULL);
  xTaskCreate(TaskWebServer, "Hosting Web Server", 4096, NULL, 4, NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}