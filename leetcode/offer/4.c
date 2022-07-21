#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 1e3 + 3
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * Given a `n x m` matrix array, a `target` integer,
 * find whether the target in the matrix array.
 */
bool findNumberIn2DArray(int** matrix, int m, int* n, int target) {
  if (m == 0 || (*n) == 0) {
    return false;
  }
  int i = 0;
  int j = (*n) - 1;
  while (i < m && j >= 0) {
    if (matrix[i][j] > target) {
      j--;
      continue;
    }
    if (matrix[i][j] < target) {
      i++;
      continue;
    }
    return true;
  }
  return false;
}

int main() {
  // define
  int m, n;
  int target;
  int** matrix = malloc(MAX_SIZE * sizeof(*matrix));
  // input
  scanf("%d %d %d", &m, &n, &target);
  for (int i = 0; i < m; i++) {
    matrix[i] = malloc(n * sizeof(**matrix));
    for (int j = 0; j < n; j++) {
      scanf("%d", &matrix[i][j]);
    }
  }
  // output
  log(findNumberIn2DArray(matrix, m, &n, target) ? "true\n" : "false\n");
  // free memory
  for (int i = 0; i < m; i++) {
    free(matrix[i]);
    matrix[i] = NULL;
  }
  free(matrix);
  matrix = NULL;
  return 0;
}

