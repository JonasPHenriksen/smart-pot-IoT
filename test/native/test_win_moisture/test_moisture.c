#include "../test/fff.h"
#include "unity.h"

#include "moisture.h"

#include <stdio.h>
#include <stdint.h>

uint8_t ADMUX;
uint8_t ADCSRA;
uint8_t ADCSRB;
uint8_t ADCL;
uint8_t ADCH;
uint8_t DIDR2;
uint8_t PORTK;
uint8_t DDRK;

DEFINE_FFF_GLOBALS

// Declare the function pointer for the mocked analogRead function
FAKE_VALUE_FUNC(uint8_t, fake_moisture_read);


void setUp(void)
{
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_correct_moisture_driver_initialization()
{
    // Perform the setup necessary for moisture_init()
    // (if any)

    // Call the function to be tested
    moisture_init();

    // Assert that the expected action has occurred
    TEST_ASSERT_EQUAL(65, ADMUX);
}

void test_moisture_driver_read_wet()
{
    // Perform any setup necessary for the test case
    uint8_t moistureLevel = moisture_read();
    
    // Assert that the expected action has occurred
    TEST_ASSERT_EQUAL_UINT8(100, moistureLevel);
}


int main(void)
{
    // Initialize the FFF framework
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_correct_moisture_driver_initialization);
    RUN_TEST(test_moisture_driver_read_wet);

    // End the tests
    return UNITY_END();
}
