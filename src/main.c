#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Arduino.h>
#include <util/delay.h>

#include "wifi.h"
#include "monitor.h"
#include "smart_pot.h"
#include "EEPROM_prompter.h"
#include "JsonConvert.h"
#include <stdbool.h>
#include <AESLib.h>

#define AES_BLOCK_SIZE 16

unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
unsigned long interval = 3 * 1000;
unsigned long counter = 0;
bool aes_toggle = 0;

unsigned long requestTimeout = 5 * 1000;
uint8_t receivedResponse = false;

void print_hex(const char* label, const uint8_t* data, size_t len) {
    char buffer[3];
    monitor_send((char*)label);
    monitor_send(": ");
    for (size_t i = 0; i < len; i++) {
        snprintf(buffer, sizeof(buffer), "%02X ", data[i]);
        monitor_send(buffer);
    }
    monitor_send("\r\n");
}

void hex_to_string(const char* hex, char* output, size_t len) {
    for (size_t i = 0; i < len; i += 2) {
        char byte[3] = {hex[i], hex[i + 1], '\0'};
        output[i / 2] = (char)strtol(byte, NULL, 16);
    }
    output[len / 2] = '\0'; // Null-terminate the output string
}

void encrypt_string(const uint8_t* key, char* data) {
    size_t len = strlen(data);
    // Calculate padding length
    size_t pad_len = AES_BLOCK_SIZE - (len % AES_BLOCK_SIZE);
    if (pad_len != AES_BLOCK_SIZE) {
        // Pad with null bytes
        memset(data + len, 0, pad_len);
        len += pad_len;
    }
    // Encrypt in 16-byte blocks
    for (size_t i = 0; i < len; i += AES_BLOCK_SIZE) {
        aes128_enc_single(key, (void*)(data + i));
    }
}

// Function to decrypt a string
void decrypt_string(const uint8_t* key, char* data) {
    size_t len = strlen(data);
    // Decrypt in 16-byte blocks
    for (size_t i = 0; i < len; i += AES_BLOCK_SIZE) {
        aes128_dec_single(key, (void*)(data + i));
    }
    // Remove padding
    size_t pad_len = data[len - 1];
    if (pad_len < AES_BLOCK_SIZE && pad_len > 0) {
        data[len - pad_len] = '\0';
    }
}

