#include "bacon.h"
#include <stdio.h>
#include <stdlib.h>


// Add other #includes here if you want.
// Planing to use a hashtable to transform chars to a unsigned int. 


// change the char to ASCII values. 
int char_to_ascii (char input_char){
    return input_char;
}



unsigned int return_bacon_code(int ascii_from_above){
    unsigned int result = 0;
    // if uppercase chars from A to Z
    if ((ascii_from_above >= 65) && (ascii_from_above < 91))
    {
        int temp = ascii_from_above - 65;
        result += (unsigned int) temp;
        return result;
    }
    //if symbols
    else if ((ascii_from_above >= 32) && (ascii_from_above < 48))
    {
        unsigned int temp = ascii_from_above - 32;
        result = (unsigned int) 26 + temp;
        return result;
    }
    // if numbers from 0 to 9
    else if ((ascii_from_above >= 48) && (ascii_from_above < 58)){
        unsigned int temp = ascii_from_above - 48;
        result = (unsigned int) 40 + temp;
        return result;
    }
    // if : or ;
    else if((ascii_from_above >= 58 ) && (ascii_from_above < 60)){
        unsigned int temp = ascii_from_above - 58;
        result = (unsigned int) 50 + temp;
        return result;
    }
    // if ?
    else if(ascii_from_above == 63) {
        unsigned int temp = ascii_from_above - 63;
        result = (unsigned int) 52 + temp;
        return result;
    }
    // other, use to deal with unknown chars
    else{
        return -999;
    }
}






int encrypt(const char *plaintext, char *ciphertext) {
    int length_of_cipher = strlen(ciphertext);
    int length_of_plain = strlen(plaintext);
    length_of_cipher *= 6;
    // if not overflow
    if (length_of_plain <= length_of_cipher)
    {
        return -1000;
    }
    // if overflow
    else{

    }
    
    return -1000;
}

int decrypt(const char *ciphertext, char *plaintext) {
     return -1000;
}