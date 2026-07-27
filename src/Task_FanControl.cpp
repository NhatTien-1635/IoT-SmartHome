#include "Task_FanControl.h"

int log_timer = 0;

volatile int fan_state = FAN_STATE_OFF;
const char* fan_state_string[3] = { "OFF", "ON", "AUTO" };

void TaskFanControl(void* parameters) {
    vTaskDelay(1000);
    bool fan_running = false;
    while (1) {
        //Wait for signal from web server
        Serial.printf("\n[Time: %d] ", log_timer++);

        switch (fan_state) {
        case FAN_STATE_OFF:
            Serial.printf("MANUAL -> FAN OFF");
            break;

        case FAN_STATE_ON:
            Serial.printf("MANUAL -> FAN ON");
            break;

        case FAN_STATE_AUTO:
            Serial.printf("AUTO ");
            if (isnan(temperature[read_pointer]) || isnan(humid[read_pointer])) {
                Serial.printf("[DHT] Sensor read failed!");
                vTaskDelay(1000);
                continue;
            }

            Serial.printf("Temerature: %f, Humidity: %f", temperature[read_pointer], humid[read_pointer]);
            if (temperature[read_pointer] > 33 && humid[read_pointer] > 70) {
                fan_running = true;
            }

            if (temperature[read_pointer] < 30 && humid[read_pointer] < 67) {
                fan_running = false;
            }

            if (fan_running) {
                Serial.printf(" -> FAN ON");
            }
            else {
                Serial.printf(" -> FAN OFF");
            }

            break;

        default:
            Serial.printf("ERROR:DEFAULT CASE REACH? -> FAN OFF");
            break;
        }
        vTaskDelay(1000);
    }
}
