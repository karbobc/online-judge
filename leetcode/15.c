#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 1e6 + 3
#define COLUMN_SIZE 3
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * Quick sort
 */
void sort(int* arr, int l, int r) {
  if (l < r) {
    int pivot = arr[l];
    int i = l, j = r;
    while (i < j) {
      while(i < j && arr[j] >= pivot) {
        j--;
      }
      arr[i] = arr[j];
      while (i < j && arr[i] <= pivot) {
        i++;
      }
      arr[j] = arr[i];
    }
    arr[i] = pivot;
    sort(arr, l, i-1);
    sort(arr, i+1, r);
  }
}

/**
 * Given an integer array nums, return all the triplets
 * `nums[i], nums[j], nums[k]` such that `i != j, i != k, j != k`,
 * and `nums[i] + nums[j] + nums[k] = 0`.
 * Note: the solution set must not contain duplicate triplets.
 */
int** threeSum(int* nums, const int numsSize, int* returnSize, int** columnSizes) {
  // initialize `returnSize` variable to 0
  *returnSize = 0;
  // directly return when `numsSize` less than 3
  if (numsSize < 3) {
    return NULL;
  }
  // define
  int** arr = (int**) malloc(MAX_SIZE * sizeof(int*));
  *columnSizes = (int*) malloc(MAX_SIZE * sizeof(int));
  // use quick sort for `nums` array
  sort(nums, 0, numsSize-1);
  // find the solution set
  for (int i = 0; i < numsSize - (COLUMN_SIZE-1) && nums[i] <= 0; i++) {
    // can't contain duplicate numbers on the previous
    if (i > 0 && nums[i] == nums[i-1]) {
      continue;
    }
    int l = i + 1;
    int r = numsSize - 1;
    while (l < r) {
      if (nums[i] + nums[l] + nums[r] < 0) {
        l++;
        continue;
      }
      if (nums[i] + nums[l] + nums[r] > 0) {
        r--;
        continue;
      }
      arr[*returnSize] = (int*) malloc(COLUMN_SIZE * sizeof(int));
      arr[*returnSize][0] = nums[i];
      arr[*returnSize][1] = nums[l];
      arr[*returnSize][2] = nums[r];
      (*columnSizes)[(*returnSize)++] = COLUMN_SIZE;
      // remove duplicate numbers on the next
      while (l < r && nums[l] == nums[l+1]) {
        l++;
      }
      while (l < r && nums[r] == nums[r-1]) {
        r--;
      }
      l++;
      r--;
    }
  }
  return arr;
}

int main() {
  // define
  int numsSize, returnSize;
  int** arr = NULL;
  int* columnSizes = NULL;
  int* nums = (int*) malloc(MAX_SIZE * sizeof(int));
  // input
  scanf("%d", &numsSize);
  for (int i = 0; i < numsSize; i++) {
    scanf("%d", &nums[i]);
  }
  // output
  arr = threeSum(nums, numsSize, &returnSize, &columnSizes);
  for (int i = 0; i < returnSize; i++) {
    for (int j = 0; j < columnSizes[i]; j++) {
      log("%d ", arr[i][j]);
    }
    log("\n");
  }
  // free memory
  for (int i = 0; i < returnSize; i++) {
    free(arr[i]);
  }
  if (arr != NULL) {
    free(arr);
  }
  if (columnSizes != NULL) {
    free(columnSizes);
  }
  free(nums);
  return 0;
}

