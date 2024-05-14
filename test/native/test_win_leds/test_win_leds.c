#include "../test/fff.h"
#include "unity.h"
#include "leds.h"
#include <stdio.h>
#include <stdint.h>

uint8_t PORTB;
uint8_t DDRB;


DEFINE_FFF_GLOBALS
FAKE_VOID_FUNC(_delay_ms, int);


void setUp(void)
{
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_leds_init(void) {

    TEST_ASSERT_EQUAL_UINT8(0, PORTB);
    TEST_ASSERT_EQUAL_UINT8(0, DDRB);


    leds_init();

    TEST_ASSERT_EQUAL_UINT8(240, PORTB);
    TEST_ASSERT_EQUAL_UINT8(240, DDRB);

    PORTB = 0;
    DDRB = 0;

    // Verify that the relevant data direction registers are set correctly
}

void test_leds_light(void) {
    
    TEST_ASSERT_EQUAL_UINT8(0, PORTB);
    TEST_ASSERT_EQUAL_UINT8(0, DDRB);

    PORTB = 240;
    DDRB = 240;

    leds_turn_on(1);

    TEST_ASSERT_EQUAL_UINT8(112, PORTB);
    TEST_ASSERT_EQUAL_UINT8(240, DDRB);

    leds_turn_on(2);

    TEST_ASSERT_EQUAL_UINT8(48, PORTB);
    TEST_ASSERT_EQUAL_UINT8(240, DDRB);

    leds_turn_on(3);

    TEST_ASSERT_EQUAL_UINT8(16, PORTB);
    TEST_ASSERT_EQUAL_UINT8(240, DDRB);

    leds_turn_on(4);

    TEST_ASSERT_EQUAL_UINT8(0, PORTB);
    TEST_ASSERT_EQUAL_UINT8(240, DDRB);

        // Test turning off individual LEDs
    leds_turn_off(1);

    TEST_ASSERT_EQUAL_UINT8(128, PORTB);
    leds_turn_off(2);

    TEST_ASSERT_EQUAL_UINT8(192, PORTB);
    leds_turn_off(3);

    TEST_ASSERT_EQUAL_UINT8(224, PORTB);
    leds_turn_off(4);

    TEST_ASSERT_EQUAL_UINT8(240, PORTB);
}

int main(void) {
    // Initialize the FFF framework
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_leds_init);
    RUN_TEST(test_leds_light);

    // End the tests
    return UNITY_END();
}