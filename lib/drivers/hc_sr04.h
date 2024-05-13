#include <inttypes.h>
#include <stdbool.h>

void hc_sr04_init();
void hc_sr04_toggle(bool state);
uint16_t hc_sr04_takeMeasurement();