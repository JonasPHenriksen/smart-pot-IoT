#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "aes_encrypt.h"

#define AES_BLOCK_SIZE 16

uint8_t* encrypt_data(const uint8_t* key, const uint8_t* data, size_t len) {
    // Calculate padding length
    size_t pad_len = AES_BLOCK_SIZE - (len % AES_BLOCK_SIZE);
    size_t total_len = len + pad_len;

    // Allocate buffer for encrypted data
    uint8_t* encrypted_data = (uint8_t*)malloc(total_len);
    if (!encrypted_data) {
        // Handle allocation failure
        return NULL;
    }

    // Copy original data to the encrypted buffer
    memcpy(encrypted_data, data, len);

    // Pad with PKCS#7 padding
    for (size_t i = 0; i < pad_len; ++i) {
        encrypted_data[len + i] = pad_len;
    }

    // Encrypt in 16-byte blocks
    for (size_t i = 0; i < total_len; i += AES_BLOCK_SIZE) {
        aes128_enc_single(key, (void*)(encrypted_data + i));
    }

    return encrypted_data;
}


// Function to decrypt a string
uint8_t* decrypt_data(const uint8_t* key, const uint8_t* data, size_t len) {
    // Allocate buffer for decrypted data
    uint8_t* decrypted_data = (uint8_t*)malloc(len + 1); // +1 for null-terminator
    if (!decrypted_data) {
        // Handle allocation failure
        return NULL;
    }

    // Copy original encrypted data to the decrypted buffer
    memcpy(decrypted_data, data, len);

    // Decrypt in 16-byte blocks
    for (size_t i = 0; i < len; i += AES_BLOCK_SIZE) {
        aes128_dec_single(key, (void*)(decrypted_data + i));
    }

    // Find the index of the first '}' character
    size_t end_index = 0;
    for (size_t i = 0; i < len; i++) {
        if (decrypted_data[i] == '}') {
            end_index = i + 1; // Include the '}' character
            break;
        }
    }

    // Null-terminate the decrypted string at the '}' character
    if (end_index < len) {
        decrypted_data[end_index] = '\0';
    } else {
        // Ensure the string is null-terminated if no '}' is found
        decrypted_data[len] = '\0';
        //end_index = len;
    }

    return decrypted_data;
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