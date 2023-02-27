#include "bacon.h"
#include <stdio.h>
#include <stdlib.h>



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


int is_english_char (char input_char) {
    // 0 if not english char, else 1
    int ascii_from_above = (int) input_char;
    if ((ascii_from_above >= 65) && (ascii_from_above < 91))
    {
        return 1;
    }
    else if((ascii_from_above >= 97) && (ascii_from_above < 123))
    {
        return 1;
    }
    else{
        return 0;
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
    return (-999); 
}

// This meant to change the lower case in the plain text to upper case,
// because lower case English chars cannot be directly encoded.
int upper_to_lower(char* input_char_str){
    int length = strlen(input_char_str);
    for(int i = 0; i < length; i++){
        if((input_char_str[i] >= 97) && (input_char_str[i] < 123)){
            input_char_str[i] -= 32;
        }  
    }
    return 0;
}

//change a char string to int str
//NEED TO CHANGE UPPER TO LOWER
unsigned int* char_str_to_bacon_int_str(char* input_char_str){
    upper_to_lower(input_char_str);
    int length_char_str = strlen(input_char_str);
    unsigned int *int_str_binary [6 * (length_char_str)];
    // data fields to get binary
    unsigned int dividend = 0;
    // unsigned int divisor = 2;
    int pointer_at_int_str_bi = 0;
    for(int i = 0; i < length_char_str; i++){
        unsigned int bacon_code = get_bacon_code(*int_str_binary[i]);
        // the transformed array from decimal to binary will be in a reverse sequence. 
        unsigned int *current_char_binary_reverse[6];
        dividend = bacon_code;
        while(bacon_code > 0){
            int j = 0;
            if (dividend % 2 == 1)
            {
                *current_char_binary_reverse[j] = (unsigned int)0x1;
            }
            bacon_code = bacon_code/2;
            j++;
        }
        unsigned int *current_char_binary[6];
        //reverse the generated binary int array
        for(int k = 0; k < 6; k++){
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
    return *int_str_binary;
}


char* auto_change_case(char* cipher_text, unsigned int* plain_int){
    int cipher_length = strlen(cipher_text);
    int plain_pointer = 0;
    for(int cipher_pointer = 0; cipher_pointer < cipher_length; cipher_pointer++){
        if(zero_lower_one_upper(cipher_text[cipher_pointer]) == -999){
            // if is not a valid character to be encrypted.
            cipher_pointer++;
            // skip the current char. 
        }
        if(zero_lower_one_upper(cipher_text[cipher_pointer]) == 0){
            // if the cipher text this char is lower case 
            if(plain_int[plain_pointer] == 0x1){
                // if the plain is 1
                cipher_text[cipher_pointer] = cipher_text[cipher_pointer] - 32; 
                // change to upper case. 
            }
        }
        if(zero_lower_one_upper(cipher_text[cipher_pointer]) == 1){
            // if the cipher text this char is upper case 
            if(plain_int[plain_pointer] == 0x0){
                // if the plain is 0
                cipher_text[cipher_pointer] = cipher_text[cipher_pointer] + 32; 
                // change to lower case. 
            }
        }
        plain_pointer++;
    }
    return cipher_text;
}


// count the num of unusable chars in the cipher text string. 
int count_unusable_char(char* char_string){
    int length = strlen(char_string);
    int result = 0;
    for(int i = 0; i < length; i++){
        if(is_english_char(char_string[i] == 0)){
            result++;
        }
    }
    return result;
}


int encrypt(const char *plaintext, char *ciphertext) {
    int length_of_cipher = strlen(ciphertext);
    int unusable_chars = count_unusable_char(ciphertext);
    int length_of_plain = strlen(plaintext);
    length_of_cipher -= unusable_chars;
    length_of_cipher *= 6;
    //int* cipher_int[length_of_cipher];
    unsigned int* plain_int_bacon = char_str_to_bacon_int_str((char*)plaintext);
    // if not overflow
    if (length_of_plain <= (length_of_cipher/6))
    {
        ciphertext = auto_change_case(ciphertext, plain_int_bacon);
        return 0; // need to change here
    }
    // if overflow
    else{
        int loss_chars = length_of_plain - (int)(length_of_cipher/6);
        ciphertext = auto_change_case(ciphertext, plain_int_bacon);
        return loss_chars;
    }
}

// int decrypt(const char *ciphertext, char *plaintext) {
//      return -1000;
// }