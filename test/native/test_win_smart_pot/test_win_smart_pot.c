#include "smart_pot.h"
#include "../test/fff.h"
#include "unity.h"
#include <stdint.h>

#define TEST

DEFINE_FFF_GLOBALS
FAKE_VOID_FUNC(_delay_ms, int);
FAKE_VOID_FUNC(moisture_init);
FAKE_VOID_FUNC(hc_sr04_init);
FAKE_VOID_FUNC(tone_init);
FAKE_VOID_FUNC(pump_init);
FAKE_VOID_FUNC(indicator_init);

FAKE_VOID_FUNC(indicator_on);
FAKE_VOID_FUNC(indicator_off);
FAKE_VOID_FUNC(tone_play, uint16_t, uint16_t);
FAKE_VOID_FUNC(pump_run, uint8_t);
FAKE_VOID_FUNC(EEPROM_write, uint16_t, uint8_t);
FAKE_VALUE_FUNC(uint8_t, EEPROM_read_uint8, uint16_t);
FAKE_VALUE_FUNC(uint16_t, EEPROM_read_uint16, uint16_t, uint16_t);
FAKE_VALUE_FUNC(uint32_t, EEPROM_read_uint32, uint16_t, uint16_t, uint16_t, uint16_t);
FAKE_VALUE_FUNC(uint16_t, moisture_read);
FAKE_VALUE_FUNC(uint16_t, hc_sr04_takeMeasurement);
// FAKE_VALUE_FUNC(bool, smart_pot_playBuzzer, SMART_POT_SONG_t);


