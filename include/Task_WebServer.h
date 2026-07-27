#ifndef TASK_WIFI_H
#define TASK_WIFI_H

#include "Global.h"

void TaskWebServer(void*);

void SetUpWifi();

void SetUpAP();
void HandleWiFiEvent(WiFiEvent_t);

void HandleConfigWifi();
void HandleSave();
void HandleToggleFan();
void HandlingSendingSensorValue();

void SetUpSTA();

void SaveWifiCredentials();
bool LoadWifiCredentials();
void ClearWifiCredentials();

void SetUpServerModeAP();
void SetUpServerModeSTA();

void MountLittleFS();
#endif