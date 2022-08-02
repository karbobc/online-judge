#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int bitsum(int n) {
  int ret = 0;
  while (n > 0) {
    ret += (n % 10);
    n /= 10;
  }
  return ret;
}

int dfs(int i, int j, bool** visited, int m, int n, int k) {
  if (i >= m || j >= n || visited[i][j] || bitsum(i) + bitsum(j) > k) {
    return 0;
  }
  visited[i][j] = true;
  return 1 + dfs(i+1, j, visited, m, n, k)
           + dfs(i, j+1, visited, m, n, k);
}

int movingCount(int m, int n, int k) {
  // create an array `visited`
  bool** visited = malloc(m * sizeof(*visited));
  for (int i = 0; i < m; i++) {
    visited[i] = malloc(n * sizeof(**visited));
    memset(visited[i], false, n * sizeof(**visited));
  }
  // moving and count
  int cnt = dfs(0, 0, visited, m, n, k);
  // free memory
  for (int i = 0; i < m; i++) {
    free(visited[i]);
    visited[i] = NULL;
  }
  free(visited);
  visited = NULL;
  return cnt;
}

int main() {
  int m, n, k;
  scanf("%d %d %d", &m, &n, &k);
  log("%d\n", movingCount(m, n, k));
  return 0;
}

