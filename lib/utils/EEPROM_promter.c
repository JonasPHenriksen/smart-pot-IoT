#include "EEPROM_prompter.h"

void EEPROM_write(uint16_t uiAddress, uint8_t ucData) {
  // Wait for completion of previous write /
  //while () {}
  for (size_t i = 0; i < 8; i++)
  {
    EECR & (1<<EEPE);
  }
  

  // Set up address and Data Registers /
  EEAR = uiAddress;
  EEDR = ucData;
  // Write logical one to EEMPE /
  EECR |= (1<<EEMPE);
  // Start eeprom write by setting EEPE /
  EECR |= (1<<EEPE);
}

uint8_t EEPROM_read_uint8(uint16_t uiAddress) {
  // Wait for completion of previous write /
  //while (EECR & (1<<EEPE)) {}

  for (size_t i = 0; i < 8; i++)
  {
    EECR & (1<<EEPE);
  }
  // Set up address register /
  EEAR = uiAddress;
  // Start eeprom read by writing EERE /
  EECR |= (1<<EERE);

  // Return data from Data Register /
  return EEDR;
}

uint16_t EEPROM_read_uint16(uint16_t uiAddress1, uint16_t uiAddress2){
  uint8_t byte1 = EEPROM_read_uint8(uiAddress1);
  uint8_t byte2 = EEPROM_read_uint8(uiAddress2);

  uint16_t value = (byte1 << 8) | byte2;

  return value;
}

uint32_t EEPROM_read_uint32(uint16_t uiAddress1, uint16_t uiAddress2, uint16_t uiAddress3, uint16_t uiAddress4){
  uint8_t byte1 = EEPROM_read_uint8(uiAddress1);
  uint8_t byte2 = EEPROM_read_uint8(uiAddress2);
  uint8_t byte3 = EEPROM_read_uint8(uiAddress3);
  uint8_t byte4 = EEPROM_read_uint8(uiAddress4);

  uint32_t value = (byte1 << 24) | (byte2 << 16) | (byte3 << 8) | byte4;

  return value;
}