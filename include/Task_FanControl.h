#ifndef TASK_FAN_CONTROL_H
#define TASK_FAN_CONTROL_H

#include "Task_TempHumidMonitor.h"
#include <Arduino.h>

/**
 * Fan is broken so Serial Monitor is used as stand in
 */

// #define IN_A_FAN_PIN 25
// #define IN_B_FAN_PIN 26

void TaskFanControl(void*);

#endif