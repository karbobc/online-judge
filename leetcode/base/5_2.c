#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1e3 + 3
#define log(S, ...) printf(S, ##__VA_ARGS__)

/**
 * Find the longest palindrome substring in a string s.
 */
char* longestPalindrome(const char* s) {
    // start is the index of start in the palindrome substring
    // end is the index of end in the palindrome substring
    int start = 0, end = 0;
    int len = strlen(s);
    char* palindrome = (char*) calloc(MAX_SIZE, sizeof(char));
    // dp[l][r] indicates whether is a palindrome string from s[l] to s[r]
    int** dp = (int**) calloc(MAX_SIZE, sizeof(int*));
    // the length is 1 of the string must be a palindrome string, so dp[i][i] is a palindrome string
    for (int i = 0; i < len; i++) {
        dp[i] = (int*) calloc(MAX_SIZE, sizeof(int));
        dp[i][i] = 1;
    }
    // find the longest palindrome substring
    for (int r = 0; r < len; r++) {
        for (int l = 0; l < r; l++) {
            if (s[l] == s[r]) {
                if (r - l <= 2) {
                    dp[l][r] = 1;
                } else {
                    dp[l][r] = dp[l+1][r-1];
                }
            }
            // record the index of start and end when appears a longer plindrome string
            if (dp[l][r] && r-l > end-start) {
                start = l;
                end = r;
            }
        }
    }
    // copy the palindrome substring from the string s
    for (int i = 0; i <= end-start; i++) {
        palindrome[i] = s[start+i];
    }
    // free memory
    for (int i = 0; i < len; i++) {
        free(dp[i]);
    }
    free(dp);
    // return
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