void setUp(void)
{
    RESET_FAKE(_delay_ms);
    RESET_FAKE(moisture_init);
    RESET_FAKE(hc_sr04_init);
    RESET_FAKE(hc_sr04_takeMeasurement)
    RESET_FAKE(tone_init);
    RESET_FAKE(pump_init);
    RESET_FAKE(EEPROM_write);
    RESET_FAKE(EEPROM_read_uint16);
    RESET_FAKE(EEPROM_read_uint8);
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_init_methods_are_called() {

    smart_pot_init();
    TEST_ASSERT_EQUAL(1, moisture_init_fake.call_count);
    TEST_ASSERT_EQUAL(1, hc_sr04_init_fake.call_count);
    TEST_ASSERT_EQUAL(1, tone_init_fake.call_count);
    TEST_ASSERT_EQUAL(1, pump_init_fake.call_count);

}

void test_init_set_values() {
    waterAmount = EEPROM_read_uint8_fake.return_val = 50;
    moistureLevel = EEPROM_read_uint8_fake.return_val = 30;
    waterTankBottom = EEPROM_read_uint16_fake.return_val = 5301;
    TEST_ASSERT_EQUAL_UINT8(50,waterAmount);
    TEST_ASSERT_EQUAL_UINT8(30,moistureLevel);
    TEST_ASSERT_EQUAL_UINT16(5301,waterTankBottom);
}

void test_set_pot_waterAmount() {

    waterAmount = 0;

    smart_pot_setWaterAmount(37);
    TEST_ASSERT_EQUAL(37, waterAmount);
    smart_pot_setWaterAmount(-1);
    TEST_ASSERT_EQUAL(255, waterAmount);
    smart_pot_setWaterAmount(256);
    TEST_ASSERT_EQUAL(0, waterAmount);
    smart_pot_setWaterAmount(255);
    TEST_ASSERT_EQUAL(255, waterAmount);
    TEST_ASSERT_EQUAL(4, EEPROM_write_fake.call_count);

}

void test_set_pot_moistureLevel() {

    moistureLevel = 0;

    smart_pot_setMoistLevel(37);
    TEST_ASSERT_EQUAL(37, moistureLevel);
    smart_pot_setMoistLevel(-1);
    TEST_ASSERT_EQUAL(255, moistureLevel);
    smart_pot_setMoistLevel(256);
    TEST_ASSERT_EQUAL(0, moistureLevel);
    smart_pot_setMoistLevel(255);
    TEST_ASSERT_EQUAL(255, moistureLevel);
    TEST_ASSERT_EQUAL(4, EEPROM_write_fake.call_count);

}
void test_set_pot_state() {
  enableState = 0;
  smart_pot_setState(1);
  TEST_ASSERT_EQUAL(1, enableState);
  smart_pot_setState(5);
  TEST_ASSERT_EQUAL(1, enableState);
  smart_pot_setState(-4);
  TEST_ASSERT_EQUAL(0, enableState);
  smart_pot_setState(255);
  TEST_ASSERT_EQUAL(1, enableState);
  smart_pot_setState(-255);
  TEST_ASSERT_EQUAL(1, enableState);
}


void test_smart_pot_tryWater() {
  moistureLevel = 30;
  waterLevelPercentage = 0;
  waterAmount = 0;
  enableState = 0;
  TEST_ASSERT_EQUAL_UINT8(0, smart_pot_tryWater(30));
  TEST_ASSERT_EQUAL_UINT8(0, smart_pot_tryWater(255));
  TEST_ASSERT_EQUAL_UINT8(0, smart_pot_tryWater(-255));

  enableState = 1;
  // TEST moisture lower and higher than moistureLevel
  TEST_ASSERT_EQUAL_UINT8(0, smart_pot_tryWater(10));
  TEST_ASSERT_EQUAL_UINT8(0, smart_pot_tryWater(50));
  // TEST waterLevelPercentage lower and higher than SMARTPOT_MIN_WATERING_WATER_LEVEL_PERCENTAGE
  waterLevelPercentage = 0;
  TEST_ASSERT_EQUAL_UINT8(0, smart_pot_tryWater(10));
  waterLevelPercentage = 10;
  TEST_ASSERT_EQUAL_UINT8(0, smart_pot_tryWater(50));
  
  // TEST both true
  waterAmount = 5;
  TEST_ASSERT_EQUAL_UINT8(5, smart_pot_tryWater(10));
  // TEST_ASSERT_EQUAL_UINT8(1, smart_pot_playBuzzer_fake.call_count);
  // TEST_ASSERT_EQUAL(SMART_POT_SONG_WATERING, smart_pot_playBuzzer_fake.arg0_history[0]);
  // TEST_ASSERT_EQUAL(true, smart_pot_playBuzzer_fake.return_val_history[0]);
  TEST_ASSERT_EQUAL_UINT8(1, pump_run_fake.call_count);
  TEST_ASSERT_EQUAL_UINT8(5, pump_run_fake.arg0_history[0]);
  
  waterAmount = 255;
  TEST_ASSERT_EQUAL_UINT8(255, smart_pot_tryWater(10));
  // TEST_ASSERT_EQUAL_UINT8(2, smart_pot_playBuzzer_fake.call_count);
  // TEST_ASSERT_EQUAL(SMART_POT_SONG_WATERING, smart_pot_playBuzzer_fake.arg0_history[1]);
  // TEST_ASSERT_EQUAL(true, smart_pot_playBuzzer_fake.return_val_history[1]);
  TEST_ASSERT_EQUAL_UINT8(2, pump_run_fake.call_count);
  TEST_ASSERT_EQUAL_UINT8(255, pump_run_fake.arg0_history[1]);
}


void test_smart_pot_getWaterLevel() {
    
    moistureLevel = 0;
    waterLevelPercentage = 0;
    waterAmount = 0;
    hc_sr04_takeMeasurement_fake.return_val = 0; 
    
    waterTankBottom = 24;
    TEST_ASSERT_EQUAL_UINT8(9,smart_pot_getWaterLevel());

    hc_sr04_takeMeasurement_fake.return_val = -50; 
    TEST_ASSERT_EQUAL_UINT8(29,smart_pot_getWaterLevel());

    hc_sr04_takeMeasurement_fake.return_val = 50; 
    TEST_ASSERT_EQUAL_UINT8(92,smart_pot_getWaterLevel());

    waterTankBottom = -24;
    TEST_ASSERT_EQUAL_UINT8(90,smart_pot_getWaterLevel());

    hc_sr04_takeMeasurement_fake.return_val = -50; 
    TEST_ASSERT_EQUAL_UINT8(12,smart_pot_getWaterLevel());

    // Mock return values for hc_sr04_takeMeasurement
    hc_sr04_takeMeasurement_fake.return_val = 60;  // 60 - 30 = 30
    waterTankBottom = 60;  // limit = 60 - 30 = 30
    TEST_ASSERT_EQUAL_UINT8(0, smart_pot_getWaterLevel());

    hc_sr04_takeMeasurement_fake.return_val = 40;  // 40 - 30 = 10
    waterTankBottom = 60;  // limit = 60 - 30 = 30
    TEST_ASSERT_EQUAL_UINT8(66, smart_pot_getWaterLevel());

    hc_sr04_takeMeasurement_fake.return_val = 20;  // 20 - 30 = -10, should be 0
    waterTankBottom = 60;  // limit = 60 - 30 = 30
    TEST_ASSERT_EQUAL_UINT8(0, smart_pot_getWaterLevel());

    hc_sr04_takeMeasurement_fake.return_val = 90;  // 90 - 30 = 60
    waterTankBottom = 60;  // limit = 60 - 30 = 30, should be capped to 30
    TEST_ASSERT_EQUAL_UINT8(0, smart_pot_getWaterLevel());

    hc_sr04_takeMeasurement_fake.return_val = 30;  // 30 - 30 = 0
    waterTankBottom = 60;  // limit = 60 - 30 = 30
    TEST_ASSERT_EQUAL_UINT8(100, smart_pot_getWaterLevel());

    // Test edge case where waterTankBottom is less than 30
    hc_sr04_takeMeasurement_fake.return_val = 40;  // 40 - 30 = 10
    waterTankBottom = 20;  // limit = 20 - 30 = -10, should be 0
    TEST_ASSERT_EQUAL_UINT8(95, smart_pot_getWaterLevel());
}

void test_smart_pot_calibrateWaterTank() {
    hc_sr04_takeMeasurement_fake.return_val = 78;

    smart_pot_calibrateWaterTank();

    TEST_ASSERT_EQUAL(1,hc_sr04_takeMeasurement_fake.call_count);
    TEST_ASSERT_EQUAL(2, EEPROM_write_fake.call_count);

    unsigned char byte1 = EEPROM_write_fake.arg1_history[0];
    unsigned char byte2 = EEPROM_write_fake.arg1_history[1];

    TEST_ASSERT_EQUAL(78,byte2);
    TEST_ASSERT_EQUAL(0,byte1);

    hc_sr04_takeMeasurement_fake.return_val = 356;
    smart_pot_calibrateWaterTank();

    byte1 = EEPROM_write_fake.arg1_history[2];
    byte2 = EEPROM_write_fake.arg1_history[3];

    TEST_ASSERT_EQUAL(1,byte1);
    TEST_ASSERT_EQUAL(100,byte2);
}

void test_smart_pot_getMoisture() {
    TEST_ASSERT_EQUAL(1, moisture_read_fake.call_count);
    TEST_ASSERT_EQUAL_UINT8(100, smart_pot_getMoisture());
}

void test_smart_pot_playBuzzer() {
  TEST_ASSERT_EQUAL(true, smart_pot_playBuzzer(SMART_POT_SONG_ERROR));
  TEST_ASSERT_EQUAL(SMART_POT_SONG_ERROR, tone_play_fake.arg0_history[0]);

  TEST_ASSERT_EQUAL(true, smart_pot_playBuzzer(SMART_POT_SONG_WATERING));
  TEST_ASSERT_EQUAL(SMART_POT_SONG_WATERING, tone_play_fake.arg0_history[1]);

  TEST_ASSERT_EQUAL(true, smart_pot_playBuzzer(SMART_POT_SONG_MOISTURE));
  TEST_ASSERT_EQUAL(SMART_POT_SONG_MOISTURE, tone_play_fake.arg0_history[2]);

  TEST_ASSERT_EQUAL(true, smart_pot_playBuzzer(SMART_POT_SONG_LOW_WATER_LEVEL));
  TEST_ASSERT_EQUAL(SMART_POT_SONG_LOW_WATER_LEVEL, tone_play_fake.arg0_history[3]);

  TEST_ASSERT_EQUAL(10, tone_play_fake.call_count);
}

void test_smart_pot_percentage() {
    TEST_ASSERT_EQUAL_INT(50, percentage(50, 100));  // 50% of 100 is 50
    TEST_ASSERT_EQUAL_INT(25, percentage(75, 100));  // 75% of 100 is 75
    TEST_ASSERT_EQUAL_INT(100, percentage(0, 100));    // 0% of 100 is 0
    TEST_ASSERT_EQUAL_INT(0, percentage(100, 100));// 100% of 100 is 100
    TEST_ASSERT_EQUAL_INT(150, percentage(-50, 100));  // -50% of 100 is -50
    TEST_ASSERT_EQUAL_INT(-2147483648, percentage(1, 0));  // -50% of 100 is -50
    TEST_ASSERT_EQUAL_INT(100, percentage(0, 1));  // -50% of 100 is -50
    TEST_ASSERT_EQUAL_INT(86, percentage(-58, -429));  // -50% of 100 is -50
    TEST_ASSERT_EQUAL_INT(83, percentage(1, 6));    // 0% of 0 is 0
}

int main(void)
{
    // Initialize the FFF framework
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_init_methods_are_called);
    RUN_TEST(test_init_set_values);
    RUN_TEST(test_set_pot_state);
    RUN_TEST(test_set_pot_waterAmount);
    RUN_TEST(test_set_pot_moistureLevel);
    RUN_TEST(test_smart_pot_tryWater);
    RUN_TEST(test_smart_pot_percentage);
    RUN_TEST(test_smart_pot_getWaterLevel);
    RUN_TEST(test_smart_pot_calibrateWaterTank);


    // End the tests
    return UNITY_END();
}