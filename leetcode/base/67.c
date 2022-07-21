#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1e4 + 4
#define log(S, ...) printf(S, ##__VA_ARGS__)

/**
 * Reverse a string
 */
void reverse(char* s) {
    char ch;
    int len = strlen(s);
    for (int i = 0; i < (len >> 1); i++) {
        ch = s[i];
        s[i] = s[len-i-1];
        s[len-i-1] = ch;
    }
}

/**
 * Given two binary string s1 and s2, return their sum as a binary string.
 */
char* addBinary(char* s1, char* s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    // ensure that the length of the s1 string is the longest
    if (len1 < len2) {
        return addBinary(s2, s1);
    }
    // initalize carry to 0
    int carry = 0;
    char* s = (char*) malloc(MAX_SIZE * sizeof(char));
    // reverse the s1 and s2 string
    reverse(s1);
    reverse(s2);
    // copy  string s1 to s
    strcpy(s, s1);
    // binary add
    for (int i = 0; i < len2; i++) {
        int sum = (s1[i] - '0') + (s2[i] - '0') + carry;
        s[i] = (sum & 1) + '0';
        carry = sum >> 1;
    }
    for (int i = len2; i < len1 && carry; i++) {
        int sum = s1[i] - '0' + carry;
        s[i] = (sum & 1) + '0';
        carry = sum >> 1;
    }
    if (carry) {
        strcat(s, "1");
    }
    // reverse all the strings
    reverse(s1);
    reverse(s2);
    reverse(s);
    // return the result
    return s;
}

int main() {
    // define
    char* s = NULL;
    char* s1 = (char*) malloc(MAX_SIZE * sizeof(char));
    char* s2 = (char*) malloc(MAX_SIZE * sizeof(char));
    // input
    scanf("%s %s", s1, s2);
    // output
    s = addBinary(s1, s2);
    log("%s\n", s);
    // free memory
    free(s);
    free(s1);
    free(s2);
    return 0;
}
