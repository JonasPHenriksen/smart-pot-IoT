#include "../fff.h"
#include "unity.h"

#include "moisture.h"
#include <util/delay.h>

#include <stdio.h>
#include <stdint.h>

// variables used in moisture.c
uint8_t ADMUX;
/*uint8_t ADCSRA;
uint8_t ADCSRB;
uint8_t ADCL;
uint8_t ADCH;
uint8_t DIDR2;
uint8_t PORTK;
uint8_t DDRK;*/

//DEFINE_FFF_GLOBALS

void setUp(void)
{
  
}
void tearDown(void) {}


void test_correct_moisture_driver_initialization()
{
  moisture_init();

 TEST_ASSERT_EQUAL(65,ADMUX);

}

void test_moisture_driver_read_dry()
{
  moisture_init();
  moisture_read();

  TEST_ASSERT_EQUAL(0,moisture_read());
}

void test_moisture_driver_read_not_dry()
{
  //moisture_init();
  //moisture_read();
    display_init()
    _delay_ms(200)
      TEST_MESSAGE("INFO! Put fingers over moisture sensore so there is a connection in 5       :1:_:PASS\n");
      display_setValues(0005)
      _delay_ms(1000);
      TEST_MESSAGE("INFO! Put fingers over moisture sensore so there is a connection in 4       :1:_:PASS\n");
            display_setValues(0004)
      _delay_ms(1000);
      TEST_MESSAGE("INFO! Put fingers over moisture sensore so there is a connection in 3       :1:_:PASS\n");
            display_setValues(0003)
      _delay_ms(1000);
      TEST_MESSAGE("INFO! Put fingers over moisture sensore so there is a connection in 2       :1:_:PASS\n");
            display_setValues(0002)
      _delay_ms(1000);
      TEST_MESSAGE("INFO! Put fingers over moisture sensore so there is a connection in 1       :1:_:PASS\n");
            display_setValues(0001)
      _delay_ms(1000);

  //TEST_ASSERT(moisture_read() > 0);
  TEST_ASSERT_GREATER_THAN(0, moisture_read());
}



// Test that it sendst stuff nonBlocking. 

int main(void)
{
  UNITY_BEGIN();
  //RUN_TEST(test_correct_moisture_driver_initialization);
  RUN_TEST(test_moisture_driver_read_dry);
  RUN_TEST(test_moisture_driver_read_not_dry);


  return UNITY_END();
}