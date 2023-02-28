#include "bacon.h"
#include <stdio.h>
#include <stdlib.h>



// Add other #includes here if you> want.
// Planing to use a hashtable to transform chars to a unsigned int. 

// hashtable
char* table[] = {
    // A-Z 0-25
    "AAAAAA", "AAAAAB", "AAAABA", "AAAABB", "AAABAA",
    "AAABAB", "AAABBA", "AAABBB", "AABAAA", "AABAAB",
    "AABABA", "AABABB", "AABBAA", "AABBAB", "AABBBA",
    "AABBBB", "ABAAAA", "ABAAAB", "ABAABA", "ABAABB",
    "ABABAA", "ABABAB", "ABABBA", "ABABBB", "ABBAAA",
    "ABBAAB",

    // Symbols 26 - 39
    "ABBABA", // SPACE 26
    "ABBABB", // ! 27
    "ABBBAA", // " 28
    "ABBBAB", // # 29
    "ABBBBA", // $ 30
    "ABBBBB", // % 31
    "BAAAAA", // & 32
    "BAAAAB", // ' 33
    "BAAABA", // ( 34
    "BAAABB", // ) 35
    "BAABAA", // , 36
    "BAABAB", // - 37
    "BAABBA", // . 38
    "BAABBB", // / 39

    // Digit 40 - 49
    "BABAAA", // 0
    "BABAAB", // 1
    "BABABA", // 2
    "BABABB", // 3
    "BABBAA", // 4
    "BABBAB", // 5
    "BABBBA", // 6
    "BABBBB", // 7
    "BBAAAA", // 8
    "BBAAAB", // 9

    // MORE SYMBOL 50 - 52
    "BBAABA", // :
    "BBAABB", // ;
    "BBABAA",  // ?

    // 53 - 62 UNUSED

    // 63
    "BBBBBB" // EOM
};

char* get_bacon(const char c){
    // lowercase
    if (c >= 97 && c <= 122){
        return table[c-97];
    }

    // uppercase
    if (c >= 65 && c <= 90){
        return table[c-65];
    }

    // space to )
    if (c>= 32 && c <= 41){
        return table[c-32+26];
    }

    // , to /
    if (c >= 44 && c <= 47){
        return table[c-44+36];
    }

    // digits
    if (c >= '0' && c <= '9'){
        return table[c - '0' + 40];
    }

    if (c == 58){
        // :
        return table[50];

    }else if(c == 59){
        // ;
        return table[51];       
    }else if(c == 63){
        // ?
        return table[52];
    }

    // return EOM
    return table[53];
}

char get_c(const char* hash){
    // letters
    for (int i = 0; i < 26; i++){
        if (strcmp(table[i], hash) == 0){
            return i + 'A'; // return a uppercase letter
        }
    }

    // space to )
    for (int i = 26; i<36; i++){
        if(strcmp(table[i], hash) == 0){
            return i - 26 + ' '; 
        }
    }

    // , to /
    for (int i = 36; i < 40; i++){
        if (strcmp(table[i], hash) == 0){
            return i - 36 + ',';
        }
    }

    // 0 to 9
    for (int i = 40; i<50 ;i++){
        if(strcmp(table[i], hash) == 0){
            return i - 40 + '0';
        }
    }

    // :
    if (strcmp(table[50], hash) == 0){
        return ':';
    }

    // ;
    if (strcmp(table[51], hash) == 0){
        return ';';
    }

    // ?
    if (strcmp(table[52], hash) == 0){
       //printf("%s\n", table[51]);
        return '?';
    }

    // EOM
    if (strcmp(table[53], hash) == 0){
        return '\1';
    }

    // invalid error
    return('\n');
}


int encrypt(const char *plaintext, char *ciphertext) {
    int plain_len = strlen(plaintext);
    int cipher_len = strlen(ciphertext);
    //int len_needed = (plain_len+1)*6;

    int actual_len = 0;
    for (int i = 0; i<cipher_len; i++){
        char c = ciphertext[i];
        if (c <= 122 && c >= 97){
            actual_len += 1;
        }
        else if(c <= 90 && c >= 65){
            actual_len += 1;
        }
    }
    if(actual_len < 6){
        // insufficient memory to encode EOM
        return -1;
    }

    actual_len = actual_len / 6 - 1;

    // MIN of the two
    if (actual_len > plain_len){
        actual_len = plain_len;
    }

    // allocate space to store the codes
    char* codes = (char*) malloc((actual_len+1)*6 + 1);
    memset(codes, '\0', (actual_len+1)*6 + 1);
    char* pointer = codes;

    // get the codes
    for(int i = 0; i < actual_len; i++){
        char c = plaintext[i];
        strncpy(pointer, get_bacon(c), 6);
        pointer += 6;
    }

    // add EOM
    strncpy(pointer, table[53], 6);

    // encrypt
    int count = 0;
    for (int i = 0; i < cipher_len;i++){
        if (count == (actual_len+1)*6){
            break;
        }
        char c = ciphertext[i];
        if (c>= 97 && c<= 122){
            // lower ciphertext
            if(codes[count] == 'B'){ // if the code is B 1
                ciphertext[i] -= 32; // to upper 
            }
            count++;
        }
        else if(c >=65 && c<= 90){
            // upper ciphertext
            if(codes[count] == 'A'){ // if the code is A 0
                ciphertext[i] += 32; // to lower
            }
            count++;
        }
    }

    // free the memory
    free(codes);
    return actual_len;
}



int decrypt(const char *ciphertext, char *plaintext) {
    int cipher_len = strlen(ciphertext);
    char* cipher_arr = (char*) calloc(cipher_len+1, 1);
    int count = 0;
    for (int i = 0; i < cipher_len; i++){
        char c = ciphertext[i];
        if (c >= 65 && c <= 90){
            cipher_arr[count] = 'B';
            count++;
        }
        else if( c >= 97 && c <= 122){
            cipher_arr[count] = 'A';
            count+=1;
        }
    }

    int plain_len = count / 6; // plaintext len 
    int actual_plain_len = strlen(plaintext); // Plaintext buffer length given
    count = 0; // reuse for plaintext counter
    char temp_holder[7];
    char* pointer = cipher_arr;
    for (int i = 0; i < plain_len; i++){
        if (count > actual_plain_len){
            free(cipher_arr);
            return -2;
        }
        strncpy(temp_holder, pointer, 6);
        temp_holder[6] = '\0';
        //printf("%s\n",temp_holder);
        char temp_c = get_c(temp_holder);
        //printf("%d\n",temp_c);
        
        // \n for -3 invalid code error
        if (temp_c == '\n'){
            free(cipher_arr);
            return -3;
        }
        
        // \1 for EOM, did NOT include EOM
        if (temp_c == '\1')
        {
            //printf("EOM\n");
            break;
        }
        plaintext[i] = temp_c;
        count++;
        pointer += 6;
    }

    if (count == 0){
        free(cipher_arr);
        return -1;
    }

    if (strncmp(table[53], temp_holder, 6) != 0){
        free(cipher_arr);
        return -2;
    }

    plaintext[count] = '\0'; // null terminator
    free(cipher_arr);
    return count;
}



