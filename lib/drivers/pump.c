#include "pump.h"
#include "includes.h"

#define PC1 1
#define OUTPUT_PIN PC1 //PC1 is the pin that we are connected to and using to send the current.

void pump_init() {
    DDRC |= (1 << OUTPUT_PIN); //set PC1 as an output
}

void pump_run(int volume_ml){

    float flow_rate_ml_s = 36.11;
    int pump_delay = (int)(volume_ml / flow_rate_ml_s * 1000);

    PORTC |= (1 << OUTPUT_PIN); //Set port to HIGH
    _delay_ms(pump_delay);
    PORTC &= ~(1 << OUTPUT_PIN); //Set port to LOW
}