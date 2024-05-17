#include "../test/fff.h"
#include "unity.h"
#include "aes_encrypt.h"
#include <stdint.h>

DEFINE_FFF_GLOBALS
FAKE_VALUE_FUNC(int, aes128_enc_single, const uint8_t*, void*);
FAKE_VALUE_FUNC(int, aes128_dec_single, const uint8_t*, void*);


void setUp(void)
{
    RESET_FAKE(aes128_enc_single);
    RESET_FAKE(aes128_dec_single);

    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_aes_encrypt_encrypt_data_and_decrypt_data() {
    char* TestString = ("Aes Test");
    char* Original_TestString = ("Aes Test");
    encrypt_data(key,TestString,strlen(TestString));
    decrypt_data(key,TestString,strlen(TestString));

    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(Original_TestString, TestString, strlen(Original_TestString), "The decrypted string does not match the original string");

}

void test_aes_encrypt_wrong_key() {

}

void test_aes_encrypt_decrypt_data() {

}

int main(void)
{
    // Initialize the FFF framework
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_aes_encrypt_encrypt_data_and_decrypt_data);

    // End the tests
    return UNITY_END();
}