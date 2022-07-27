#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (5e3 + 3)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * Given a `nums` array in ascending order that may exist repeat value,
 * now rotate the array, return the minimum value in the array.
 * eg. Rotate 1 times,
 * Old: a[0], a[1], ..., a[n-1]
 * New: a[n-1], a[0], a[1], ..., a[n-2]
 */
int minArray(int* nums, int numsSize) {
  int left = 0;
  int right = numsSize - 1;
  while (left < right) {
    int mid = (left + right) >> 1;
    if (nums[mid] < nums[right]) {
      right = mid;
      continue;
    }
    if (nums[mid] > nums[right]) {
      left = mid + 1;
      continue;
    }
    right--;
  }
  return nums[left];
}

int main() {
  // define
  int numsSize;
  int* nums = malloc(MAX_SIZE * sizeof(*nums));
  // input
  scanf("%d", &numsSize);
  for (int i = 0; i < numsSize; i++) {
    scanf("%d", &nums[i]);
  }
  // output
  log("%d\n", minArray(nums, numsSize));
  // free memory
  free(nums);
  nums = NULL;
  return 0;
}

