#pragma once
#include "includes.h"
#include <stdint.h>

// Function to write data to EEPROM /
void EEPROM_write(uint16_t uiAddress, uint8_t ucData);

// Functions to read data from EEPROM /
uint8_t EEPROM_read_uint8(uint16_t uiAddress);
uint16_t EEPROM_read_uint16(uint16_t uiAddress1, uint16_t uiAddress2);
uint32_t EEPROM_read_uint32(uint16_t uiAddress1, uint16_t uiAddress2, uint16_t uiAddress3, uint16_t uiAddress4);
