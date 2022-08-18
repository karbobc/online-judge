#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (5e4 + 4)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

int majorityElement(int* nums, int numsSize) {
  int vote;
  int cnt = 0;
  for (int i = 0; i < numsSize; i++) {
    if (cnt == 0) {
      vote = nums[i];
    }
    vote == nums[i] ? cnt++ : cnt--;
  }
  return vote;
}

int main() {
  int numsSize;
  int* nums = malloc(MAX_SIZE * sizeof(*nums));
  scanf("%d", &numsSize);
  for (int i = 0; i < numsSize; i++) {
    scanf("%d", &nums[i]);
  }
  log("%d\n", majorityElement(nums, numsSize));
  free(nums);
  return 0;
}

