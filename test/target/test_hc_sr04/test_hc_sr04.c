#include "unity.h"
#include "hc_sr04.h"
#include <stdint.h>
#include "includes.h"
#include <stdio.h>



void setUp(void)
{
    hc_sr04_init();
}

void tearDown(void)
{
}

void test_hc_sr04_is_measoring_between_5cm_and_3m()
{

    hc_sr04_init();
    _delay_ms(500);

      TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be between 5cm and 3m in 5       :1:_:PASS\n");
            display_setValues(17,17,17,5);
      _delay_ms(2000);
      TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be between 5cm and 3m in 4       :1:_:PASS\n");
            display_setValues(17,17,17,4);
      _delay_ms(2000);
      TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be between 5cm and 3m in 3       :1:_:PASS\n");
            display_setValues(17,17,17,3);
      _delay_ms(2000);
      TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be between 5cm and 3m in 2       :1:_:PASS\n");
            display_setValues(17,17,17,2);
      _delay_ms(2000);
      TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be between 5cm and 3m in 1       :1:_:PASS\n");
            display_setValues(17,17,17,1);
      _delay_ms(1000);

    uint16_t distance = hc_sr04_takeMeasurement();

    char message[1024];
    sprintf(message, "INFO! hc_sr04 measurement! Distance %d cm        :1:_:PASS\n", distance / 10);
    TEST_MESSAGE(message); // TEST_MESSAGE("m e s s a g e :1:_:PASS\n");

    TEST_ASSERT_TRUE_MESSAGE(50 < distance && 3000 > distance, message);
}

void test_hc_sr04_is_measoring_over_3m()
{
        hc_sr04_init();
    _delay_ms(500);
    uint16_t distance = hc_sr04_takeMeasurement();

      TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be grater than 3m in 5       :1:_:PASS\n");
            display_setValues(17,17,17,5);
      _delay_ms(2000);
      TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be grater than 3m in 4       :1:_:PASS\n");
            display_setValues(17,17,17,4);
      _delay_ms(2000);
      TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be grater than 3m in 3       :1:_:PASS\n");
            display_setValues(17,17,17,3);
      _delay_ms(2000);
      TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be grater than 3m in 2       :1:_:PASS\n");
            display_setValues(17,17,17,2);
      _delay_ms(2000);
      TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be grater than 3m in 1       :1:_:PASS\n");
            display_setValues(17,17,17,1);
      _delay_ms(2000);

    char message[1024];
    sprintf(message, "INFO! hc_sr04 measurement! Distance %d cm        :1:_:PASS\n", distance / 10);
    TEST_MESSAGE(message); // TEST_MESSAGE("m e s s a g e :1:_:PASS\n");

    TEST_ASSERT_TRUE_MESSAGE(3000 < distance, message); 
}

void test_hc_sr04_is_measoring_between_9cm_and_11cm()
{
        hc_sr04_init();
    _delay_ms(500);
    uint16_t distance = hc_sr04_takeMeasurement();
              TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be between 9cm to 11 cm in 5       :1:_:PASS\n");
            display_setValues(17,17,17,5);
      _delay_ms(2000);
          TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be between 9cm to 11 cm in 4       :1:_:PASS\n");
            display_setValues(17,17,17,4);
      _delay_ms(2000);
          TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be between 9cm to 11 cm in 3       :1:_:PASS\n");
            display_setValues(17,17,17,3);
      _delay_ms(2000);
          TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be between 9cm to 11 cm in 2       :1:_:PASS\n");
            display_setValues(17,17,17,2);
      _delay_ms(2000);
          TEST_MESSAGE("INFO! Let the distance from the hc_sr04 be between 9cm to 11 cm in 1       :1:_:PASS\n");
            display_setValues(17,17,17,1);
      _delay_ms(2000);

    char message[1024];
    sprintf(message, "INFO! hc_sr04 measurement! Distance %d cm        :1:_:PASS\n", distance / 10);
    TEST_MESSAGE(message); // TEST_MESSAGE("m e s s a g e :1:_:PASS\n");

    TEST_ASSERT_TRUE_MESSAGE(90 < distance && 110 > distance, message);
}


int main(void)
{
    UNITY_BEGIN();
    _delay_ms(500);
    RUN_TEST(test_hc_sr04_is_measoring_between_5cm_and_3m);
    TEST_MESSAGE("Remove everything in around 3 meter in fron of hc_sr04 sensor        :1:_:PASS\n");
    _delay_ms(2000);
    RUN_TEST(test_hc_sr04_is_measoring_over_3m);
    TEST_MESSAGE("Place something 10cm in front of the sensor        :1:_:PASS\n");
    RUN_TEST(test_hc_sr04_is_measoring_between_9cm_and_11cm);

    
    return UNITY_END();
}