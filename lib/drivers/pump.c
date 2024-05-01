#include "pump.h"
#include "includes.h"

#define PC1 1
#define OUTPUT_PIN PC1 //PC1 is the pin that we are connected to and using to send the current.

void pump_init() {
    DDRC |= (1 << OUTPUT_PIN); //set PC1 as an output
}

void pump_run(int delay_ms){

        PORTC |= (1 << OUTPUT_PIN); //Set port to HIGH
        _delay_ms(delay_ms);
        
        PORTC &= ~(1 << OUTPUT_PIN); //Set port to LOW
}