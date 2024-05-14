#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Arduino.h>
#include <util/delay.h>

#include "wifi.h"
#include "monitor.h"
#include "smart_pot.h"
#include "EEPROM_prompter.h"
#include "JsonConvert.h"

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long interval = 3 * 1000;
unsigned long counter = 0;

unsigned long requestTimeout = 5 * 1000;
uint8_t receivedResponse = false;

void cycle() {
  receivedResponse = false;

  uint8_t watered = smart_pot_tryWater();
  uint8_t moisture = smart_pot_getMoisture();
  uint8_t waterLevel = smart_pot_getWaterLevel();

  // Send the data to the serial monitor
  char result[128];
  sprintf(result, "Watered: %d, Moisture: %d, Water Level: %d\n", watered, moisture, waterLevel);
  monitor_send(result);
  
  const char* keys[] = {"MachineID", "WaterTankLevel", "MeasuredSoilMoisture", "AmountOfWatering"};
  char amountOfWatering[32];
  char waterTankLevel[32];
  char measuredSoilMoisture[32];
  sprintf(amountOfWatering, "%d", watered);
  sprintf(waterTankLevel, "%d", waterLevel);
  sprintf(measuredSoilMoisture, "%d", moisture);

  const char* values[] = {"999",waterTankLevel, measuredSoilMoisture, amountOfWatering};
  char* jsonString = rawDatasToJSONString(4, keys, values);
  wifi_command_TCP_transmit(jsonString, strlen(jsonString));
  free(jsonString);
}

char messageBuffer[256];
void callback() {
  receivedResponse = true;
  cJSON *result = cJSON_Parse(messageBuffer);
  if (result == NULL) {
    return;
  }

  cJSON *machine = cJSON_GetObjectItemCaseSensitive(result, "MachineID");
  if (strcmp(machine->valuestring, "999") != 0) {
    return;
  }

  cJSON *moisture = cJSON_GetObjectItemCaseSensitive(result, "SoilMinimumMoisture");
  smart_pot_setMoistLevel(moisture->valueint);

  cJSON *waterAmount = cJSON_GetObjectItemCaseSensitive(result, "AmountOfWaterToBeGiven");
  smart_pot_setWaterAmount(waterAmount->valueint);

  char buffington[300];
  sprintf(
    buffington, 
    "----- RECEIVED RESPONSE -----\n - ID: %s\n - Moisture: %d\n - Water Amount: %d\n", 
    machine->valuestring, 
    moisture->valueint,
    waterAmount->valueint
  );
  monitor_send(buffington);

  cJSON_Delete(result);
}

void setup() {
  monitor_init(9600);
  wifi_init();
  smart_pot_init();
  wifi_command_join_AP("YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD");
  // wifi_command_create_TCP_connection("13.53.174.85", 11000, &callback, messageBuffer);
  wifi_command_create_TCP_connection("192.168.43.221", 23, &callback, messageBuffer);
  
}

void loop() {
  // Get the current time
  currentMillis = millis();

  // Check if it's time to run the method
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    counter++;
    uint8_t digit1 = counter / 1000; // Extract thousands digit
    uint8_t digit2 = (counter / 100) % 10; // Extract hundreds digit
    uint8_t digit3 = (counter / 10) % 10; // Extract tens digit
    uint8_t digit4 = counter % 10; // Extract units digit
    display_setValues(digit1, digit2, digit3, digit4);

    cycle();

    // Wait for request response
    do {
      currentMillis = millis();
    } while (currentMillis - previousMillis < requestTimeout && !receivedResponse);
  }
  
  if (buttons_1_pressed() && buttons_2_pressed()) {
    smart_pot_playBuzzer(SMART_POT_SONG_LOW_WATER_LEVEL);
    return;
  }
  if (buttons_1_pressed()) {
    smart_pot_calibrateWaterTank();
  }
  if (buttons_2_pressed()) {
    smart_pot_playBuzzer(SMART_POT_SONG_WATERING);
  }
  if (buttons_3_pressed()) {
    
  }
}