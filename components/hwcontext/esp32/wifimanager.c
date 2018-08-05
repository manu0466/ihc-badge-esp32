#include "wifimanager.h"
#include "esp32hwcontext.h"
#include "esp32wifimanager.h"
#include <stdlib.h>
#include <string.h>

WifiManager_t* wifi_manager_create() {
    WifiManager_t* instance = malloc(sizeof(WifiManager_t));
    instance->currentStatus.status = DISABLED;
    memset(instance->currentStatus.ip, 0, 4);
    memset(instance->currentStatus.gateway, 0, 4);
    memset(instance->currentStatus.net_mask, 0, 4);
    return instance;
}

void wifi_manager_set_enabled(void *wifi_manager, uint8_t enabled) {
    ((WifiManager_t*)wifi_manager)->currentStatus.status = enabled ? NOT_CONNECTED : DISABLED;
}

const WifiStationStatus_t* wifi_manager_get_wifi_status(void *wifi_manager) {
    return &((WifiManager_t*)wifi_manager)->currentStatus;
}
