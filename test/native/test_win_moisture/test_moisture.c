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

DEFINE_FFF_GLOBALS


void setUp(void)
{
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_correct_moisture_driver_initialization()
{

    moisture_init();

    TEST_ASSERT_EQUAL(65, ADMUX);
    TEST_ASSERT_EQUAL(128, ADCSRA);
    TEST_ASSERT_EQUAL(8, ADCSRB);
    TEST_ASSERT_EQUAL(65, ADMUX);
    TEST_ASSERT_EQUAL(2, DIDR2);
}

void test_moisture_driver_read()
{

    uint8_t moistureLevel = moisture_read();

    TEST_ASSERT_EQUAL_UINT8(0, moistureLevel);
    TEST_ASSERT_EQUAL_UINT8(192, ADCSRA);
}


int main(void)
{
    // Initialize the FFF framework
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_correct_moisture_driver_initialization);
    RUN_TEST(test_moisture_driver_read);

    // End the tests
    return UNITY_END();
}