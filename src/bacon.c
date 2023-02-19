//#include "bacon.h"
#include <stdio.h>
#include <stdlib.h>

// Add other #includes here if you want.
// Planing to use a hashtable to transform chars to a unsigned int. 


int char_to_ascii (char input_char){
    char temp_char = '0';
    int result = input_char - temp_char;
    return result;
}

unsigned int hash_table_function(int ascii_from_above){
    unsigned int result = 0;
    if ((ascii_from_above < 43) && (ascii_from_above > 16))
    {
        int temp = ascii_from_above - 17;
        result += (unsigned int) temp;
        return result;
    }
    else if ((ascii_from_above < 0) && (ascii_from_above > -17))
    {
        unsigned int temp = ascii_from_above + 16;
        result = (unsigned int) 26 + temp;
        return result;
    }

}



int main(int argc, char const *argv[])
{
    printf("The int is: %d \n", char_to_ascii('A'));
    return 0;
}



int encrypt(const char *plaintext, char *ciphertext) {
    return -1000;
}

int decrypt(const char *ciphertext, char *plaintext) {
     return -1000;
}