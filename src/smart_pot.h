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
  SONG_LOW_WATER_LEVEL,
  SONG_MOISTURE,
  SONG_WATERING,
  SONG_ERROR
} song_enum_t;

void smartPotInit();
void setWaterAmount(uint32_t waterAmount);
void setMoistLevel(uint8_t moist);
uint32_t tryWater();
bool playBuzzer(song_enum_t song);
uint8_t getMoisture();
uint8_t getWaterLevel();