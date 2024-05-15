#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <AESLib.h>

//AESLib aesLib;


/*void encrypt(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 256, &enc_key);
    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &enc_key, iv, AES_ENCRYPT);
}*/

/*char* encrypt(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv) {
    AES_KEY enc_key;
    AES_set_encrypt_key(key, 256, &enc_key);

    // Determine the length of the ciphertext (add padding if necessary)
    int ciphertext_len = ((plaintext_len + AES_BLOCK_SIZE - 1) / AES_BLOCK_SIZE) * AES_BLOCK_SIZE;
    unsigned char *ciphertext = (unsigned char *)malloc(ciphertext_len);
    if (ciphertext == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Encrypt the plaintext
    AES_cbc_encrypt(plaintext, ciphertext, plaintext_len, &enc_key, iv, AES_ENCRYPT);

    return ciphertext;
}*/

void encrypt(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    //aesLib.set_key(key, 32);

    // Encrypt the plaintext
    //aesLib.encrypt(iv, plaintext, ciphertext, plaintext_len);
}