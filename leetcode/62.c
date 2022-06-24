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
    int** dp = (int**) malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        dp[i] = (int*) malloc(n * sizeof(int));
    }
    // find the unique paths
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
                continue;
            }
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    paths = dp[m-1][n-1];
    // free memory and then return
    for (int i = 0; i < m; i++) {
        free(dp[i]);
    }
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
