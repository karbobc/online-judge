#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (2e2 + 2)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)
#define max(a, b) (a > b ? a : b)

/**
 * Given a `m x n` grid,
 * find a path from top left to bottom right,
 * which maximizes the sum of all numbers along it's path.
 * Note: You can only move either down or right at any point in time.
 */
int maxValue(int** grid, int m, int* n) {
  // initialize
  int ret = 0;
  int* dp = malloc((*n) * sizeof(*dp));
  dp[0] = grid[0][0];
  // initialize the first row in `dp` array
  for (int j = 1; j < (*n); j++) {
    dp[j] = dp[j-1] + grid[0][j];
  }
  // find the max path sum.
  for (int i = 1; i < m; i++) {
    dp[0] = dp[0] + grid[i][0];
    for (int j = 1; j < (*n); j++) {
      dp[j] = max(dp[j], dp[j-1]) + grid[i][j];
    }
  }
  // dp[n-1] is the result
  ret = dp[(*n)-1];
  // free and return
  free(dp);
  dp = NULL;
  return ret;
}

int main() {
  // define
  int m, n;
  int** grid = malloc(MAX_SIZE * sizeof(*grid));
  // input
  scanf("%d %d", &m, &n);
  for (int i = 0; i < m; i++) {
    grid[i] = malloc(n * sizeof(**grid));
    for (int j = 0; j < n; j++) {
      scanf("%d", &grid[i][j]);
    }
  }
  // output
  log("%d\n", maxValue(grid, m, &n));
  // free memory
  for (int i = 0; i < m; i++) {
    free(grid[i]);
    grid[i] = NULL;
  }
  free(grid);
  grid = NULL;
  return 0;
}

