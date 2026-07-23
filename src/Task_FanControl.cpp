#include "Task_FanControl.h"

extern float temperature;
extern float humid;

void TaskFanControl(void* parameters) {
    while (1) {
        //Wait for signal from 'temp/himid monitor' task
        if (xSemaphoreTake(dht_semaphore, portMAX_DELAY) == pdTRUE) {
            if (isnan(temperature) || isnan(humid)) {
                Serial.println("[DHT] Sensor read failed!");
                vTaskDelay(1000);
                continue;
            }

            Serial.printf("Temerature: %f, Humidity: %f", temperature, humid);
            if (temperature > 32 || humid > 70) {
                Serial.println("-> FAN ON");
            }

            if (temperature < 28 || humid < 63) {
                Serial.println("-> FAN OFF");
            }
        }
        vTaskDelay(1000);
    }
}
