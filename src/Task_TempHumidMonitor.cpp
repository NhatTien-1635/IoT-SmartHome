#include "Task_TempHumidMonitor.h"

void TaskMonitorDHT(void* parameters) {
    DHT dht(DHT_DATA_PIN, DHT_TYPE);
    dht.begin();

    while (1) {
        temperature = dht.readTemperature();
        humid = dht.readHumidity();

        //Send Semaphore to Fan
        xSemaphoreGive(dht_semaphore);

        vTaskDelay(1000);
    }
}