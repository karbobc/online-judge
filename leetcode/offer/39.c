#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

#define MAX_SIZE (5e4 + 4)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct HashMap {
  int key;
  uint value;
  UT_hash_handle hh;
} HashMap, MapItem;

int majorityElement(int* nums, int numsSize) {
  int ret = *nums;
  int maxCount = 0;
  HashMap* map = NULL;
  MapItem* item = NULL;
  for (int i = 0; i < numsSize; i++) {
    HASH_FIND_INT(map, &nums[i], item);
    if (item == NULL) {
      item = malloc(sizeof(*item));
      item->key = nums[i];
      item->value = 0;
      HASH_ADD_INT(map, key, item);
    }
    item->value++;
    if (item->value > maxCount) {
      ret = item->key;
      maxCount = item->value;
    }
  }
  MapItem* temp = NULL;
  HASH_ITER(hh, map, item, temp) {
    HASH_DEL(map, item);
    free(item);
    item = NULL;
  }
  return ret;
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
  log("%d\n", majorityElement(nums, numsSize));
  // free memory
  free(nums);
  nums = NULL;
  return 0;
}

