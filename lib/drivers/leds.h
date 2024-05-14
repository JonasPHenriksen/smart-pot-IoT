#include <stdint.h>

void leds_init(); // initialize the LED’s to be output. 
void leds_turn_on(uint8_t led_no); //takes in the value 1, 2, 3 or 4, each number corresponding to a LED. 
void leds_turn_off(uint8_t led_no); //takes in the value 1, 2, 3 or 4, each number corresponding to a LED. 
void leds_toggle(uint8_t led_no); //takes in the value 1, 2, 3 or 4, each number corresponding to a LED.