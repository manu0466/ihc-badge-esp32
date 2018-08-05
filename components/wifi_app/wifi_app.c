#include "appcontext.h"
#include "hwcontext.h"
#include "painter.h"
#include "ui.h"
#include "wifimanager.h"
#include "hwcontext.h"

#define CHOICES_ENTRIES 4

#define ENABLE_ENTRY 0
#define DISABLE_ENTRY 1
#define STATUS_ENTRY 2
#define SCAN_ENTRY 3

void wifi_scan_app(struct AppContext *appctx);

void wifi_app(struct AppContext *appctx) {

    void *hwcontext = appctx->hwcontext;
    void *wifi_manager = hwcontext_get_wifi_manager(hwcontext);

    const char *const choices[] = {
            "Enable",
            "Disable",
            "Status",
            "Scan"
    };

    int choice;
    do {
        choice = ui_show_menu(hwcontext, CHOICES_ENTRIES, choices, 0);
        const WifiStationStatus_t *ws = wifi_manager_get_wifi_status(wifi_manager);
        switch(choice) {
            case ENABLE_ENTRY: {
                if (ws->status == DISABLED) {
                    wifi_manager_set_enabled(wifi_manager, 1);
                    ui_show_message(hwcontext, "Wi-Fi enabled");
                } else {
                    ui_show_message(hwcontext, "Wi-Fi already enabled");
                    hwcontext_delay_ms(hwcontext, 2000);
                    ui_show_menu(hwcontext, CHOICES_ENTRIES, choices, 0);
                }
            }break;
            case DISABLE_ENTRY: {
                if (ws->status != DISABLED) {
                    wifi_manager_set_enabled(wifi_manager, 0);
                    ui_show_message(hwcontext, "Wi-Fi disabled");
                } else {
                    ui_show_message(hwcontext, "Wi-Fi already disabled");
                }
            }break;
            case STATUS_ENTRY:
                switch(ws->status) {
                    case DISABLED:
                        ui_show_message(hwcontext, "Wi-Fi Disabled");
                        break;
                    case NOT_CONNECTED:
                        ui_show_message(hwcontext, "Not connected");
                        break;
                    case CONNECTING:
                        ui_show_message(hwcontext, "Connecting...");
                        break;
                    case CONNECTED:
                        ui_show_message(hwcontext, "Connected");
                        break;
                    case GOT_IP:
                        ui_show_message(hwcontext, "Got ip!");
                        break;
                }
                break;
            case SCAN_ENTRY:
                wifi_scan_app(appctx);
                break;
        }
    } while (choice >= 0);

}