void cycle() {
  receivedResponse = false;

  uint8_t watered = smart_pot_tryWater();
  uint8_t moisture = smart_pot_getMoisture();
  uint8_t waterLevel = smart_pot_getWaterLevel();

  // Send the data to the serial monitor
  char result[128];
  sprintf(result, "Watered: %d, Moisture: %d, Water Level: %d\n", watered, moisture, waterLevel);
  monitor_send(result);
  
  const char* keys[] = {"MachineID", "WaterTankLevel", "MeasuredSoilMoisture", "AmountOfWatering"};
  char amountOfWatering[32];
  char waterTankLevel[32];
  char measuredSoilMoisture[32];
  sprintf(amountOfWatering, "%d", watered);
  sprintf(waterTankLevel, "%d", waterLevel);
  sprintf(measuredSoilMoisture, "%d", moisture);

  const char* values[] = {"999",waterTankLevel, measuredSoilMoisture, amountOfWatering};
  char* jsonString = rawDatasToJSONString(4, keys, values);

  if (aes_toggle == 0)
  {
    //const char *json_data = "{\"name\": \"John\", \"age\": 30}";

    // AES encryption key (128 bits = 16 bytes)
    /*const uint8_t key[16] = {
        0x2b, 0x7e, 0x15, 0x16,
        0x28, 0xae, 0xd2, 0xa6,
        0xab, 0xf7, 0x97, 0x46,
        0x32, 0x36, 0xa8, 0x5a
    };*/

    // Determine the length of JSON data
    int json_len = strlen(jsonString);

    // Allocate memory for ciphertext
    unsigned char *ciphertext = (unsigned char *)malloc(json_len);
    if (ciphertext == NULL) {


    }

    // Encrypt the JSON data
 uint8_t key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    char data[17] = "0123456789012345"; // 16 chars + 1 for null terminator
  
        uint8_t iv[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Initialization vector

    monitor_send("Original: ");
    monitor_send(jsonString);
    monitor_send("\r\n");

    // Encrypt the JSON data
    encrypt_string(key, jsonString);

       // Print decrypted data as a string
    monitor_send("Encrypted (string): ");
    monitor_send(jsonString);
    monitor_send("\r\n");
    
    // Print encrypted data as hexadecimal
    print_hex("Encrypted Hex", (uint8_t*)jsonString, strlen(jsonString));

    // Decrypt the encrypted JSON data
    decrypt_string(key, jsonString);

    // Print decrypted data as a string
    monitor_send("Decrypted (string): ");
    monitor_send(jsonString);
    monitor_send("\r\n");



    //uint8_t data[128] = "{\"MachineID\":\"999\",\"WaterTankLevel\":32,\"MeasuredSoilMoisture\":62,\"AmountOfWatering\":0}"; // Data to encrypt
    //size_t data_len = strlen((char*)data);
  
        // Print original data
    /*print_hex("Original", jsonString, 16);

    size_t json_len = strlen(jsonString);
    uint8_t* json_data = (uint8_t*)jsonString;

    // Encrypt the data
    aes128_enc_single(key, jsonString);
    print_hex("Encrypted", jsonString, 16);

        // Print decrypted data as a string
    monitor_send("Encrypted (string): ");
    monitor_send((char*)jsonString);
    monitor_send("\r\n");

    // Decrypt the data
    aes128_dec_single(key, jsonString);
    print_hex("Decrypted", jsonString, 16);

    // Print decrypted data as a string
    monitor_send("Decrypted (string): ");
    monitor_send((char*)jsonString);
    monitor_send("\r\n");
  */
  /*   print_hex("Original", data, 16);

    // Encrypt the data
    aes128_enc_single(key, data);
    print_hex("Encrypted", data, 16);

    //aes128_enc_single(key, (void *)ciphertext);

    // Print the encrypted data
    //wifi_command_TCP_transmit((const char *)ciphertext, json_len);
    monitor_send("Ciphertext \n");
    monitor_send((char*) data);
    monitor_send("\nCiphertext \n");
    monitor_send("\n");
    


    // Decrypt the data
    aes128_dec_single(key, data);
    print_hex("Decrypted", data, 16);

    monitor_send("DeCiphertext \n");
    monitor_send((char*) data);
     monitor_send("\r\n");
    monitor_send("\nDeCiphertext \n");

*/
    // Clean up
    free(ciphertext);
  }

  else 
  {
    //wifi_command_TCP_transmit(jsonString, strlen(jsonString));
    monitor_send("Regular \n");
    monitor_send(jsonString);
    monitor_send("\nRegular \n");
    free(jsonString);

  }
 


}

char messageBuffer[256];
void callback() {
  receivedResponse = true;
  cJSON *result = cJSON_Parse(messageBuffer);
  if (result == NULL) {
    return;
  }

  cJSON *machine = cJSON_GetObjectItemCaseSensitive(result, "MachineID");
  if (strcmp(machine->valuestring, "999") != 0) {
    return;
  }

  cJSON *moisture = cJSON_GetObjectItemCaseSensitive(result, "SoilMinimumMoisture");
  smart_pot_setMoistLevel(moisture->valueint);

  cJSON *waterAmount = cJSON_GetObjectItemCaseSensitive(result, "AmountOfWaterToBeGiven");
  smart_pot_setWaterAmount(waterAmount->valueint);

  char buffington[300];
  sprintf(
    buffington, 
    "----- RECEIVED RESPONSE -----\n - ID: %s\n - Moisture: %d\n - Water Amount: %d\n", 
    machine->valuestring, 
    moisture->valueint,
    waterAmount->valueint
  );
  monitor_send(buffington);

  cJSON_Delete(result);
}

void setup() {
  monitor_init(9600);
  //wifi_init();
  smart_pot_init();
  //wifi_command_join_AP("YOUR_WIFI_SSID", "YOUR_WIFI_PASSWORD");
  // wifi_command_create_TCP_connection("13.53.174.85", 11000, &callback, messageBuffer);
  //wifi_command_create_TCP_connection("192.168.43.221", 23, &callback, messageBuffer);
  
}

void loop() {
  // Get the current time
  currentMillis = millis();

  // Check if it's time to run the method
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    counter++;
    uint8_t digit1 = counter / 1000; // Extract thousands digit
    uint8_t digit2 = (counter / 100) % 10; // Extract hundreds digit
    uint8_t digit3 = (counter / 10) % 10; // Extract tens digit
    uint8_t digit4 = counter % 10; // Extract units digit
    display_setValues(digit1, digit2, digit3, digit4);

    cycle();

    // Wait for request response
    do {
      currentMillis = millis();
    } while (currentMillis - previousMillis < requestTimeout && !receivedResponse);
  }
  
  if (buttons_1_pressed() && buttons_2_pressed()) {
    smart_pot_playBuzzer(SMART_POT_SONG_LOW_WATER_LEVEL);
    return;
  }
  if (buttons_1_pressed()) {
    smart_pot_calibrateWaterTank();
  }
  if (buttons_2_pressed()) {
    //smart_pot_playBuzzer(SMART_POT_SONG_WATERING);
      aes_toggle = 0;
  }
  if (buttons_3_pressed()) {
        aes_toggle = 1;
  }
}