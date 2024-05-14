#include <stdint.h>
#define PC1 1
#define PUMP_OUTPUT_PIN PC1 // PC1 is the pin that we are connected to and using to send the current.

void pump_init();
void pump_on();
void pump_off();
void pump_run(uint8_t volume_ml);
static int volume_to_delay(uint8_t volume_ml);