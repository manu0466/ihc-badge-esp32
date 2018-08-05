#ifndef _ESP32HWCONTEXT_
#define _ESP32HWCONTEXT_

#include <u8g2.h>
#include <time.h>
#include "esp32wifimanager.h"

struct HWContext
{
    u8g2_t *u8g2;
    void *key_events_queue;
    WifiManager_t *wifi_manager;
};

struct KeyEvent
{
    char key;
    int pressed;
    struct timespec timestamp;
};

#endif
