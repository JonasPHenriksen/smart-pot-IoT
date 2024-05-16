#include "../test/fff.h"
#include "unity.h"
#include "pump.h"
#include <stdio.h>
#include <stdint.h>

uint8_t DDRC;
uint8_t PORTC;

DEFINE_FFF_GLOBALS
FAKE_VOID_FUNC(_delay_ms, int);


void setUp(void)
{
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_correct_pump_driver_initialization() {

    pump_init();

    TEST_ASSERT_TRUE(DDRC & (1 << PUMP_OUTPUT_PIN));
}


void test_pump_driver_run() {

    pump_on();
    TEST_ASSERT_TRUE(PORTC & (1 << PUMP_OUTPUT_PIN)); // Verify pin is set high

    pump_off();
    TEST_ASSERT_FALSE(PORTC & (1 << PUMP_OUTPUT_PIN)); // Verify pin is set low after delay
}


int main(void)
{
    // Initialize the FFF framework
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_correct_pump_driver_initialization);
    RUN_TEST(test_pump_driver_run);

    // End the tests
    return UNITY_END();
}