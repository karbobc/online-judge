#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 2e2 + 2
#define log(S, ...) printf(S, ##__VA_ARGS__)


/**
 * find the longest common prefix in s1 and s2
 */
char* commonPrefix(char* s1, char* s2) {
    int index = 0;
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    char* prefix = (char *) calloc(MAX_SIZE, sizeof(char));
    while (index < len1 && index < len2 && s1[index] == s2[index]) {
        index++;
    }
    memcpy(prefix, s1, index * sizeof(char));
    return prefix;
}

/**
 * find the longest common prefix in all the strings
 */
char* longestCommonPrefix(char** strs, int strSize) {
    char* prefix = strs[0];
    for (int i = 1; i < strSize; i++) {
        prefix = commonPrefix(prefix, strs[i]);
    }
    return prefix;
}

int main() {
    int strSize;
    char* prefix;
    char** strs = (char **) calloc(MAX_SIZE, sizeof(char*));
    scanf("%d", &strSize);
    for (int i = 0; i < strSize; i++) {
        char* s = (char *) calloc(MAX_SIZE, sizeof(char));
        scanf("%s", s);
        strs[i] = s;
    }
    prefix = longestCommonPrefix(strs, strSize);
    printf("%s\n", prefix);
    // free memory
    free(prefix);
    for (int i = 0; i < strSize; i++) {
        free(strs[i]);
    }
    free(strs);

}
