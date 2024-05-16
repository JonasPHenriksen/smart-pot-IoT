#include "indicator.h"
#include "includes.h"

void indicator_init() {
  DDRC |= (1 << INDICATOR_OUTPUT_PIN);
}
void indicator_on() {
  PORTC |= (1 << INDICATOR_OUTPUT_PIN);
}
void indicator_off() {
  PORTC &= ~(1 << INDICATOR_OUTPUT_PIN);
}
