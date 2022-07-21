#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 1e3 + 3
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * Binary search
 */
bool binarySearch(int* arr, int l, int r, int target) {
  if (l <= r) {
    int mid = (l + r) >> 1;
    if (arr[mid] > target) {
      return binarySearch(arr, l, mid-1, target);
    }
    if (arr[mid] < target) {
      return binarySearch(arr, mid+1, r, target);
    }
    return true;
  }
  return false;
}

/**
 * Given a `n x m` matrix array, a `target` integer,
 * find whether the target in the matrix array.
 */
bool findNumberIn2DArray(int** matrix, int m, int* n, int target) {
  for (int i = 0; i < m; i++) {
    if (binarySearch(matrix[i], 0, (*n)-1, target)) {
      return true;
    }
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

