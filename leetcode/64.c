#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) ( a < b ? a : b )
#define log(S, ...) printf(S, ##__VA_ARGS__)

/**
 * Given a m x n grid filled with non-negative numbers,
 * find a path from top left to bottom right,
 * which minimizes the sum of all numbers along it's path.
 * Note: You can only move either down or right at any point in time.
 */
int minPathSum(int** grid, int gridSize, int* gridColSize) {
    // define
    int ret;
    int** dp = (int**) malloc(gridSize * sizeof(int*));
    for (int i = 0; i < gridSize; i++) {
        dp[i] = (int*) malloc((*gridColSize) * sizeof(int));
    }
    // find the min path sum
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < *gridColSize; j++) {
            if (i == 0 && j == 0) {
                dp[i][j] = grid[i][j];
                continue;
            }
            if (i == 0 && j > 0) {
                dp[i][j] = dp[i][j-1] + grid[i][j];
                continue;
            }
            if (j == 0 && i > 0) {
                dp[i][j] = dp[i-1][j] + grid[i][j];
                continue;
            }
            dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
        }
    }
    // dp[m-1][n-1] is the result
    ret = dp[gridSize-1][(*gridColSize)-1];
    // free memory and then return
    for (int i = 0; i < gridSize; i++) {
        free(dp[i]);
    }
    free(dp);
    return ret;
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
    log("%d\n", minPathSum(grid, m, &n));
    // free memory
    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);
    return 0;
}
