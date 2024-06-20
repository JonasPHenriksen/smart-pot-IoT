#include "connection_handler.h"

char* messageBuffer[256];
CUSTOM_CALLBACK_T customCallback;
WIFI_ERROR_MESSAGE_t connection_handler_init(char* SSID, char* password) {
  wifi_init();
  return wifi_command_join_AP(SSID, password);
}

WIFI_ERROR_MESSAGE_t connection_handler_connect(char* ip, uint16_t port, CUSTOM_CALLBACK_T userCallback) {
  connection_handler_disconnect();
  customCallback = userCallback;
  return wifi_command_create_TCP_connection(ip, port, &callback, messageBuffer);
}
WIFI_ERROR_MESSAGE_t connection_handler_disconnect() {
  return wifi_command_close_TCP_connection();
}
WIFI_ERROR_MESSAGE_t connection_handler_send(char* message) {
  return wifi_command_TCP_transmit(message, strlen(message));
}

static void callback() {
  cJSON* result = cJSON_Parse(messageBuffer);
  if (result == NULL) {
    return;
  }

  cJSON* machine = cJSON_GetObjectItemCaseSensitive(result, "MachineID");
  if (strcmp(machine->valuestring, "8000") != 0) {
    return;
  }

  if (customCallback) {
    customCallback(&result);
  }

  cJSON_Delete(result);
}