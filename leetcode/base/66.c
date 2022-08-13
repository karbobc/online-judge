#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (1e2 + 2)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int* plusOne(int* nums, int numsSize, int* returnSize) {
  int carry = 0;
  *returnSize = numsSize;
  int* arr = malloc((*returnSize) * sizeof(*arr));
  for (int i = numsSize-1; i >= 0; i--) {
    int ret = i == numsSize-1 ? (nums[i] + 1) : (nums[i] + carry);
    arr[i] = ret % 10;
    carry = ret / 10;
  }
  if (carry) {
    (*returnSize)++;
    int* temp = malloc((*returnSize) * sizeof(*temp));
    temp[0] = carry;
    memcpy(temp+1, arr, numsSize * sizeof(*temp));
    free(arr);
    arr = temp;
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
  arr = plusOne(nums, numsSize, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    log("%d ", arr[i]);
  }
  // free memory
  free(nums);
  free(arr);
  return 0;
}

