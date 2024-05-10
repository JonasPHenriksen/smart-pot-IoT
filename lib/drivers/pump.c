#include "pump.h"
#include "includes.h"

void pump_init() {
    DDRC |= (1 << OUTPUT_PIN); //set PC1 as an output
}

void pump_run(int volume_ml){
    pump_on();
    _delay_ms(volume_to_delay(volume_ml));
    pump_off();
}

void pump_on() {
    PORTC |= (1 << OUTPUT_PIN); //Set port to HIGH
}

void pump_off() {
    PORTC &= ~(1 << OUTPUT_PIN); //Set port to LOW
}

int volume_to_delay(int volume_ml){
    float flow_rate_ml_s = 36.11;
    int pump_delay = (int)(volume_ml / flow_rate_ml_s * 1000);
}