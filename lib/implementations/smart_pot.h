#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
// DRIVERS
#include "tone.h"
#include "light.h"
#include "moisture.h"
#include "hc_sr04.h"
#include "pump.h"
#include "indicator.h"

// UTILS
#include "EEPROM_prompter.h"
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
void smart_pot_setState(uint8_t enable);
void smart_pot_calibrateWaterTank();
uint8_t smart_pot_tryWater(uint8_t moisture);
uint8_t smart_pot_getMoisture();
uint8_t smart_pot_getWaterLevel();
int percentage(int value, int ceiling);


#ifdef WINDOWS_TEST
extern uint8_t waterAmount;
extern uint8_t waterLevelPercentage;
extern uint8_t moistureLevel;
extern uint16_t waterTankBottom;
extern uint8_t machineGen;
extern uint32_t machineId;
extern uint8_t enableState;
#endif