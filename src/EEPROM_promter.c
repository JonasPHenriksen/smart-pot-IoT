#include <avr/io.h>
#include <EEPROM_promter.h>

void EEPROM_write(uint16_t uiAddress, uint8_t ucData) {
  // Wait for completion of previous write /
  while(EECR & (1<<EEPE))
  ;

  // Set up address and Data Registers /
  EEAR = uiAddress;
  EEDR = ucData;
  // Write logical one to EEMPE /
  EECR |= (1<<EEMPE);
  // Start eeprom write by setting EEPE /
  EECR |= (1<<EEPE);
}

uint8_t EEPROM_read(uint16_t uiAddress) {
  // Wait for completion of previous write /
  while(EECR & (1<<EEPE))
  ;
  // Set up address register /
  EEAR = uiAddress;
  // Start eeprom read by writing EERE /
  EECR |= (1<<EERE);
  // Return data from Data Register /
  return EEDR;
}