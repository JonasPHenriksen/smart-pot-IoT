#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 
#ifndef WINDOWS_TEST
#include <AESLib.h>
#endif

void encrypt_data(const uint8_t* key, uint8_t* data, size_t len);
void decrypt_data(const uint8_t* key, uint8_t* data, size_t len);
// void print_hex(const char* label, const uint8_t* data, size_t len);
// void hex_to_string(const char* hex, char* output, size_t len);