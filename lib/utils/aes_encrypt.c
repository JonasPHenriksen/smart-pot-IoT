#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "aes_encrypt.h"

#define AES_BLOCK_SIZE 16

uint8_t* encrypt_data(const uint8_t* key, const uint8_t* data, size_t len) {
    size_t pad_len = AES_BLOCK_SIZE - (len % AES_BLOCK_SIZE);
    size_t total_len = len + pad_len;

    uint8_t* encrypted_data = (uint8_t*)malloc(total_len);
    if (!encrypted_data) {
        return NULL;
    }
    memcpy(encrypted_data, data, len);
    for (size_t i = 0; i < pad_len; ++i) {
        encrypted_data[len + i] = pad_len;
    }
    for (size_t i = 0; i < total_len; i += AES_BLOCK_SIZE) {
        aes128_enc_single(key, (void*)(encrypted_data + i));
    }

    return encrypted_data;
}

uint8_t* decrypt_data(const uint8_t* key, const uint8_t* data, size_t len) {
    uint8_t* decrypted_data = (uint8_t*)malloc(len + 1); 
    if (!decrypted_data) {
        return NULL;
    }

    memcpy(decrypted_data, data, len);

    for (size_t i = 0; i < len; i += AES_BLOCK_SIZE) {
        aes128_dec_single(key, (void*)(decrypted_data + i));
    }

    size_t end_index = 0;
    for (size_t i = 0; i < len; i++) {
        if (decrypted_data[i] == '}') {
            end_index = i + 1; 
            break;
        }
    }

    if (end_index < len) {
        decrypted_data[end_index] = '\0';
    } else {
        decrypted_data[len] = '\0';
    }

    return decrypted_data;
}