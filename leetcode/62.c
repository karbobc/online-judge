#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)

/**
 * Given the two integers m and n,
 * returns the number of possible unique paths that destination is the bottom-right corner.
 * Note: Only can move either dwon or right at any point in time.
 */
int uniquePaths(int m, int n) {
    // define
    int paths;
    int* dp = (int*) calloc(n, sizeof(int));
    // find the unique paths
    dp[0] = 1;
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[j] += dp[j-1];
        }
    }
    paths = dp[n-1];
    // free memory and then return
    free(dp);
    return paths;
}

int main() {
    // define
    int m, n;
    // input
    scanf("%d %d", &m, &n);
    // output
    log("%d\n", uniquePaths(m, n));
    return 0;
}
