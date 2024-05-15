#include "smart_pot.h"
#include "../test/fff.h"
#include "unity.h"
#include <stdint.h>

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

void setUp(void)
{
    RESET_FAKE(_delay_ms);
    RESET_FAKE(moisture_init);
    RESET_FAKE(hc_sr04_init);
    RESET_FAKE(tone_init);
    RESET_FAKE(pump_init);
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


int main(void)
{
    // Initialize the FFF framework
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_init_methods_are_called);

    // End the tests
    return UNITY_END();
}