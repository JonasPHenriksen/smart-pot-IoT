#include "scheduler.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

extern task_t task_list[];
extern uint8_t task_count;

static uint32_t _sTick;
static uint8_t _task_index;

void scheduler_init() {
  uint16_t frequency = 1000/MS_PER_TICK; // Hz
  TCCR1A = 0;
  TCCR1B = (1 << WGM12) | (1 << CS11) | (1 << CS10);
  OCR1A = F_CPU/(64*frequency);
  TIMSK1 = (1 << OCIE1A); // Enable timer comapre match interrupt

  _sTick = 0;
  _task_index = 0;
}

void scheduler_dispatch() {
  for (uint8_t i = 0; i < task_count; i++) {
    task_t task = task_list[i]
    if (task.ready) {
      task.task_p();
      task.ready = false;
    }
  }
}

ISR(TIMER1_COMPA_vect) {
  for (uint8_t i = 0; i < task_count; i++) {
    if (0 == (_sTick % (task_list[i].period/MS_PER_TICK))) {
      task_list[i].ready = true;
    }
  }
  _sTick++;
}