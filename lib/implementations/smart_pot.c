#include "smart_pot.h"

// DRIVERS
#include "tone.h"
#include "light.h"
#include "moisture.h"
#include "hc_sr04.h"
#include "pump.h"

// UTILS
#include "monitor.h"
#include "EEPROM_prompter.h"

#define SMARTPOT_WATER_AMOUNT_ADDR 2001
#define SMARTPOT_MOISTURE_LEVEL_ADDR 2002

#define SMARTPOT_WATER_TANK_BOTTOM_ADDR1 2003 //different addresses on purpose
#define SMARTPOT_WATER_TANK_BOTTOM_ADDR2 2004 //different addresses on purpose
#define SMARTPOT_ENABLE_STATE_ADDR 2005

#define SMARTPOT_MIN_WATERING_WATER_LEVEL_PERCENTAGE 5
#define SMARTPOT_LOW_WATER_LEVEL_PERCENTAGE 25


uint8_t waterAmount;
uint8_t waterLevelPercentage;
uint8_t moistureLevel;
uint16_t waterTankBottom;
uint8_t machineGen;
uint32_t machineId;
uint8_t enableState;

void smart_pot_init() {
  indicator_init();
  moisture_init();
  hc_sr04_init();
  tone_init();
  pump_init();

  // if (EEPROM_read(100) == 1)

  waterAmount = EEPROM_read_uint8(SMARTPOT_WATER_AMOUNT_ADDR);
  moistureLevel = EEPROM_read_uint8(SMARTPOT_MOISTURE_LEVEL_ADDR);
  waterTankBottom = EEPROM_read_uint16(
    SMARTPOT_WATER_TANK_BOTTOM_ADDR1,
    SMARTPOT_WATER_TANK_BOTTOM_ADDR2
  );
}
void smart_pot_setWaterAmount(uint8_t water) {
  waterAmount = water;
  EEPROM_write(SMARTPOT_WATER_AMOUNT_ADDR, water);
}

void smart_pot_setMoistLevel(uint8_t moist) {
  moistureLevel = moist;
  EEPROM_write(SMARTPOT_MOISTURE_LEVEL_ADDR, moist);
}

void smart_pot_setState(uint8_t enable){
  enable %= 2;
  EEPROM_write(SMARTPOT_ENABLE_STATE_ADDR, enable); 
  enableState = enable;
}


uint8_t smart_pot_tryWater(uint8_t moisture) {
  if (enableState != 1) {
    return 0;
  }

  if (
    (moisture < moistureLevel) && 
    (waterLevelPercentage > SMARTPOT_MIN_WATERING_WATER_LEVEL_PERCENTAGE)
  ) {
    smart_pot_playBuzzer(SMART_POT_SONG_WATERING);
    pump_run(waterAmount);
    return waterAmount;
  } else {
    return 0;
  }
}

uint8_t smart_pot_getWaterLevel() {
  // 30 + 50 mm
  uint8_t waterLevel = hc_sr04_takeMeasurement() - 30;
  uint8_t limit = waterTankBottom - 30;
  if (waterLevel < 0) {
    waterLevel = 0;
  }
  if (waterLevel > limit) {
    waterLevel = limit;
  }
  waterLevelPercentage = percentage(waterLevel, limit);

  if (waterLevelPercentage <= SMARTPOT_LOW_WATER_LEVEL_PERCENTAGE) {
    smart_pot_playBuzzer(SMART_POT_SONG_LOW_WATER_LEVEL);
    indicator_on();
  } else {
    indicator_off();
  }

  return waterLevelPercentage;
}

void smart_pot_calibrateWaterTank() {
  waterTankBottom = hc_sr04_takeMeasurement(); 

  unsigned char byte1 = (waterTankBottom >> 8) & 0xFF; // Extract the first byte
  unsigned char byte2 = waterTankBottom & 0xFF; // Extract the second byte

  EEPROM_write(SMARTPOT_WATER_TANK_BOTTOM_ADDR1, byte1); // Write the first byte to EEPROM
  EEPROM_write(SMARTPOT_WATER_TANK_BOTTOM_ADDR2, byte2); // Write the second byte to EEPROM
}

uint8_t smart_pot_getMoisture() {
  uint16_t moisture = moisture_read();
  return percentage(moisture, 1023);
}

uint64_t smart_pot_getMachineId() {
  machineGen = EEPROM_read_uint8(1000);
  machineId = EEPROM_read_uint32(1001, 1002, 1003, 1004);
  return (machineGen << 32) | machineId;
}

int percentage(int value, int ceiling) {
  return (1 - ((float)value / ceiling)) * 100;
}


bool smart_pot_playBuzzer(SMART_POT_SONG_t song) {
  switch (song) {
    case SMART_POT_SONG_LOW_WATER_LEVEL:
      tone_play(600, 150);
      tone_play(400, 150);
      break;
    case SMART_POT_SONG_WATERING:
      tone_play(650, 150);
      tone_play(800, 150);
      break;
    case SMART_POT_SONG_MOISTURE:
      tone_play(400, 150);
      tone_play(0, 150);
      tone_play(400, 150);
      break;
    case SMART_POT_SONG_ERROR:
      tone_play(200, 150);
      tone_play(100, 150);
      tone_play(200, 150);
      break;
    default:
      return false;
  }
  return true;
}
