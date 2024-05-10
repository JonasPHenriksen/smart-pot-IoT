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

    testChanges();

    leds_turnOn(1);

    TEST_ASSERT_EQUAL_UINT8(112, PORTB);
    TEST_ASSERT_EQUAL_UINT8(240, DDRB);

    testChanges();

        leds_turnOn(2);

    TEST_ASSERT_EQUAL_UINT8(48, PORTB);
    TEST_ASSERT_EQUAL_UINT8(240, DDRB);

    testChanges();

        leds_turnOn(3);

    TEST_ASSERT_EQUAL_UINT8(16, PORTB);
    TEST_ASSERT_EQUAL_UINT8(240, DDRB);

    testChanges();

        leds_turnOn(4);

    TEST_ASSERT_EQUAL_UINT8(0, PORTB);
    TEST_ASSERT_EQUAL_UINT8(240, DDRB);

    testChanges();

        // Test turning off individual LEDs
    leds_turnOff(1);
        testChanges();
    TEST_ASSERT_EQUAL_UINT8(128, PORTB);
    leds_turnOff(2);
        testChanges();
    TEST_ASSERT_EQUAL_UINT8(192, PORTB);
    leds_turnOff(3);
        testChanges();
    TEST_ASSERT_EQUAL_UINT8(224, PORTB);
    leds_turnOff(4);
        testChanges();
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



void testChanges() {
    char message_ADMUX[1024];
sprintf(message_ADMUX, "INFO! PORTB value. %u       :1:_:PASS\n", PORTB);
TEST_MESSAGE(message_ADMUX);

char message_ADCSRA[1024];
sprintf(message_ADCSRA, "INFO! DDRB value. %u       :1:_:PASS\n", DDRB);
TEST_MESSAGE(message_ADCSRA);

char message_end[1024];
sprintf(message_end, "____________ END OF VALUES DISPLAY ______________        :1:_:PASS\n");
TEST_MESSAGE(message_end);

}