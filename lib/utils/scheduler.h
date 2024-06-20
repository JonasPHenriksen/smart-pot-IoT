#pragma once
#include <stdint.h>
#include <stdbool.h>

#define MS_PER_TICK 10

typedef struct task_s {
  uint32_t period; // delay in ms between each run
  void (*task_p)(); // pointer to task
  bool ready; // is it time to run now
} task_t;

void scheduler_init();
void scheduler_dispatch();