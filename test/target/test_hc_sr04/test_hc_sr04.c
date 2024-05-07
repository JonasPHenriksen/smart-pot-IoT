#include "unity.h"
#include "hc_sr04.h"
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>



void setUp(void)
{
}

void tearDown(void)
{
}

void test_hc_sr04_is_measoring_between_5cm_and_3m()
{
    hc_sr04_init();
    _delay_ms(500);
    uint16_t distance = hc_sr04_takeMeasurement();

    char message[1024];
    sprintf(message, "INFO! hc_sr04 measurement! Distance %d cm        :1:_:PASS\n", distance / 10);
    TEST_MESSAGE(message); // TEST_MESSAGE("m e s s a g e :1:_:PASS\n");

    TEST_ASSERT_TRUE_MESSAGE(50 < distance && 3000 > distance, message);
}


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_hc_sr04_is_measoring_between_5cm_and_3m);
    
    return UNITY_END();
}