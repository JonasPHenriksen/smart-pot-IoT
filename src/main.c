#include "includes.h"
#include <stdbool.h>

#include "buttons.h"
#include "monitor.h"
#include "smart_pot.h"
#include "connection_handler.h"
#include "cycle.h"
#include "scheduler.h"

bool aesEncryption = false; 
task_t task_list[] = { 
  { 20 * 1000, cycle_run, false },
  { 100,  }
};
uint8_t task_count = sizeof(task_list)/sizeof(task_t);

// Network config
char* ip = "13.53.174.85";
uint16_t port = 11000;
char* SSID = "YOUR_WIFI_SSID";
char* password = "YOUR_WIFI_PASSWORD";

void connect_wrapper() {
  connection_handler_connect(ip, port, &smart_pot_updateConfig);
}

void setup() {
  monitor_init(9600);
  buttons_init();
  
  scheduler_init();
  sei();

  smart_pot_init();
  WIFI_ERROR_MESSAGE_t error = connection_handler_init(SSID, password);

  // Check if couldnt connect etc.

  cycle_init(aesEncryption, &connect_wrapper);
}

void loop() {
  scheduler_dispatch();
  if (buttons_1_pressed()) {
    smart_pot_calibrateWaterTank();
  }
  if (buttons_2_pressed()) {
    aesEncryption = true;
  }
  if (buttons_3_pressed()) {
    aesEncryption = false;
  }
}