#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define COLUMN_SIZE 3
#define INF 0x3f3f3f3f
#define MAX_SIZE 1e3 + 3
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

/**
 * Quick sort.
 */
void sort(int* arr, int l, int r) {
  if (l >= r) return;
  int i = l;
  int j = r;
  int pivot = arr[l];
  while (i < j) {
    while (i < j && arr[j] >= pivot) {
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

/**
 * Given an integer array `nums` of length `n` and an integer `target`,
 * find three integers such that the sum is closest to `target`.
 * Return the sum of the three integers.
 */
int threeSumClosest(int* nums, int n, int target) {
  // define
  int ret = INF;
  // sort for `nums array`
  sort(nums, 0, n-1);
  // find the closest three integers
  for (int i = 0; i < n - (COLUMN_SIZE-1); i++) {
    int l = i + 1;
    int r = n - 1;
    while (l < r) {
      int sum = nums[i] + nums[l] + nums[r];
      if (sum == target) {
        return sum;
      }
      if (abs(target-ret) > abs(target-sum)) {
        ret = sum;
      }
      sum < target ? l++ : r--;
    }

  }
  return ret;
}

int main() {
  // define
  int n;
  int target;
  int* nums = (int*) malloc(MAX_SIZE * sizeof(int));
  // input
  scanf("%d %d", &n, &target);
  for (int i = 0; i < n; i++) {
    scanf("%d", &nums[i]);
  }
  // output
  log("%d\n", threeSumClosest(nums, n, target));
  // free memory
  free(nums);
  return 0;
}

