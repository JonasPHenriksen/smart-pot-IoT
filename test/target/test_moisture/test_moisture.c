#include "unity.h"

#include "moisture.h"
#include <util/delay.h>

#include <stdio.h>
#include <stdint.h>

void setUp(void)
{
    moisture_init();
  
}
void tearDown(void) {}

void test_moisture_driver_read_dry()
{

       TEST_MESSAGE("INFO! Let the moisture sensor be dry in 3       :1:_:PASS\n");
            display_setValues(17,17,17,3);
      _delay_ms(1000);
       TEST_MESSAGE("INFO! Let the moisture sensor be dry in 2       :1:_:PASS\n");
            display_setValues(17,17,17,2);
      _delay_ms(1000);
       TEST_MESSAGE("INFO! Let the moisture sensor be dry in 1       :1:_:PASS\n");
            display_setValues(17,17,17,1);
      _delay_ms(1000);
  moisture_read();

  TEST_ASSERT_GREATER_OR_EQUAL(1000,moisture_read());
}

void test_moisture_driver_read_not_dry()
{
   moisture_init();
       moisture_read();
      TEST_MESSAGE("INFO! Make moisture sensore moist in 5       :1:_:PASS\n");
      display_setValues(17,17,17,5);
      _delay_ms(1000);
      TEST_MESSAGE("INFO! Make moisture sensore moist in 4       :1:_:PASS\n");
            display_setValues(17,17,17,4);
      _delay_ms(1000);
      TEST_MESSAGE("INFO! Make moisture sensore moist in 3       :1:_:PASS\n");
            display_setValues(17,17,17,3);
      _delay_ms(1000);
      TEST_MESSAGE("INFO! Make moisture sensore moist in 2       :1:_:PASS\n");
            display_setValues(17,17,17,2);
      _delay_ms(1000);
      TEST_MESSAGE("INFO! Make moisture sensore moist in 1       :1:_:PASS\n");
            display_setValues(17,17,17,1);
      _delay_ms(1000);

  //TEST_ASSERT(moisture_read() > 0);
  TEST_ASSERT_LESS_THAN(970, moisture_read());
}

void test_moisture_driver_read_ca_between_20_and_80()
{
      moisture_init();
       moisture_read();

      TEST_MESSAGE("INFO! Inset the moisture sensor into something moist in 3       :1:_:PASS\n");
      display_setValues(17,17,17,3);
      _delay_ms(2000);
      TEST_MESSAGE("INFO! Inset the moisture sensor into something moist in 2       :1:_:PASS\n");
            display_setValues(17,17,17,2);
      _delay_ms(2000);
      TEST_MESSAGE("INFO! Inset the moisture sensor into something moist in 1       :1:_:PASS\n");
            display_setValues(17,17,17,1);
      _delay_ms(2000);
      uint16_t moisture = moisture_read();
      char message[1024];
    sprintf(message, "INFO! Moisture sense! Moisture of %d        :1:_:PASS\n", moisture);
    TEST_MESSAGE(message); // TEST_MESSAGE("m e s s a g e :1:_:PASS\n");
    TEST_ASSERT_TRUE_MESSAGE(200 < moisture && 900 > moisture, message);
}

void test_moisture_driver_read_ca100precent()
{
      moisture_init();
       moisture_read();

      TEST_MESSAGE("INFO! Submerge the moisture sensore in water in 3       :1:_:PASS\n");
      display_setValues(17,17,17,3);
      _delay_ms(1000);
      TEST_MESSAGE("INFO! Submerge the moisture sensore in water in 2       :1:_:PASS\n");
            display_setValues(17,17,17,2);
      _delay_ms(1000);
      TEST_MESSAGE("INFO! Submerge the moisture sensore in water in 1       :1:_:PASS\n");
            display_setValues(17,17,17,1);
      _delay_ms(1000);
      uint16_t moisture = moisture_read();
      char message[1024];
    sprintf(message, "INFO! Moisture sense! Moisture of %d        :1:_:PASS\n", moisture);
    TEST_MESSAGE(message); // TEST_MESSAGE("m e s s a g e :1:_:PASS\n");
    TEST_ASSERT_TRUE_MESSAGE(0 <= moisture && 200 > moisture, message);
}


int main(void)
{
  UNITY_BEGIN();
  _delay_ms(500);
  RUN_TEST(test_moisture_driver_read_dry);
  RUN_TEST(test_moisture_driver_read_not_dry);
    _delay_ms(500);
  RUN_TEST(test_moisture_driver_read_ca100precent);
    _delay_ms(500);
  RUN_TEST(test_moisture_driver_read_ca_between_20_and_80);

  return UNITY_END();
}