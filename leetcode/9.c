#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)


bool isPalindrome(const int x) {
    if (x < 0) {
        return false;
    }
    int n = x;
    int len = 0;
    while (n > 0) {
        len++;
        n /= 10;
    }
    int* arr = (int *) calloc(len, sizeof(int));
    n = x;
    // copy to array
    for (int i = 0; i < len; i++) {
        arr[i] = n % 10;
        n /= 10;
    }
    // check
    for (int i = 0; i < len >> 1; i++) {
        if (arr[i] != arr[len-i-1]) {
            free(arr);
            return false;
        }
    }
    free(arr);
    return true;
}

int main(int args, char* argv[]) {
    // define
    int x;
    // input
    scanf("%d", &x);
    // output
    log("%s\n", isPalindrome(x) ? "true" : "false");
    return 0;
}

