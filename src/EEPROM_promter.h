#ifndef EEPROM_H
#define EEPROM_H

#include <avr/io.h>

// Function to write data to EEPROM /
void EEPROM_write(unsigned int uiAddress, unsigned char ucData);

// Function to read data from EEPROM /
unsigned char EEPROM_read(unsigned int uiAddress);

#endif // EEPROM_H 