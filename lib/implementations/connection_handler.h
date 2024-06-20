#pragma once
#include "wifi.h"
#include <string.h>
#include "cJSON.h"

typedef void(*CUSTOM_CALLBACK_T)(cJSON* result);
WIFI_ERROR_MESSAGE_t connection_handler_init(char* SSID, char* password);

WIFI_ERROR_MESSAGE_t connection_handler_connect(char* ip, uint16_t port, CUSTOM_CALLBACK_T customCallback);
WIFI_ERROR_MESSAGE_t connection_handler_disconnect();
WIFI_ERROR_MESSAGE_t connection_handler_send(char* message);