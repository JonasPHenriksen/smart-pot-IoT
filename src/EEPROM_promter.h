#ifndef EEPROM_H
#define EEPROM_H

#include <avr/io.h>
#include <stdint.h>

// Function to write data to EEPROM /
void EEPROM_write(uint8_t uiAddress, uint8_t ucData);

// Function to read data from EEPROM /
uint8_t EEPROM_read(uint8_t uiAddress);

#endif // EEPROM_H 