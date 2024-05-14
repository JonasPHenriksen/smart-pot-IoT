#pragma once
// STANDARD LIBRARIES
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// DRIVERS
#include "tone.h"
#include "buttons.h"
#include "light.h"
#include "display.h"
#include "moisture.h"
#include "hc_sr04.h"
#include "pump.h"

// UTILS
#include "EEPROM_promter.h"

typedef enum {
  SMART_POT_SONG_LOW_WATER_LEVEL,
  SMART_POT_SONG_MOISTURE,
  SMART_POT_SONG_WATERING,
  SMART_POT_SONG_ERROR
} SMART_POT_SONG_t;

void smart_pot_init();
bool smart_pot_playBuzzer(SMART_POT_SONG_t song);
void smart_pot_setMoistLevel(uint8_t moist);
void smart_pot_setWaterAmount(uint8_t water);
uint8_t smart_pot_tryWater();
uint8_t smart_pot_getMoisture();
uint8_t smart_pot_getWaterLevel();
uint16_t smart_pot_calibrateWaterTank();