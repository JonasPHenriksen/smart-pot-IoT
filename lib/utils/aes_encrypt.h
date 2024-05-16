#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> 

extern uint8_t key[16];

void encrypt_data(const uint8_t* key, uint8_t* data, size_t len);
void decrypt_data(const uint8_t* key, uint8_t* data, size_t len);
void print_hex(const char* label, const uint8_t* data, size_t len);
void hex_to_string(const char* hex, char* output, size_t len);