#include "../test/fff.h"
#include "unity.h"
#include "tone.h"
#include <stdio.h>
#include <stdint.h>

uint8_t TCNT2;
uint8_t PORTA;
uint8_t TCCR2B;
uint8_t TCCR2A;
uint8_t DDRA;


DEFINE_FFF_GLOBALS


void setUp(void)
{
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_tone_init(void) {
    
    tone_init();

    TEST_ASSERT_EQUAL_UINT16(128, DDRA); // Ensure measurement is 0 when no echo signal is received
    // Verify that the relevant data direction registers are set correctly
    
}


int main(void) {
    // Initialize the FFF framework
    UNITY_BEGIN();
    
    // Run the tests
    RUN_TEST(test_tone_init);

    // End the tests
    return UNITY_END();
}