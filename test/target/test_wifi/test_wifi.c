// Tests the Wifi module on target
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"
#define TCP_SERVER "192.168.56.1" // should be running and in echo mode for the test to pass. 
#define TCP_PORT 23

#include "unity.h"
#include "wifi.h"
#include <util/delay.h>
#include <avr/io.h>
#include <string.h>
#include <stdio.h>


void setUp(void)
{
 wifi_init();   
}

void tearDown(void)
{
}



void test_wifi_Connect_to_accessPoint_wrong_password()
{

    TEST_ASSERT_EQUAL(WIFI_FAIL, wifi_command_join_AP(WIFI_SSID, "vildfredd"));
}



int main(void)
{
    UNITY_BEGIN();
       _delay_ms(4000);
    RUN_TEST(test_wifi_Connect_to_accessPoint_wrong_password);

    return UNITY_END();
}