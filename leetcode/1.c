#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)


int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* arr = (int *) calloc(*returnSize, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        for(int j = i+1; j < numsSize; j++) {
            if (target == nums[i] + nums[j]) {
                *arr = i;
                *(arr+1) = j;
            }
        }
    }
    return arr;
}

int main(int args, char* argv[]) {
    // define
    int numsSize, target;
    int* nums;
    int* returnSize;
    int* arr;
    // input
    scanf("%d %d", &numsSize, &target);
    nums = (int *) calloc(numsSize, sizeof(int));
    returnSize = (int *) malloc(1 * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        scanf("%d", nums + i);
    }
    // output
    arr = twoSum(nums, numsSize, target, returnSize);
    log("%d %d\n", *arr, *(arr+1));
    // free memory
    free(nums);
    free(returnSize);
    free(arr);
    return 0;
}

