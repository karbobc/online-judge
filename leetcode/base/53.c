#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (1e5 + 5)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)
#define max(a, b) (a >= b ? a : b)

int maxSubArray(int* nums, int numsSize) {
  int sum = 0;
  int ret = nums[0];
  for (int i = 0; i < numsSize; i++) {
    sum = max(sum+nums[i], nums[i]);
    ret = max(ret, sum);
  }
  return ret;
}

int main() {
  int numsSize;
  int* nums = malloc(MAX_SIZE * sizeof(*nums));
  scanf("%d", &numsSize);
  for (int i = 0; i < numsSize; i++) {
    scanf("%d", &nums[i]);
  }
  log("%d\n", maxSubArray(nums, numsSize));
  free(nums);
  return 0;
}

