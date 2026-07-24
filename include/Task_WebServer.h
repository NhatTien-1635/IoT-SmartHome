#ifndef TASK_WIFI_H
#define TASK_WIFI_H

#include "Global.h"

void TaskWebServer(void*);

void SetUpAP();
void HandleWiFiEvent(WiFiEvent_t);

void HandleRoot();
void HandleSave();

void SetUpSTA();

void SaveWifiCredentials();
bool LoadWifiCredentials();
void ClearWifiCredentials();

void SetUpServerModeAP();
void SetUpServerModeSTA();

void MountLittleFS();
#endif