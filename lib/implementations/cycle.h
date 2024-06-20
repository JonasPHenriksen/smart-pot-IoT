#pragma once
#include <stdbool.h>
#include <stdint.h>
#include "connection_handler.h"

void cycle_init(
  bool _aesEncryption,
  CUSTOM_CALLBACK_T customCallback
);
void cycle_run();