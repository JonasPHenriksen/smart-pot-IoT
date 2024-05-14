#include "../test/fff.h"
#include "unity.h"
#include "EEPROM_prompter.h"
#include <stdio.h>
#include <stdint.h>

uint8_t EECR;
uint8_t EEPE;
uint8_t EEAR;
uint8_t EEDR;
uint8_t EEMPE;
uint8_t EERE;


DEFINE_FFF_GLOBALS
FAKE_VOID_FUNC(_delay_ms, int);


void setUp(void)
{
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_EEPROM_value(void) {

    EEPROM_write(0,-1);
    uint8_t result = EEPROM_read_uint8(0);

    TEST_ASSERT_EQUAL_UINT8(255,result);

    EEPROM_write(0,0);
    result = EEPROM_read_uint8(0);

    TEST_ASSERT_EQUAL_UINT8(0,result);

    EEPROM_write(0,1);
    result = EEPROM_read_uint8(0);

    TEST_ASSERT_EQUAL_UINT8(1,result);

    EEPROM_write(0,42);
    result = EEPROM_read_uint8(0);

    TEST_ASSERT_EQUAL_UINT8(42,result);

    EEPROM_write(0,255);
    result = EEPROM_read_uint8(0);

    TEST_ASSERT_EQUAL_UINT8(255,result);

    EEPROM_write(0,256);
    result = EEPROM_read_uint8(0);

    TEST_ASSERT_EQUAL_UINT8(0,result);

    EEPROM_write(0,NULL);
    result = EEPROM_read_uint8(0);

    TEST_ASSERT_EQUAL_UINT8(0,result);
}

void test_EEPROM_address(void) {

    EEPROM_write(-1,2);
    uint8_t result = EEPROM_read_uint8(4095);

    TEST_ASSERT_EQUAL_UINT8(2,result);

    EEPROM_write(0,3);
    result = EEPROM_read_uint8(0);

    TEST_ASSERT_EQUAL_UINT8(3,result);

    EEPROM_write(573,4);
    result = EEPROM_read_uint8(573);

    TEST_ASSERT_EQUAL_UINT8(4,result);

    EEPROM_write(4095,5);
    result = EEPROM_read_uint8(4095);

    TEST_ASSERT_EQUAL_UINT8(5,result);

    EEPROM_write(4096,6);
    result = EEPROM_read_uint8(0);

    TEST_ASSERT_EQUAL_UINT8(6,result);

    EEPROM_write(NULL,7);
    result = EEPROM_read_uint8(0);

    TEST_ASSERT_EQUAL_UINT8(7,result);


}




int main(void) {
    // Initialize the FFF framework
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_EEPROM_value);
    RUN_TEST(test_EEPROM_address);

    // End the tests
    return UNITY_END();
}