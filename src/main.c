#include "wifi.h"
#include "EEPROM_promter.h"
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Arduino.h>
// #include "tcp_command_receiver.h"
#include "smart_pot.h"
#include "uart.h"
#include "pump.h"

unsigned long interval = 1000;
unsigned long previousMillis = 0;
unsigned long counter = 0;
unsigned long intervalCounter = 0;
int buttonState = 0;
const int buttonPin = 2;    // Pin connected to the external button
const int ledPin = 13;      // Pin connected to the LED (built-in LED for Arduino Mega)

void setup() {
  uartInit(9600);
  wifi_init();
  smart_pot_init();
  // pinMode(buttonPin, INPUT_PULLUP);  // Set button pin as input with pull-up resistor
}

void cycle() {
  smart_pot_setMoistLevel(20);
  smart_pot_setWaterAmount(50);

  uint8_t watered = smart_pot_tryWater();
  uint8_t moisture = smart_pot_getMoisture();
  uint8_t waterLevel = smart_pot_getWaterLevel();

  // Send the data to the serial monitor
  char result[128];
  sprintf(result, "Watered: %d, Moisture: %d, Water Level: %d\n", watered, moisture, waterLevel);
  uartSend(result);
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // Check if it's time to run the method
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;    
    counter++;
    
    uint8_t digit1 = counter / 1000;       // Extract thousands digit
    uint8_t digit2 = (counter / 100) % 10; // Extract hundreds digit
    uint8_t digit3 = (counter / 10) % 10;  // Extract tens digit
    uint8_t digit4 = counter % 10;         // Extract units digit
    display_setValues(digit1, digit2, digit3, digit4);

    cycle();
  }
  intervalCounter--;
  if (intervalCounter < 0) {
    intervalCounter = 0;
  }

  if (buttons_1_pressed() && buttons_2_pressed()) {
    smart_pot_playBuzzer(SMART_POT_SONG_LOW_WATER_LEVEL);
    return;
  }
  if (buttons_1_pressed()) {
    // uint8_t message = "Hello from Arduino over LAN\n";
    // wifi_command_TCP_transmit(message, strlen(message));
    // _delay_ms(2000);
    // smart_pot_playBuzzer(SMART_POT_SONG_MOISTURE);
    // interval = 5000;
    // intervalCounter = 5000;
    smart_pot_calibrateWaterTank();
    // EEPROM_write(100, 24);
  }
  if (buttons_2_pressed()) {
    // tone_play_mario();
    smart_pot_playBuzzer(SMART_POT_SONG_WATERING);
    // uint16_t value = EEPROM_read(100);
    // uint8_t digit1 = value / 1000;       // Extract thousands digit
    // uint8_t digit2 = (value / 100) % 10; // Extract hundreds digit
    // uint8_t digit3 = (value / 10) % 10;  // Extract tens digit
    // uint8_t digit4 = value % 10;         // Extract units digit
  
    // display_setValues(digit1, digit2, digit3, digit4);
    interval = 9999;
    intervalCounter = 9999;
  }
  if (buttons_3_pressed()) {
    // smart_pot_playBuzzer(SMART_POT_SONG_ERROR);
    // uint16_t distance_value = hc_sr04_takeMeasurement();
    // uint8_t moisture_value = moisture_read();
    // char buffer[30];
    // sprintf(buffer, "moisture: %d, distance: %d\n", moisture_value, distance_value);
    // wifi_command_TCP_transmit(buffer, strlen(buffer));
    // EEPROM_write(100, 56);

    // char* result = runAndCycle();
    // uartSend(result);
  }
}