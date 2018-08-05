#ifndef _SDLHWCONTEXT_H_
#define _SDLHWCONTEXT_H_

#include "linuxwifimanager.h"

struct HWContext
{
    int data_fd;
    void *screen_buf;
    WifiManager_t* wifi_manager;
};

#endif
