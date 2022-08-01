#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (5e4 + 5)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * Given a array `nums`, exchange the order of the array,
 * odd numbers are in the first of the array,
 * and even numbers are in the second of the array.
 */
int* exchange(int* nums, int numsSize, int* returnSize) {
  *returnSize = numsSize;
  int* arr = malloc(numsSize * sizeof(*arr));
  int i = 0, j = numsSize-1;
  for (int k = 0; k < numsSize; k++) {
    if (nums[k] & 1) {
      arr[i++] = nums[k];
    } else {
      arr[j--] = nums[k];
    }
  }
  return arr;
}

int main() {
  // define
  int numsSize;
  int returnSize;
  int* arr = NULL;
  int* nums = malloc(MAX_SIZE * sizeof(*nums));
  // input
  scanf("%d", &numsSize);
  for (int i = 0; i < numsSize; i++) {
    scanf("%d", &nums[i]);
  }
  // output
  arr = exchange(nums, numsSize, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    log("%d ", arr[i]);
  }
  log("\n");
  // free memory
  free(arr);
  arr = NULL;
  free(nums);
  nums = NULL;
  return 0;
}

