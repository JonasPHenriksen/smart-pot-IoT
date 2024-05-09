#include "wifi.h"
#include "EEPROM_promter.h"
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Arduino.h>
#include "tcp_command_receiver.h"
#include "smart_pot.h"

unsigned long interval = 1000;
unsigned long previousMillis = 0;
unsigned long counter = 0;
int buttonState = 0;
const int buttonPin = 2;    // Pin connected to the external button
const int ledPin = 13;      // Pin connected to the LED (built-in LED for Arduino Mega)

void setup() {
  wifi_init();
  smartPotInit();
  pinMode(buttonPin, INPUT_PULLUP);  // Set button pin as input with pull-up resistor
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // Read the state of the button
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    // Button is pressed, change the interval
    interval = 1000;  // Change the interval to 1000 milliseconds
  }

  if (buttonState == LOW) {
    // Button is pressed, change the interval
    interval = 2000;  // Change the interval to 2000 milliseconds
  }
  

  // Check if it's time to run the method
  if (currentMillis - previousMillis >= interval) {
    // Calculate the actual elapsed time
    unsigned long elapsedTime = currentMillis - previousMillis;
    
    // Update the previous time to the current time
    previousMillis = currentMillis;
    
    // Increment the counterw
    counter++;
    // Turn on the LED
    digitalWrite(ledPin, HIGH);
    
    // Delay for a short duration
    delay(50);
    
    // Turn off the LED
    digitalWrite(ledPin, LOW);

    char* runAndCycle();

  }



    if (buttons_1_pressed() && buttons_2_pressed()) {
      playBuzzer(SONG_LOW_WATER_LEVEL);
      return;
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


char* runAndCycle() {
    // Implement your logic here
    // Example:
    uint32_t watered = tryWater();
    uint32_t moisture = getMoisture();
    uint32_t waterLevel = getWaterLevel();

    // Assuming you have a character array declared within the function
    static char result[50];  // Adjust the size as needed
    // Populate the result array with data or messages
    sprintf(result, "Watered: %d, Moisture: %d, Water Level: %d", watered, moisture, waterLevel);

    // Return a pointer to the result array
    return result;
}



