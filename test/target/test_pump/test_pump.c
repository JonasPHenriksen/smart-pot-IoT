#include "includes.h"
#include "pump.h"

void setUp(void)
{
    pump_init();
    pir_init(pir_callback_func);
}
void tearDown(void) {}

uint8_t pir_callback_called = 0;
void pir_callback_func()
{
    pir_callback_called = 1;
}

void test_pir_if_it_calls_the_callback_function_in_20sec_time_after_activating_pump()
{
    _delay_ms(100);
    pump_run(20);

    pir_callback_called = 0;
    uint16_t timer = 0;
    while (!pir_callback_called && timer < 30)
    {
        _delay_ms(1000);
        timer++;
    }

    TEST_ASSERT_TRUE_MESSAGE(pir_callback_called, "It timed out");

    char message[1024];
    sprintf(message, "INFO! it took %d sec, before PIR registered something       :1:_:PASS\n", timer);
    TEST_MESSAGE(message); // TEST_MESSAGE("m e s s a g e :1:_:PASS\n"); // no : in the message
}

int main(void)
{
    UNITY_BEGIN();

    TEST_MESSAGE("INFO! wave your hand above the pir sensor after pump runs       :1:_:PASS\n"); // no : in the message
    RUN_TEST(test_pir_if_it_calls_the_callback_function_in_20sec_time_after_activating_pump);

    return UNITY_END();
}
