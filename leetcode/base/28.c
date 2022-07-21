#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1e4 + 4
#define log(S, ...) printf(S, ##__VA_ARGS__)


/**
 * create next array
 */
char* createNext(const char* a) {
    // length of array
    int len = strlen(a);
    // create next array that is empty
    char* next = (char *) calloc(len, sizeof(char));
    // i: index of next array
    // j: the longest common prefix of next array
    int i = 0, j = 0;
    // the longest common prefix of next[0] is 0 
    next[i++] = 0;
    // build the next array
    while (i < len) {
        if (a[i] == a[j]) {
            next[i++] = ++j;
            continue;
        }
        if (j > 0) {
            j = next[j-1];
        } else {
            next[i++] = 0;
        }
    }
    return next;
}


/**
 * find the first index of the needle string in the haystack string
 * the index starts from 0
 * if it does not exist, -1 is returned
 */
int strStr(const char* haystack, const char* needle) {
    // i is the index of haystack
    // j is the index of needle
    int i = 0, j = 0;
    // index is the result
    int index = -1;
    // the length of string array
    int len1 = strlen(haystack);
    int len2 = strlen(needle);
    // create next array
    char* next = createNext(needle);
    // find the index
    while (i < len1) {
        if (haystack[i] == needle[j]) {
            i++;
            j++;
            if (j == len2) {
                index = i - j;
                break;
            }
            continue;
        }
        if (j > 0) {
            j = next[j-1];
        } else {
            i++;
        }
    }
    free(next);
    return index;
}

int main(int args, char* argv[]) {
    // define
    char* haystack = (char *) malloc(MAX_SIZE * sizeof(char));
    char* needle = (char *) malloc(MAX_SIZE * sizeof(char));
    // input
    scanf("%s %s", haystack, needle);
    // output
    log("%d\n", strStr(haystack, needle));
    log("%s %s\n", haystack, needle);
    // free memory
    free(haystack);
    free(needle);
    return 0;
}

