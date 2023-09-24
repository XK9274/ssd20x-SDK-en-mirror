#ifndef _WIFI_CONFIG_H_
#define _WIFI_CONFIG_H_
#include "mi_common_datatype.h"
#include "mi_wlan.h"
typedef void (*wifi_cb_t)(void *arg, void *req);

//A wifi configuration thread will be created. Actions to handle wifi blocking
int wifi_init(wifi_cb_t open_cb, wifi_cb_t state_cb);

void wifi_scan(wifi_cb_t cb, void *arg);
void wifi_connect(char *ssid, char *pwd);
void wifi_disconnect(wifi_cb_t cb, void *arg);

//Call in a loop in the main thread. Function: Determine whether there is a callback function application. Only by calling the callback function can we ensure that it is the callback function called by the main thread.
void wifi_mastar_run();
#endif