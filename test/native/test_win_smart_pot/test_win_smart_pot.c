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

FAKE_VOID_FUNC(tone_play, uint16_t, uint16_t);
FAKE_VOID_FUNC(pump_run, uint8_t);
FAKE_VOID_FUNC(EEPROM_write, uint16_t, uint16_t);
FAKE_VALUE_FUNC(uint8_t, EEPROM_read_uint8, uint16_t);
FAKE_VALUE_FUNC(uint16_t, EEPROM_read_uint16, uint16_t, uint16_t);
FAKE_VALUE_FUNC(uint32_t, EEPROM_read_uint32, uint16_t, uint16_t, uint16_t, uint16_t);
FAKE_VALUE_FUNC(uint16_t, moisture_read);
FAKE_VALUE_FUNC(uint16_t, hc_sr04_takeMeasurement);


extern uint8_t waterAmount;
extern uint8_t waterLevelPercentage;
extern uint8_t moistureLevel;
extern uint16_t waterTankBottom;
extern uint8_t machineGen;
extern uint32_t machineId;

void setUp(void)
{
    RESET_FAKE(_delay_ms);
    RESET_FAKE(moisture_init);
    RESET_FAKE(hc_sr04_init);
    RESET_FAKE(tone_init);
    RESET_FAKE(pump_init);
    RESET_FAKE(EEPROM_write)
    RESET_FAKE(EEPROM_read_uint16)
    RESET_FAKE(EEPROM_read_uint8)
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

void test_set_pot_moisterLevel() {

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


void test_smart_pot_tryWater() {
    
    moistureLevel = 0;
    waterLevelPercentage = 0;
    waterAmount = 0;

    TEST_ASSERT_EQUAL_UINT8(0,smart_pot_tryWater());



}

void test_smart_pot_getMoisture() {
    TEST_ASSERT_EQUAL(1, moisture_read_fake.call_count);
    TEST_ASSERT_EQUAL_UINT8(100, smart_pot_getMoisture());
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
    RUN_TEST(test_set_pot_waterAmount);
    RUN_TEST(test_set_pot_moisterLevel);
    RUN_TEST(test_smart_pot_tryWater);
    RUN_TEST(test_smart_pot_percentage);


    // End the tests
    return UNITY_END();
}