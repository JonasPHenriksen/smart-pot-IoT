#include "../test/fff.h"
#include "unity.h"
#include "JsonConvert.h"
#include <stdio.h>
#include <stdint.h>

DEFINE_FFF_GLOBALS
FAKE_VOID_FUNC(_delay_ms, int);
FAKE_VOID_FUNC(cJSON_Delete, cJSON*);
FAKE_VALUE_FUNC(cJSON*, cJSON_CreateObject);
FAKE_VALUE_FUNC(cJSON*, cJSON_AddStringToObject, cJSON*, const char*, const char*);
FAKE_VALUE_FUNC(char*, cJSON_PrintUnformatted, const cJSON*);
FAKE_VALUE_FUNC(cJSON*, cJSON_AddNumberToObject, cJSON*, const char*, double);
FAKE_VALUE_FUNC(double, atof, const char*);
FAKE_VALUE_FUNC(int, strcmp, const char*, const char*);


static cJSON dummy_json;
void setUp(void)
{
    RESET_FAKE(_delay_ms);
    RESET_FAKE(cJSON_Delete);
    RESET_FAKE(cJSON_CreateObject);
    RESET_FAKE(cJSON_AddStringToObject);
    RESET_FAKE(cJSON_PrintUnformatted);
    RESET_FAKE(cJSON_AddNumberToObject);
    RESET_FAKE(atof);
    RESET_FAKE(strcmp);
    
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_Json_conversion() {

  uint8_t moisture = 51;
  uint8_t watered = 54;
  uint8_t waterLevel = 68;

  // Send the data to the serial monitor
  char result[128];
  sprintf(result, "Watered: %d, Moisture: %d, Water Level: %d\n", watered, moisture, waterLevel);
  
  const char* keys[] = {"MachineID", "WaterTankLevel", "MeasuredSoilMoisture", "AmountOfWatering"};
  char amountOfWatering[32];
  char waterTankLevel[32];
  char measuredSoilMoisture[32];
  sprintf(amountOfWatering, "%d", watered);
  sprintf(waterTankLevel, "%d", waterLevel);
  sprintf(measuredSoilMoisture, "%d", moisture);



  const char* values[] = {"777",waterTankLevel, measuredSoilMoisture, amountOfWatering};
  char* jsonString = rawDatasToJSONString(4, keys, values);

  TEST_ASSERT_EQUAL(1,cJSON_CreateObject_fake.call_count);
      TEST_ASSERT_EQUAL(1,strcmp_fake.call_count);

      TEST_ASSERT_EQUAL(1,cJSON_AddStringToObject_fake.call_count);
    TEST_ASSERT_EQUAL(1,cJSON_AddNumberToObject_fake.call_count);

    
    TEST_ASSERT_EQUAL(1, atof_fake.call_count);


  
  TEST_ASSERT_EQUAL_STRING("expected", jsonString);
    
}


int main(void)
{
    // Initialize the FFF framework
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_Json_conversion);

    // End the tests
    return UNITY_END();
}