#include "smart_pot.h"

static uint32_t waterAmount;
static uint8_t moistLevel;

void smartPotInit() {
  moisture_init();
  hc_sr04_init();
  display_init();
  buttons_init();
  tone_init();
  pump_init();
}

void setWaterAmount(uint32_t water) {
  waterAmount = water;
}

void setMoistLevel(uint8_t moist) {
  moistLevel = moist;
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
  uint8_t waterLevelPercentage = waterLevel / 50 * 100;

  return waterLevelPercentage;
}
uint8_t getMoisture() {
  uint16_t moisture = moisture_read();
  uint8_t moisture_percentage = (1 - ((float)moisture / 1023.0)) * 100;
  return moisture_percentage;
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
