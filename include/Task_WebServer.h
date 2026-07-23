#ifndef TASK_WIFI_H
#define TASK_WIFI_H

#include "Global.h"

void TaskWebServer(void*);

void SetUpAP();
void HandleWiFiEvent(WiFiEvent_t);

void HandleRoot();

void SetUpSTA();

void ListLittleFSFiles();
#endif