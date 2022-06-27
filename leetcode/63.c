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
    int** dp = (int**) malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        dp[i] = (int*) calloc((*n), sizeof(int));
    }
    // find the unique paths with obstacle
    for (int i = 0; i < m; i++) {
        if (grid[i][0] == 1) {
            break;
        }
        dp[i][0] = 1;
    }
    for (int j = 0; j < *n; j++) {
        if (grid[0][j] == 1) {
            break;
        }
        dp[0][j] = 1;
    }
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < *n; j++) {
            if (grid[i][j] == 1) {
                dp[i][j] = 0;
                continue;
            }
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    paths = dp[m-1][(*n)-1];
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
