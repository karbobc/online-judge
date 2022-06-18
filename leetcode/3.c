#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 5e4 + 4
#define max(a, b) ((a) > (b) ? (a) : (b))
#define log(S, ...) printf(S, ##__VA_ARGS__)


/**
 * Given a string s, find the length of the longest substring that
 * does not contain repeated characters.
 */
int lengthOfLongestSubstring(const char* s) {
    // set array
    int* set = (int *) calloc(2e2, sizeof(int));
    // l is the left index of string
    // r is the right index of string
    int l = 0, r = 0;
    // ret is the result
    int ret = 0;
    int len = strlen(s);
    // find the length of longest substring
    while (r < len) {
        if (set[s[r]] == 0) {
            set[s[r++]]++;
        } else {
            set[s[l++]] = 0;
        }
        ret = max(ret, r-l);
    }
    // free memory
    free(set);
    return ret;
}

int main() {
    char* s = (char *) calloc(MAX_SIZE, sizeof(char));
    scanf("%s", s);
    printf("%d\n", lengthOfLongestSubstring(s));
    free(s);
    return 0;
}
