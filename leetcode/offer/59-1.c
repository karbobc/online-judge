#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE (1e5 + 5)
#define INF 0x3f3f3f3f
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)
#define max(a, b) (a > b ? a : b)

typedef struct Deque {
  int head;
  int tail;
  int size;
  int capacity;
  int* data;
} Deque;

Deque* createQueue() {
  Deque* deque = malloc(sizeof(*deque));
  deque->head = -1;
  deque->tail = -1;
  deque->size = 0;
  deque->capacity = MAX_SIZE;
  deque->data = malloc(deque->capacity * sizeof(*(deque->data)));
  return deque;
}

bool isQueueEmpty(Deque* deque) {
  return deque->size == 0;
}

void push(Deque* deque, int val) {
  deque->tail = (deque->tail + 1) % deque->capacity;
  deque->data[deque->tail] = val;
  if (isQueueEmpty(deque)) {
    deque->head = deque->tail;
  }
  deque->size++;
}

void popFirst(Deque* deque) {
  if (isQueueEmpty(deque)) {
    return;
  }
  deque->size--;
  deque->head = (deque->head + 1) % deque->capacity;
  if (isQueueEmpty(deque)) {
    deque->tail = deque->head;
  }
}

void popLast(Deque* deque) {
  if (isQueueEmpty(deque)) {
    return;
  }
  deque->size--;
  if (--deque->tail < 0) {
    deque->tail += deque->capacity;
  }
  if (isQueueEmpty(deque)) {
    deque->head = deque->tail;
  }
}

int peekFirst(Deque* deque) {
  return deque->data[deque->head];
}

int peekLast(Deque* deque) {
  return deque->data[deque->tail];
}

void freeQueue(Deque* deque) {
  free(deque->data);
  deque->data = NULL;
  free(deque);
  deque = NULL;
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
  *returnSize = 0;
  int* arr = malloc((numsSize+1) * sizeof(*arr));
  if (numsSize == 0) {
    return arr;
  }
  Deque* deque = createQueue();
  for (int i = 0; i < k; i++) {
    while (!isQueueEmpty(deque) && nums[i] >= nums[peekLast(deque)]) {
      popLast(deque);
    }
    push(deque, i);
  }
  arr[(*returnSize)++] = nums[peekFirst(deque)];
  for (int i = k; i < numsSize; i++) {
    while (!isQueueEmpty(deque) && nums[i] >= nums[peekLast(deque)]) {
      popLast(deque);
    }
    push(deque, i);
    while (peekFirst(deque) <= i-k) {
      popFirst(deque);
    }
    arr[(*returnSize)++] = nums[peekFirst(deque)];
  }
  freeQueue(deque);
  return arr;
}

int main() {
  // define
  int k;
  int numsSize;
  int returnSize;
  int* nums = malloc(MAX_SIZE * sizeof(*nums));
  int* arr = NULL;
  // input
  scanf("%d %d", &numsSize, &k);
  for (int i = 0; i < numsSize; i++) {
    scanf("%d", &nums[i]);
  }
  // output
  arr = maxSlidingWindow(nums, numsSize, k, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    log("%d\n", arr[i]);
  }
  // free memory
  free(nums);
  nums = NULL;
  free(arr);
  arr = NULL;
  return 0;
}

