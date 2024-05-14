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
uint8_t CCR2B;
uint8_t CCR2A;


DEFINE_FFF_GLOBALS


void setUp(void)
{
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_tone_init(void) {
    
    TEST_ASSERT_EQUAL_UINT8(0, DDRA); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCCR2A); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, PORTA); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCNT2); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCCR2B); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, CCR2B); // Ensure measurement is 0 when no echo signal is received4    TEST_ASSERT_EQUAL_UINT8(0, CCR2B); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, CCR2A); // Ensure measurement is 0 when no echo signal is received




    tone_init();

    TEST_ASSERT_EQUAL_UINT8(128, DDRA); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCCR2A); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, PORTA); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCNT2); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCCR2B); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, CCR2B); // Ensure measurement is 0 when no echo signal is received4    TEST_ASSERT_EQUAL_UINT8(0, CCR2B); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, CCR2A); // Ensure measurement is 0 when no echo signal is received


}

void test_tone_play() {
        TEST_ASSERT_EQUAL_UINT8(128, DDRA); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCCR2A); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, PORTA); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCNT2); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCCR2B); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, CCR2B); // Ensure measurement is 0 when no echo signal is received4    TEST_ASSERT_EQUAL_UINT8(0, CCR2B); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, CCR2A); // Ensure measurement is 0 when no echo signal is received
        test_tone_player(392,500);
        TEST_ASSERT_EQUAL_UINT8(128, DDRA); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCCR2A); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, PORTA); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCNT2); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(5, TCCR2B); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, CCR2B); // Ensure measurement is 0 when no echo signal is received4    TEST_ASSERT_EQUAL_UINT8(0, CCR2B); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, CCR2A); // Ensure measurement is 0 when no echo signal is received
    test_tone_player(11,500);
        TEST_ASSERT_EQUAL_UINT8(128, DDRA); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCCR2A); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, PORTA); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, TCNT2); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(7, TCCR2B); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, CCR2B); // Ensure measurement is 0 when no echo signal is received4    TEST_ASSERT_EQUAL_UINT8(0, CCR2B); // Ensure measurement is 0 when no echo signal is received
    TEST_ASSERT_EQUAL_UINT8(0, CCR2A); // Ensure measurement is 0 when no echo signal is received

}


int main(void) {
    // Initialize the FFF framework
    UNITY_BEGIN();
    
    // Run the tests
    RUN_TEST(test_tone_init);
    RUN_TEST(test_tone_play);

    // End the tests
    return UNITY_END();
}