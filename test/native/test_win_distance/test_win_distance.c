#include "../test/fff.h"
#include "unity.h"
#include "hc_sr04.h"
#include <stdio.h>
#include <stdint.h>


uint8_t PINL;
uint8_t TCNT1;
uint8_t TCCR1B;
uint8_t PORTL;
uint8_t DDRL;
uint8_t DDRC;


DEFINE_FFF_GLOBALS
FAKE_VOID_FUNC(_delay_ms, int);


void setUp(void)
{
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_hc_sr04_init(void) {

    
    // Call the function to test
    hc_sr04_init();

    

TEST_ASSERT_EQUAL_UINT16(128, DDRL); // Ensure measurement is 0 when no echo signal is received
    // Verify that the relevant data direction registers are set correctly
}

void test_hc_sr04_takeMeasurement(void) {
    // Call the function to test

    hc_sr04_toggle(true);

    TEST_ASSERT_EQUAL_UINT16(128, PORTL); // Ensure measurement is 0 when no echo signal is received

    hc_sr04_toggle(false);

    TEST_ASSERT_EQUAL_UINT16(0, PORTL); // Ensure measurement is 0 when no echo signal is received
}

int main(void) {
    // Initialize the FFF framework
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_hc_sr04_init);
    RUN_TEST(test_hc_sr04_takeMeasurement);

    // End the tests
    return UNITY_END();
}