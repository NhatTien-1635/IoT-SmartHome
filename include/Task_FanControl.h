#ifndef TASK_FAN_CONTROL_H
#define TASK_FAN_CONTROL_H

#include "Global.h"

/**
 * Fan is broken so Serial Monitor is used as stand in
 */

#define PWM_FREQ 25000
#define PWM_RESOLUTION 8

#define IN_A_FAN_PIN 25
#define IN_B_FAN_PIN 26

#define IN_A_CHANNEL 0
#define IN_B_CHANNEL 1

void TaskFanControl(void*);

#endif