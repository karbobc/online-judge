#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 1e5 + 5
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * Given a `nums` array, find the duplicate integer in the arrary.
 */
int findRepeatNumber(int* nums, int numsSize) {
  int* set = calloc(MAX_SIZE, sizeof(*set));
  for (int i = 0; i < numsSize; i++) {
    set[nums[i]]++;
    if (set[nums[i]] > 1) {
      free(set);
      set = NULL;
      return nums[i];
    }
  }
  free(set);
  set = NULL;
  return INT_MAX;
}

int main() {
  // define
  int n;
  int* nums = malloc(MAX_SIZE * sizeof(*nums));
  // input
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }
  // output
  log("%d\n", findRepeatNumber(nums, n));
  // free memory
  free(nums);
  nums = NULL;
  return 0;
}

