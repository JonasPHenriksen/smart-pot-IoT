#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

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
int percentage(int value, int ceiling);


extern uint8_t waterAmount;
extern uint8_t waterLevelPercentage;
extern uint8_t moistureLevel;
extern uint16_t waterTankBottom;
extern uint8_t machineGen;
extern uint32_t machineId;