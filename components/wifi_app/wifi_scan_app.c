#include <appcontext.h>
#include <wifimanager.h>
#include "painter.h"
#include "hwcontext.h"
#include "wifimanager.h"
#include "ui.h"

#define STATUS_SCANNING 0
#define STATUS_NO_AP_FOUND 1
#define STATUS_SHOW_AP 2


#define STATUS_COMPLETED 255

static void wait_menu_key_press(void *hwcontext)
{
    char c;
    int pressed;
    do {
        struct timespec ts;
        c = hwcontext_get_key_code(hwcontext, &pressed, &ts);
    } while ((c != 'M') || pressed);
}

uint8_t ui_status;
ScanResult_t* scan_result = 0;
int scan_result_count = 0;


static void on_scan_result(int cont, ScanResult_t *result) {
    ui_status = result == 0 ? STATUS_NO_AP_FOUND : STATUS_SHOW_AP;
    scan_result = result;
    scan_result_count = cont;
}

static void wifi_scanning(struct AppContext *appctx) {
    painter_draw_text(appctx->hwcontext, 15, 2, "Scanning...", PAINTER_FONT_REGULAR, PAINTER_BLACK);
}

static void wifi_no_ap_found(struct AppContext *appctx) {
    painter_draw_text(appctx->hwcontext, 15, 2, "No ap found.", PAINTER_FONT_REGULAR, PAINTER_BLACK);
}

static void wifi_display_scan_results(struct AppContext *appctx) {
    uint8_t current_row = 0;
    for(int i = 0; i < scan_result_count; i++) {
        painter_draw_bounded_text(appctx->hwcontext, 0, current_row++, PAINTER_SCREEN_WIDTH,
                                  current_row * PAINTER_SCREEN_WIDTH, scan_result[i].ssid, PAINTER_FONT_REGULAR,
                                  PAINTER_BLACK);
    }
    wait_menu_key_press(appctx->hwcontext);
}

void wifi_scan_app(struct AppContext *appctx) {

    void *hwctx = appctx->hwcontext;
    void *wifimgr = hwcontext_get_wifi_manager(hwctx);

    ui_status = STATUS_SCANNING;
    wifi_manager_perform_scan(wifimgr, on_scan_result);

    while (ui_status != STATUS_COMPLETED) {
        painter_clear_screen(hwctx);
        switch(ui_status){
            case STATUS_SCANNING:
                wifi_scanning(appctx);
                break;
            case STATUS_NO_AP_FOUND:
                wifi_no_ap_found(appctx);
                break;
            case STATUS_SHOW_AP:
                wifi_display_scan_results(appctx);
                break;
        }
        hwcontext_delay_ms(hwctx, 30);
    }

    // Clear the heap
    free(scan_result);
}
