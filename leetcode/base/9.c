#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)


bool isPalindrome(const int x) {
    if (x < 0) {
        return false;
    }
    long n = x, m = 0;
    while (n > 0) {
        m = m*10 + n%10;
        n /= 10;
    }
    return m == x;
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

