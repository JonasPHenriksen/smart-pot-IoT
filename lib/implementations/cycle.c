#include "cycle.h"
#include "smart_pot.h"
#include "connection_handler.h"
#include "JsonConvert.h"
#include "aes_encrypt.h"

static bool* aesEncryption;
static CUSTOM_CALLBACK_T customCallback;

void cycle_init(
  bool _aesEncryption,
  CUSTOM_CALLBACK_T customCallback
) {
  aesEncryption = _aesEncryption;
  customCallback = customCallback;
}

void cycle_run() {
  uint8_t moisture = smart_pot_getMoisture();
  uint8_t waterLevel = smart_pot_getWaterLevel();
  uint8_t watered = smart_pot_tryWater(moisture);

  const char* keys[] = {"MachineID", "WaterTankLevel", "MeasuredSoilMoisture", "AmountOfWatering"};
  char amountOfWatering[32];
  char waterTankLevel[32];
  char measuredSoilMoisture[32];
  sprintf(amountOfWatering, "%d", watered);
  sprintf(waterTankLevel, "%d", waterLevel);
  sprintf(measuredSoilMoisture, "%d", moisture);

  const char* values[] = {"8000",waterTankLevel, measuredSoilMoisture, amountOfWatering};
  char* jsonString = rawDatasToJSONString(4, keys, values);
  
  uint8_t key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};  

  if (aesEncryption == true) {
    uint8_t encrypted_message = encrypt_data(key, (uint8_t*)jsonString, strlen(jsonString));

    connection_handler_send(encrypted_message);
    free(encrypted_message);
    free(jsonString);
  } else {
    connection_handler_send(jsonString);
    free(jsonString);
  }
}