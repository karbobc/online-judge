#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1e5 + 2
#define log(S, ...) printf(S, ##__VA_ARGS__)

/**
 * DFS to generate all the valid bracket combinations.
 */
void dfs(char* str, int left, int right, char** strs, int* returnSize) {
    // copy the str string to the strs array when DFS to leaf node
    if (left == 0 && right == 0) {
        int len = strlen(str);
        strs[*returnSize] = (char*) malloc((len+1) * sizeof(char));
        memcpy(strs[(*returnSize)++], str, len+1);
        return;
    }
    // return directly when the number of left bracket greater than the number of right bracket
    if (left > right) {
        return;
    }
    // DFS the left side
    if (left > 0) {
        // concat the left bracket to the str string
        strcat(str, "(");
        dfs(str, left-1, right, strs, returnSize);
        // delete the last character
        str[strlen(str)-1] = '\0';
    }
    // DFS the right side
    if (left < right) {
        // concat the right bracket to the str string
        strcat(str, ")");
        dfs(str, left, right-1, strs, returnSize);
        // delete the last character
        str[strlen(str)-1] = '\0';
    }
}

/**
 * Generate n pairs of valid bracket combinations.
 */
char** generateParenthesis(int n, int* returnSize) {
    // define and alloc memory
    *returnSize = 0;
    char** strs = (char**) malloc(MAX_SIZE * sizeof(char*));
    char* str = (char*) malloc(MAX_SIZE * sizeof(char));
    str[0] = '\0';
    // DFS
    dfs(str, n, n, strs, returnSize);
    // free memory and then return
    free(str);
    return strs;
}

int main() {
    // define
    int n;
    int* returnSize;
    char** strs = NULL;
    // input
    scanf("%d", &n);
    // output
    strs = generateParenthesis(n, returnSize);
    for (int i = 0; i < *returnSize; i++) {
        log("%s\n", strs[i]);
    }
    // free memory
    for (int i = 0; i < *returnSize; i++) {
        free(strs[i]);
    }
    free(strs);
    return 0;
}
