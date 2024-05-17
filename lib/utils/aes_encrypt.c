#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "aes_encrypt.h"

#define AES_BLOCK_SIZE 16

void encrypt_data(const uint8_t* key, uint8_t* data, size_t len) {
    // Calculate padding length
    size_t pad_len = AES_BLOCK_SIZE - (len % AES_BLOCK_SIZE);
    // Pad with PKCS#7 padding
    for (size_t i = 0; i < pad_len; ++i) {
        data[len + i] = pad_len;
    }
    len += pad_len;
    // Encrypt in 16-byte blocks
    for (size_t i = 0; i < len; i += AES_BLOCK_SIZE) {
        aes128_enc_single(key, (void*)(data + i));
    }
}

// Function to decrypt a string
void decrypt_data(const uint8_t* key, uint8_t* data, size_t len) {
    // Decrypt in 16-byte blocks
    for (size_t i = 0; i < len; i += AES_BLOCK_SIZE) {
        aes128_dec_single(key, data + i);
    }
    // Find the index of the first '}' character
    size_t end_index = 0;
    for (size_t i = 0; i < len; i++) {
        if (data[i] == '}') {
            end_index = i + 1; // Include the '}' character
            break;
        }
    }
    // Null-terminate the decrypted string at the '}' character
    if (end_index < len) {
        data[end_index] = '\0';
    }
}



// void print_hex(const char* label, const uint8_t* data, size_t len) {
//     char buffer[3];
//     monitor_send((char*)label);
//     monitor_send(": ");
//     for (size_t i = 0; i < len; i++) {
//         snprintf(buffer, sizeof(buffer), "%02X ", data[i]);
//         monitor_send(buffer);
//     }
//     monitor_send("\r\n");
// }

// void hex_to_string(const char* hex, char* output, size_t len) {
//     for (size_t i = 0; i < len; i += 2) {
//         char byte[3] = {hex[i], hex[i + 1], '\0'};
//         output[i / 2] = (char)strtol(byte, NULL, 16);
//     }
//     output[len / 2] = '\0'; // Null-terminate the output string
// }