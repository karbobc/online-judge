#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (1e3 + 3)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int* spiralOrder(int** matrix, int row, int* columns, int* returnSize) {
  *returnSize = 0;
  int m = row;
  int n = columns[0];
  int l = 0;
  int r = n - 1;
  int t = 0;
  int b = m - 1;
  int* arr = malloc(m * n * sizeof(*arr));
  while (l <= r && t <= b) {
    for (int i = l; i <= r; i++) {
      arr[(*returnSize)++] = matrix[t][i];
    }
    if (++t > b) break;
    for (int i = t; i <= b; i++) {
      arr[(*returnSize)++] = matrix[i][r];
    }
    if (l > --r) break;
    for (int i = r; i >= l; i--) {
      arr[(*returnSize)++] = matrix[b][i];
    }
    if (t > --b) break;
    for (int i = b; i >= t; i--) {
      arr[(*returnSize)++] = matrix[i][l];
    }
    if (++l > r) break;
  }
  return arr;
}

int main() {
  // define
  int m, n;
  int returnSize;
  int* arr = NULL;
  int** matrix = malloc(MAX_SIZE * sizeof(*matrix));
  // input
  scanf("%d %d", &m, &n);
  for (int i = 0; i < m; i++) {
    matrix[i] = malloc(MAX_SIZE * sizeof(**matrix));
    for (int j = 0; j < n; j++) {
      scanf("%d", &matrix[i][j]);
    }
  }
  // output
  arr = spiralOrder(matrix, m, &n, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    log("%d ", arr[i]);
  }
  log("\n");
  // free memory
  for (int i = 0; i < m; i++) {
    free(matrix[i]);
  }
  free(matrix);
  free(arr);
  return 0;
}

