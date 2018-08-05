#ifndef _WIFI_MANAGER_
#define _WIFI_MANAGER_

#include <stdint.h>

enum ConnectionStatus {
    DISABLED,
    NOT_CONNECTED,
    CONNECTING,
    CONNECTED,
    GOT_IP
};

typedef struct WifiStationStatus {
    enum ConnectionStatus status;
    uint8_t ip[4];
    uint8_t gateway[4];
    uint8_t net_mask[4];
} WifiStationStatus_t;



void wifi_manager_set_enabled(void *wifi_manager, uint8_t enabled);

/**
 * Enabled/Disable the wifi station interface.
 * @param wifi_manager
 * @param enabled : True to enable, False to disable.
 */
void wifi_manager_set_enabled(void *wifi_manager, uint8_t enabled);

/**
 * Gets the current wifi station interface status
 * @param wifi_manager
 * @return A const reference to WifiStationStatus
 */
const WifiStationStatus_t* wifi_manager_get_wifi_status(void *wifi_manager);

#endif

