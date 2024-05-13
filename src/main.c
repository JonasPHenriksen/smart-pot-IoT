#include "wifi.h"
#include "tone.h"
#include "buttons.h"
#include "light.h"
#include "display.h"
#include "moisture.h"
#include "hc_sr04.h"
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Arduino.h>
#include "JsonConvert.h"
#include "uart_custom.h"


char messageBuffer[256];

void callback() {
  uartSend(messageBuffer);
}

int main() {
  uartInit(9600);
  moisture_init();
  hc_sr04_init();
  display_init();
  buttons_init();
  tone_init();
  wifi_init();

  display_setValues(1,2,3,4);

  wifi_command_join_AP("YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD");

  WIFI_ERROR_MESSAGE_t error = wifi_command_create_TCP_connection("13.53.174.85", 11000, &callback, &messageBuffer);
  //WIFI_ERROR_MESSAGE_t error = wifi_command_create_TCP_connection("192.168.43.227", 23, &callback, &messageBuffer);


  while(1) {
    if (buttons_1_pressed()) {
      uint8_t message = "Hello from Arduino over LAN\n";
      wifi_command_TCP_transmit(message, strlen(message));
      _delay_ms(2000);
    }
    if (buttons_2_pressed()) {
      
    const char* keys[] = {"MachineID", "WaterTankLevel", "MeasuredSoilMoisture", "AmountOfWatering"};
    const char* values[] = {"123","80.0", "30", "100"};
    // cJSON* json = rawDatasToJSON(4, keys, values);
    char* jsonString = rawDatasToJSONString(4, keys, values);

    //const char* jsonString = "{\"MachineID\": \"123\", \"WaterTankLevel\": 75.0, \"MeasuredSoilMoisture\": 22.0, \"AmountOfWatering\": 500}";
    //const char* jsonString = "{\"MachineID\": \"103\", \"WaterTankLevel\": 75, \"MeasuredSoilMoisture\": 22, \"AmountOfWatering\": 500}";



    // char* jsonString = cJSON_Print(json);
    wifi_command_TCP_transmit(jsonString, strlen(jsonString));


    // cJSON_Delete(json);
    free(jsonString);

    }
    if (buttons_3_pressed()) {
      uint16_t distance_value = hc_sr04_takeMeasurement();
      uint8_t moisture_value = moisture_read();
      char buffer[30];
      sprintf(buffer, "moisture: %d, distance: %d\n", moisture_value, distance_value);
      wifi_command_TCP_transmit(buffer, strlen(buffer));
    }
  }
  return 0;
}