#include "Task_FanControl.h"

void TaskFanControl(void* parameters) {
    vTaskDelay(1000);
    bool fan_state = false;
    while (1) {
        //Wait for signal from 'temp/himid monitor' task
        if (xSemaphoreTake(dht_semaphore, portMAX_DELAY) == pdTRUE) {
            Serial.printf("\n[Time: %d] ", debug_timer++);

            if (isnan(temperature) || isnan(humid)) {
                Serial.printf("[DHT] Sensor read failed!");
                vTaskDelay(1000);
                continue;
            }

            Serial.printf("Temerature: %f, Humidity: %f", temperature, humid);
            if (temperature > 33 && humid > 70) {
                fan_state = true;
            }

            if (temperature < 30 && humid < 67) {
                fan_state = false;
            }

            if (fan_state) {
                Serial.printf("-> FAN ON");
            }
            else {
                Serial.printf(" -> FAN OFF");
            }
        }
        vTaskDelay(1000);
    }
}
