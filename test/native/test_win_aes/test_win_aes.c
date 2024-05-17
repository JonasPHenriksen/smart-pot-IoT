#include "../test/fff.h"
#include "unity.h"
#include "aes_encrypt.h"
#include "includes.h"
#include <stdio.h>

DEFINE_FFF_GLOBALS
FAKE_VOID_FUNC(aes128_enc_single, const uint8_t*, void*);
FAKE_VOID_FUNC(aes128_dec_single, const uint8_t*, void*);


void setUp(void)
{
    RESET_FAKE(aes128_enc_single);
    RESET_FAKE(aes128_dec_single);
    FFF_RESET_HISTORY();
}

void tearDown(void) {}

void test_aes_encrypt_encrypt_data_and_decrypt_data() {
    char* TestString = ("{Aes Test}");
    //char* Original_TestString = ("Aes Test");
    uint8_t key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};  
    uint8_t* encrypted_message = encrypt_data(key,TestString,strlen(TestString));
    uint8_t* decrypted_message = decrypt_data(key,encrypted_message,strlen(encrypted_message));

    TEST_ASSERT_EQUAL_STRING(TestString, decrypted_message);
    TEST_ASSERT_EQUAL(1, aes128_enc_single_fake.call_count);
    TEST_ASSERT_EQUAL(1, aes128_dec_single_fake.call_count);

    // TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(Original_TestString, TestString, strlen(Original_TestString));

}

void test_aes_encrypt_encrypt_data_and_decrypt_long_charPointer() {
    char* TestString = ("{Aes Testxfh dgj kjnlg hojie huiojxj iopd xgdpfhx dfgdxfg hx dhgfhdxg f dxhgfdxfh g xhdji ghdxp hxdfj hpfjohf}");
    //char* Original_TestString = ("Aes Test");
    uint8_t key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    uint8_t* encrypted_message = encrypt_data(key,TestString,strlen(TestString));
    uint8_t* decrypted_message = decrypt_data(key,encrypted_message,strlen(encrypted_message));

    TEST_ASSERT_EQUAL(7, aes128_enc_single_fake.call_count);
    TEST_ASSERT_EQUAL(7, aes128_dec_single_fake.call_count);
    TEST_ASSERT_EQUAL_STRING(TestString, decrypted_message);

    // TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(Original_TestString, TestString, strlen(Original_TestString));

}

void test_aes_encrypt_decrypt_data() {

}

int main(void)
{
    // Initialize the FFF framework
    UNITY_BEGIN();

    // Run the tests
    RUN_TEST(test_aes_encrypt_encrypt_data_and_decrypt_data);
    RUN_TEST(test_aes_encrypt_encrypt_data_and_decrypt_long_charPointer);

    // End the tests
    return UNITY_END();
}