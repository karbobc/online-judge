#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int** generateMatrix(int n, int* row, int** column) {
  int l = 0;
  int r = n-1;
  int t = 0;
  int b = n-1;
  *row = n;
  *column = malloc(n * sizeof(**column));
  int** matrix = malloc(n * sizeof(*matrix));
  for (int i = 0; i < n; i++) {
    (*column)[i] = n;
    matrix[i] = malloc(n * sizeof(**matrix));
  }
  for (int i = 1;;) {
    for (int j = l; j <= r; j++) {
      matrix[t][j] = i++;
    }
    if (++t > b) break;

    for (int j = t; j <= b; j++) {
      matrix[j][r] = i++;
    }
    if (l > --r) break;

    for (int j = r; j >= l; j--) {
      matrix[b][j] = i++;
    }
    if (t > --b) break;

    for (int j = b; j >= t; j--) {
      matrix[j][l] = i++;
    }
    if (++l > r) break;
  }
  return matrix;
}

int main() {
  // define
  int n;
  int row;
  int* column = NULL;
  int** matrix = NULL;
  // input
  scanf("%d", &n);
  // output and free memory
  matrix = generateMatrix(n, &row, &column);
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < column[i]; j++) {
      log("%d ", matrix[i][j]);
    }
    log("\n");
    free(matrix[i]);
  }
  free(column);
  free(matrix);
  return 0;
}

