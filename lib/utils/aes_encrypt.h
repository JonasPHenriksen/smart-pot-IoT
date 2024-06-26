#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 


#ifndef WINDOWS_TEST
#include "AESLib.h"
#endif

uint8_t* encrypt_data(const uint8_t* key, const uint8_t* data, size_t len);
uint8_t* decrypt_data(const uint8_t* key, const uint8_t* data, size_t len);