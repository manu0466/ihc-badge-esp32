#include "wifimanager.h"
#include "sdlhwcontext.h"
#include <stdlib.h>
#include <memory.h>

WifiManager_t* wifi_manager_create() {
    WifiManager_t* instance = malloc(sizeof(WifiManager_t));
    instance->currentStatus.status = DISABLED;
    memset(instance->currentStatus.ip, 0, 4);
    memset(instance->currentStatus.gateway, 0, 4);
    memset(instance->currentStatus.net_mask, 0, 4);
    return instance;
}

void wifi_manager_set_enabled(void *wifi_manager, uint8_t enabled) {
    WifiManager_t *wm = ((WifiManager_t*)wifi_manager);
    wm->currentStatus.status = enabled ? NOT_CONNECTED : CONNECTED;
    if(enabled) {
        wm->currentStatus.status = GOT_IP;
        // Fake ip
        wm->currentStatus.ip[0] = 192;
        wm->currentStatus.ip[1] = 168;
        wm->currentStatus.ip[2] = 0;
        wm->currentStatus.ip[3] = 23;
        // Fake gateway
        wm->currentStatus.gateway[0] = 192;
        wm->currentStatus.gateway[1] = 168;
        wm->currentStatus.gateway[2] = 0;
        wm->currentStatus.gateway[3] = 1;
        // Fake net mask
        wm->currentStatus.net_mask[0] = 255;
        wm->currentStatus.net_mask[1] = 255;
        wm->currentStatus.net_mask[2] = 255;
        wm->currentStatus.net_mask[3] = 0;
    } else {
        wm->currentStatus.status = DISABLED;
        memset(wm->currentStatus.ip, 0, 4);
        memset(wm->currentStatus.gateway, 0, 4);
        memset(wm->currentStatus.net_mask, 0, 4);
    }
}

const WifiStationStatus_t* wifi_manager_get_wifi_status(void *wifi_manager) {
    return &((WifiManager_t*)wifi_manager)->currentStatus;
}
