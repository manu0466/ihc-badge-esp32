#ifndef _LINUX_WIFI_MANAGER_
#define _LINUX_WIFI_MANAGER_

#include "wifimanager.h"

typedef struct WifiManager {
    WifiStationStatus_t currentStatus;
} WifiManager_t;

WifiManager_t* wifi_manager_create();

#endif
