#include "Task_TempHumidMonitor.h"
static int write_pointer = 0;
int read_pointer = 1;
float temperature[2]= {};
float humid[2] = {};

void TaskMonitorDHT(void* parameters) {
    vTaskDelay(1000);   
    DHT dht(DHT_DATA_PIN, DHT_TYPE);
    dht.begin();

    while (1) {
        temperature[write_pointer] = dht.readTemperature();
        humid[write_pointer] = dht.readHumidity();

        std::swap(write_pointer, read_pointer);

        vTaskDelay(1000);
    }
}