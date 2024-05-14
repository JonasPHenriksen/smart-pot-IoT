#include "smart_pot.h"
#include "uart.h"

#define SMARTPOT_WATER_AMOUNT_ADDR 2001
#define SMARTPOT_MOISTURE_LEVEL_ADDR 2002
#define SMARTPOT_WATER_TANK_BOTTOM_ADDR1 2003
#define SMARTPOT_WATER_TANK_BOTTOM_ADDR2 2003

#define SMARTPOT_MIN_WATERING_WATER_LEVEL_PERCENTAGE 5
#define SMARTPOT_LOW_WATER_LEVEL_PERCENTAGE 25

static uint8_t waterAmount;
static uint8_t waterLevelPercentage;
static uint8_t moistureLevel;
static uint16_t waterTankBottom;
static uint8_t machineGen;
static uint32_t machineId;

void smart_pot_init() {
  moisture_init();
  hc_sr04_init();
  display_init();
  buttons_init();
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

uint8_t smart_pot_tryWater() {
  uint8_t moisture = smart_pot_getMoisture();
  if (
    (moisture < moistureLevel) && 
    (waterLevelPercentage > SMARTPOT_MIN_WATERING_WATER_LEVEL_PERCENTAGE)
  ) {
    smart_pot_playBuzzer(SMART_POT_SONG_WATERING);
    pump_run(waterAmount);
    return waterAmount;
  }
  return 0;
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
  }

  return waterLevelPercentage;
}

uint16_t smart_pot_calibrateWaterTank() {
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
