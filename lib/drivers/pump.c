#include "pump.h"
#include "includes.h"
#include <stdio.h>

void pump_init() {
  DDRC |= (1 << PUMP_OUTPUT_PIN); // Set PC1 as an output
}

void pump_run(uint8_t volume_ml) {
  pump_on();
  for (int i = 0; i < pump_volume_to_delay(volume_ml); i++) {
    _delay_ms(1);
  }
  pump_off();
}

void pump_on() {
  PORTC |= (1 << PUMP_OUTPUT_PIN); // Set port to HIGH
}

void pump_off() {
  PORTC &= ~(1 << PUMP_OUTPUT_PIN); // Set port to LOW
}

int pump_volume_to_delay(uint8_t volume_ml){
  float flow_rate_ml_s = 36.11;
  int pump_delay = (int)(volume_ml / flow_rate_ml_s * 1000);
  return pump_delay;
}