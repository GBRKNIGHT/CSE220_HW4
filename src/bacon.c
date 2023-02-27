#include "bacon.h"
#include <stdio.h>
#include <stdlib.h>
typedef enum {false,true}bool;


// Add other #includes here if you> want.
// Planing to use a hashtable to transform chars to a unsigned int. 


// change the char to ASCII values. 
int char_to_ascii (char input_char){
    return input_char;
}



unsigned int askii_to_bacon(int ascii_from_above){
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


// use 2 functions above to get the bacon code
unsigned int get_bacon_code(char input_char){
    unsigned int askii = char_to_ascii(input_char);
    unsigned int bacon = askii_to_bacon(askii);
    return bacon;
}


// use to find out if a character is upper or lower case
int zero_lower_one_upper(char test_char){
    if ((test_char >= 65 ) && (test_char < 91)) // if it is an upper case char
    {
        return 1;
    }
    else if((test_char >= 97) && (test_char < 123)){
        return 0;
    }
    else{

    }
    return -999; 
}


//change a char string to int str
int* char_str_to_bacon_int_str(char* input_char_str){
    int length_char_str = strlen(input_char_str);
    int *int_str_binary [6 * length_char_str];
    // data fields to get binary
    unsigned int dividend = 0;
    unsigned int divisor = 2;
    int pointer_at_int_str_bi = 0;
    for(int i = 0; i < length_char_str; i++){
        unsigned int bacon_code = get_bacon_code(int_str_binary[i]);
        // the transformed array from decimal to binary will be in a reverse sequence. 
        unsigned int *current_char_binary_reverse[6];
        dividend = bacon_code;
        while(bacon_code > 0){
            int j = 0;
            if (dividend % 2 == 1)
            {
                current_char_binary_reverse[j] == 0x1;
            }
            bacon_code = bacon_code/2;
            j++;
        }
        unsigned int *current_char_binary[6];
        //reverse the generated binary int array
        for(int k = 0; k < strlen(current_char_binary); k++){
            int l = 5;
            current_char_binary[k] = current_char_binary_reverse[l];
            l--;
        }
        //store the binary int array of each character into the general binary int array
        for(int m = 0; m < 6; m++){
            int_str_binary[pointer_at_int_str_bi] = current_char_binary[m];
            pointer_at_int_str_bi ++;
        }
        dividend = 0;
    }
    return int_str_binary;
}


int encrypt(const char *plaintext, char *ciphertext) {
    int length_of_cipher = strlen(ciphertext);
    int length_of_plain = strlen(plaintext);
    length_of_cipher *= 6;
    int cipher_int[length_of_cipher];
    int* plain_int_bacon = char_str_to_bacon_int_str(plaintext);
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