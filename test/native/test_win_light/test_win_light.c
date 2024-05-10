#include "../test/fff.h"
#include "unity.h"
#include "light.h"
#include <stdio.h>
#include <stdint.h>

// variables used in light.c
uint8_t ADMUX;
uint8_t ADCSRA;
uint8_t ADCSRB;
uint8_t ADCL;
uint8_t ADCH;
uint8_t DIDR2;
uint8_t PORTK;
uint8_t DDRK;

DEFINE_FFF_GLOBALS

void setUp(void)
{
  FFF_RESET_HISTORY();
}

void tearDown(void) {}


void test_light_init()
{

    light_init();

  TEST_ASSERT_EQUAL(71,ADMUX);
  TEST_ASSERT_EQUAL(135,ADCSRA);
  TEST_ASSERT_EQUAL(128,DIDR2);
}

void test_light_read()
{

  light_read();

  TEST_ASSERT_EQUAL(199,ADCSRA);

}

int main(void)
{
  UNITY_BEGIN();
  RUN_TEST(test_light_init);
  RUN_TEST(test_light_read);
  return UNITY_END();
}