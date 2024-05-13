#include "smart_pot.h"

static uint32_t waterAmount;
static uint8_t moistLevel;
static uint16_t waterTankBottom;
static uint8_t machineGen;
static uint32_t machineId;

void smartPotInit() {
  moisture_init();
  hc_sr04_init();
  display_init();
  buttons_init();
  tone_init();
  pump_init();

  if  (EEPROM_read(100) == 1)

  waterAmount = EEPROM_read_uint8(2001);
  moistLevel = EEPROM_read_uint8(2002);
  waterTankBottom = EEPROM_read_uint16(2003, 2004);
}

void setWaterAmount(uint32_t water) {
  waterAmount = water;
  EEPROM_write(2001, waterAmount);
}

void setMoistLevel(uint8_t moist) {
  moistLevel = moist;
  EEPROM_write(2002, moistLevel);
}

uint32_t tryWater() {
  uint8_t moisture = getMoisture();
  if (moisture < moistLevel) {
    pump_run(waterAmount);
  } else {
    return NULL;
  }
  return waterAmount;
}

uint8_t getWaterLevel() {
  // 30 + 50 mm

  uint16_t waterLevel = hc_sr04_takeMeasurement() - 30;
  uint8_t waterLevelPercentage = percentage(waterLevel, 50);

  return waterLevelPercentage;
}

uint16_t calibrateWaterTank(){
  waterTankBottom = hc_sr04_takeMeasurement; 

  unsigned char byte1 = (waterTankBottom >> 8) & 0xFF; // Extract the first byte
  unsigned char byte2 = waterTankBottom & 0xFF; // Extract the second byte

  EEPROM_write(2003, byte1); // Write the first byte to EEPROM
  EEPROM_write(2004, byte2); // Write the second byte to EEPROM
}

uint8_t getMoisture() {
  uint16_t moisture = moisture_read();
  uint8_t moisture_percentage = percentage(moisture,1023);
  return moisture_percentage;
}

uint64_t getMachineId(){
  machineGen = EEPROM_read_uint8(1000);
  machineId = EEPROM_read_uint32(1001, 1002, 1003, 1004);

  uint64_t combined_value = (machineGen << 32) | machineId;
  
  return combined_value;
}

int percentage(int value, int ceiling){
    return (1 - ((float)value / ceiling)) * 100;
}


bool playBuzzer(song_enum_t song) {
  switch (song) {
    case SONG_LOW_WATER_LEVEL:
      tone_play(600, 150);
      tone_play(400, 150);
      
      break;
    case SONG_WATERING:
      tone_play(650, 150);
      tone_play(800, 150);
      break;
    case SONG_MOISTURE:
      tone_play(400, 150);
      tone_play(0, 150);
      tone_play(400, 150);
      break;
    case SONG_ERROR:
      tone_play(200, 150);
      tone_play(100, 150);
      tone_play(200, 150);
      break;
    default:
      return false;
  }
  return true;
}
