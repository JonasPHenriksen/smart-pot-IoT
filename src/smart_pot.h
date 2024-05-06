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

typedef enum {
  SONG_LOW_WATER_LEVEL,
  SONG_MOISTURE,
  SONG_WATERING,
  SONG_ERROR
} song_enum_t;

void smartPotInit();
void setWaterAmount(int waterAmount);
void setMoistLevel(int moist);
int tryWater();
bool playBuzzer(song_enum_t song);