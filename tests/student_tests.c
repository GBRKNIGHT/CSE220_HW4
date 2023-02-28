#include "unit_tests.h"

TestSuite(student_suite, .timeout=TEST_TIMEOUT);

/*
Test(student_suite, name_of_test, .description="description of test") {
    // Steps of unit test go here
}
*/

Test(student_suite, decrypt_one_error, .description="Length of plaintext is 0. Error -1.") {
    char plaintext_act[] = "*******************";
    for (unsigned int i = 0; i < strlen(plaintext_act); i++)
        plaintext_act[i] = (char)(rand() % 200 + 33);
    char *ciphertext = "ONE OF THe mAiN cAuseS of THE fall of The rOman EmpiRe Was THaT LaCking ZeRo, tHey haD no wAy To iNDicaTE SUCCESSful termination of their C programs.";
    int count_act = decrypt(ciphertext, plaintext_act);  
    //char *plaintext_exp = "--ROBERT FIRTH";
    int count_exp = -1;
    //cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_two_error, .description="Missing EOM. Error -2.") {
    char plaintext_act[] = "*******************";
    for (unsigned int i = 0; i < strlen(plaintext_act); i++)
        plaintext_act[i] = (char)(rand() % 200 + 33);
    char *ciphertext = "He mAiN cAuseS of THE fall of The rOman EmpiRe Was THaT LaCking ZeRo, tHey haD no wAy To iNDicaTE ";
    int count_act = decrypt(ciphertext, plaintext_act);  
    //char *plaintext_exp = "--ROBERT FIRTH";
    int count_exp = -2;
    //cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(student_suite, decrypt_three_error, .description="Invalid code. Error -3.") {
    char plaintext_act[] = "*******************";
    for (unsigned int i = 0; i < strlen(plaintext_act); i++)
        plaintext_act[i] = (char)(rand() % 200 + 33);
    char *ciphertext = "HE mAiN cAuseS of THE fall of The rOman EmpiRe Was THaT LaCking ZeRo, tHey haD no wAy To iNDicaTE ";
    int count_act = decrypt(ciphertext, plaintext_act);  
    //char *plaintext_exp = "--ROBERT FIRTH";
    int count_exp = -3;
    //cr_expect_str_eq(plaintext_act, plaintext_exp, "plaintext was:           %s\nbut it should have been: %s", plaintext_act, plaintext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

Test(base_suite, encrypt_one_error, .description="Insufficient memory for EOM. Error -1") {
    char ciphertext_act[] = "Too oo2022";
    char *plaintext = "Stony Brook University";
    int count_act = encrypt(plaintext, ciphertext_act);
    //char *ciphertext_exp = "TOO SHOrt 2022";
    int count_exp = -1;
    //cr_expect_str_eq(ciphertext_act, ciphertext_exp, "ciphertext was:          %s\nbut it should have been: %s", ciphertext_act, ciphertext_exp);
    cr_expect_eq(count_act, count_exp, "Return value was %d, but it should have been %d.\n", count_act, count_exp);
}

// Test(student_suite, decrypt_one_erro_valgrind) {
//     assert_no_valgrind_errors(run_using_system("decrypt_one_error"));
// }

// Test(student_suite, decrypt_one_error_valgrind) {
//     assert_no_valgrind_errors(run_using_system("decrypt_one_error"));
// }

