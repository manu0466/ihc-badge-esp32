#ifndef _WIFI_MANAGER_
#define _WIFI_MANAGER_

#include <stdint.h>

#define WIFI_OK 0
#define WIFI_ERR 1
#define WIFI_ERR_ALREADY_ENABLED 2
#define WIFI_ERR_ALREADY_DISABLED 3
#define WIFI_ERR_WIFI_DISABLED 4


enum ConnectionStatus {
    DISABLED,
    NOT_CONNECTED,
    CONNECTING,
    CONNECTED,
    GOT_IP
};

typedef struct {
    enum ConnectionStatus status;
    uint8_t ip[4];
    uint8_t gateway[4];
    uint8_t net_mask[4];
} WifiStationStatus_t;

typedef enum {
    WIFI_AUTH_OPEN = 0,         /**< authenticate mode : open */
    WIFI_AUTH_WEP,              /**< authenticate mode : WEP */
    WIFI_AUTH_WPA_PSK,          /**< authenticate mode : WPA_PSK */
    WIFI_AUTH_WPA2_PSK,         /**< authenticate mode : WPA2_PSK */
    WIFI_AUTH_WPA_WPA2_PSK,     /**< authenticate mode : WPA_WPA2_PSK */
    WIFI_AUTH_WPA2_ENTERPRISE,  /**< authenticate mode : WPA2_ENTERPRISE */
} WifiAuthMode_t;

typedef struct {
    uint8_t bssid[6];
    uint8_t ssid[33];
    uint8_t ssid_len;
    WifiAuthMode_t auth_mode;
    int8_t rssi;
} ScanResult_t;

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


/**
 * Starts a wifi scan.
 * @param wifi_manager
 * @param call_back: Function called when the scan completes.
 * @return Returns:
 *         - WIFI_OK if the scan successfully starts;
 *         - WIFI_ERR_WIFI_DISABLED if the wifi is disabled;
 *         - WIFI_ERR if the call_back params is == null.
 */
int wifi_manager_perform_scan(void *wifi_manager, void (*call_back)(int, ScanResult_t*));

/**
 * Stops a wifi scan.
 * @param wifi_manager
 * @return Returns:
 *         - WIFI_OK if the scan was successfully cancelled;
 *         - WIFI_ERR if no scan was started.
 */
int wifi_manager_stop_scan(void *wifi_manager);

#endif

