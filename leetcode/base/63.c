#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)

/**
 * Given the two integers m and n,
 * returns the number of possible unique paths that destination is the bottom-right corner.
 * Addtionally, an obstacle and space are marked as 1 or 0 respectively in grid,
 * and a path cannot include any squrare that is an obstacle.
 * Note: Only can move either dwon or right at any point in time.
 */
int uniquePathsWithObstacles(int** grid, int m, int* n) {
    // define
    int paths;
    int* dp = (int*) calloc(*n, sizeof(int));
    // find the unique paths with obstacle
    dp[0] = grid[0][0] == 0 ? 1 : 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < *n; j++) {
            if (grid[i][j] == 1) {
                dp[j] = 0;
                continue;
            }
            if (j > 0) {
                dp[j] += dp[j-1];
            }
        }
    }
    paths = dp[(*n)-1];
    // free memory and then return
    free(dp);
    return paths;
}

int main() {
    // define
    int m, n;
    int** grid = NULL;
    // input
    scanf("%d %d", &m, &n);
    grid = (int**) malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        grid[i] = (int*) malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    // output
    log("%d\n", uniquePathsWithObstacles(grid, m, &n));
    // free memory
    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);
    return 0;
}
