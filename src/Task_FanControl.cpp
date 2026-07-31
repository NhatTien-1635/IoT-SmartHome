#include "Task_FanControl.h"

int log_timer = 0;

volatile int fan_state = FAN_STATE_OFF;
const char* fan_state_string[3] = { "OFF", "ON", "AUTO" };

void TaskFanControl(void* parameters) {
    ledcSetup(IN_A_CHANNEL, PWM_FREQ, PWM_RESOLUTION);     //IN_A
    ledcSetup(IN_B_CHANNEL, PWM_FREQ, PWM_RESOLUTION);     //IN_B

    ledcAttachPin(IN_A_FAN_PIN, IN_A_CHANNEL);
    ledcAttachPin(IN_B_FAN_PIN, IN_B_CHANNEL);

    ledcWrite(IN_A_CHANNEL, 0);
    ledcWrite(IN_B_CHANNEL, 0);

    vTaskDelay(1000);
    bool fan_running = false;
    while (1) {
        //Wait for signal from web server
        Serial.printf("\n[Time: %d] ", log_timer++);

        switch (fan_state) {
        case FAN_STATE_OFF:
            Serial.printf("MANUAL -> FAN OFF");
            fan_running = false;
            break;

        case FAN_STATE_ON:
            Serial.printf("MANUAL -> FAN ON");
            fan_running = true;
            break;

        case FAN_STATE_AUTO:
            Serial.printf("AUTO ");
            if (isnan(temperature[read_pointer]) || isnan(humid[read_pointer])) {
                Serial.printf("[DHT] Sensor read failed!");
                vTaskDelay(1000);
                continue;
            }

            Serial.printf("Temerature: %f, Humidity: %f", temperature[read_pointer], humid[read_pointer]);
            if(inference < 0.5){
                fan_running = true;
            }
            else {
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

        ledcWrite(IN_A_CHANNEL, fan_running ? 255 : 0);
        vTaskDelay(1000);
    }
}
