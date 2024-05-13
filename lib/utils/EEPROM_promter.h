#pragma once

#include "includes.h"
#include <stdint.h>

// Function to write data to EEPROM /
void EEPROM_write(uint16_t uiAddress, uint8_t ucData);

// Function to read data from EEPROM /
uint8_t EEPROM_read(uint16_t uiAddress);