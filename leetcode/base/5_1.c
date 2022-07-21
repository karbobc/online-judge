#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1e3 + 3
#define max(a, b) (a > b ? a : b)
#define log(S, ...) printf(S, ##__VA_ARGS__)

/**
 * Expand around center algorithm.
 * Centered on s[l] and s[r], and expand to the left and right to find the palindrome string.
 */
int expand(const char* s, int l, int r) {
    int len = strlen(s);
    while (l >= 0 && r < len && s[l] == s[r]) {
        l--;
        r++;
    }
    return r - l - 1;
}

/**
 * Find the longest palindrome substring in a string s.
 */
char* longestPalindrome(const char* s) {
    // start is the index of start in the palindrome substring
    // end is the index of end in the palindrome substring
    int start = 0, end = 0;
    int strLen = strlen(s);
    char* palindrome = (char *) calloc(MAX_SIZE, sizeof(char));
    // find the longest palindrome substring
    for (int i = 0; i < strLen; i++) {
        int len1 = expand(s, i, i);
        int len2 = expand(s, i, i+1);
        int len = max(len1, len2);
        if (len > end - start) {
          start = i - ((len - 1) >> 1);
          end = i + (len >> 1);
        }
    }
    // copy the palindrome substring from the string s
    for (int i = 0; i <= end - start; i++) {
        palindrome[i] = s[start+i];
    }
    return palindrome;
}

int main() {
    // define 
    char* palindrome;
    char* s = (char *) calloc(MAX_SIZE, sizeof(char));
    // input
    scanf("%s", s);
    // output
    palindrome = longestPalindrome(s);
    log("%s\n", palindrome);
    // free memory
    free(palindrome);
    free(s);
    return 0;
}
