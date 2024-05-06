#include "smart_pot.h"

static uint8_t waterAmount;
static uint8_t moistLevel;

void smartPotInit() {
  moisture_init();
  hc_sr04_init();
  display_init();
  buttons_init();
  tone_init();
  pump_init();
}

void setWaterAmount(int water) {
  waterAmount = water;
}

void setMoistLevel(int moist) {
  moistLevel = moist;
}

int tryWater() {
  if (getMoisture() < moistLevel) {
    pump_run(waterAmount);
  } else {
    return NULL;
  }
  return waterAmount;
}

int getWaterLevel() {

}
int getMoisture() {
  uint16_t moisture = moisture_read();
  uint8_t moisture_percentage = (1 - ((float)moisture / 1023.0)) * 100;
  return moisture_percentage;
}
bool playBuzzer(song_enum_t song) {
  switch (song) {
    case SONG_LOW_WATER_LEVEL:
      tone_play_mario();
      break;
    case SONG_WATERING:
      tone_play_starwars();
      break;
    case SONG_MOISTURE:
      tone_play_mario();
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
