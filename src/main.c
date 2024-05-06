
#include "wifi.h"

#include "EEPROM_promter.h"
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Arduino.h>

#include "tcp_command_receiver.h"
#include "smart_pot.h"

int main() {
  wifi_init();
  smartPotInit();

  // wifi_command_join_AP("YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD");
  // tcp_listen("192.168.43.221", 23); // Listen for incoming messages

  while(1) {
    if (buttons_1_pressed() && buttons_2_pressed()) {
      playBuzzer(SONG_LOW_WATER_LEVEL);
      continue;
    }
    if (buttons_1_pressed()) {
      // uint8_t message = "Hello from Arduino over LAN\n";
      // wifi_command_TCP_transmit(message, strlen(message));
      // _delay_ms(2000);
      // playBuzzer(SONG_MOISTURE);
      EEPROM_write(100, 24);
    }
    if (buttons_2_pressed()) {
      // tone_play_mario();
      // playBuzzer(SONG_WATERING);
      uint16_t value = EEPROM_read(100);
      uint8_t digit1 = value / 1000;       // Extract thousands digit
      uint8_t digit2 = (value / 100) % 10; // Extract hundreds digit
      uint8_t digit3 = (value / 10) % 10;  // Extract tens digit
      uint8_t digit4 = value % 10;         // Extract units digit

      display_setValues(digit1, digit2, digit3, digit4);
    }
    if (buttons_3_pressed()) {
      // playBuzzer(SONG_ERROR);
      // uint16_t distance_value = hc_sr04_takeMeasurement();
      // uint8_t moisture_value = moisture_read();
      // char buffer[30];
      // sprintf(buffer, "moisture: %d, distance: %d\n", moisture_value, distance_value);
      // wifi_command_TCP_transmit(buffer, strlen(buffer));
      EEPROM_write(100, 56);
    }
  }
  return 0;
}