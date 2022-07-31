#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int pow10(int n) {
  int ret = 1;
  for (int i = 0; i < n; i++) {
    ret *= 10;
  }
  return ret;
}

int* printNumbers(int n, int* returnSize) {
  *returnSize = 0;
  int size = pow10(n);
  int* arr = malloc(size * sizeof(*arr));
  while (*returnSize < size-1) {
    arr[(*returnSize)++] = (*returnSize) + 1;
  }
  return arr;
}

int main() {
  // define
  int n;
  int returnSize;
  int* arr = NULL;
  // input
  scanf("%d", &n);
  // output
  arr = printNumbers(n, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    log("%d ", arr[i]);
  }
  log("\n");
  // free memory
  free(arr);
  arr = NULL;
  return 0;
}

