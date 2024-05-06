#ifndef EEPROM_H
#define EEPROM_H

#include <avr/io.h>
#include <stdint.h>

// Function to write data to EEPROM /
void EEPROM_write(uint8_t uiAddress, unsigned char ucData);

// Function to read data from EEPROM /
unsigned char EEPROM_read(unsigned int uiAddress);

#endif // EEPROM_H 