#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE (1e5 + 5)
#define INF 0x3f3f3f3f
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)
#define max(a, b) (a > b ? a : b)

typedef struct DequeNode {
  int val;
  struct DequeNode* prev;
  struct DequeNode* next;
} DequeNode;

typedef struct {
  DequeNode* front;
  DequeNode* rear;
} Deque;

Deque* createQueue() {
  Deque* deque = malloc(sizeof(*deque));
  deque->front = NULL;
  deque->rear = NULL;
  return deque;
}

bool isQueueEmpty(Deque* deque) {
  return deque->front == NULL && deque->rear == NULL;
}

void push(Deque* deque, int val) {
  DequeNode* node = malloc(sizeof(*node));
  node->val = val;
  if (isQueueEmpty(deque)) {
    node->prev = NULL;
    node->next = NULL;
    deque->front = node;
    deque->rear = node;
    return;
  }
  node->prev = deque->rear;
  node->next = deque->rear->next;
  deque->rear->next = node;
  deque->rear = deque->rear->next;
}

void popFirst(Deque* deque) {
  if (isQueueEmpty(deque)) {
    return;
  }
  DequeNode* node = deque->front;
  if (deque->front == deque->rear) {
    deque->front = NULL;
    deque->rear = NULL;
  } else {
    deque->front = node->next;
    deque->front->prev = node->prev;
  }
  free(node);
}

void popLast(Deque* deque) {
  if (isQueueEmpty(deque)) {
    return;
  }
  DequeNode* node = deque->rear;
  if (deque->front == deque->rear) {
    deque->front = NULL;
    deque->rear = NULL;
  } else {
    deque->rear = node->prev;
    deque->rear->next = node->next;
  }
  free(node);
}

int peekFirst(Deque* deque) {
  return deque->front->val;
}

int peekLast(Deque* deque) {
  return deque->rear->val;
}

void freeQueue(Deque* deque) {
  while (!isQueueEmpty(deque)) {
    popFirst(deque);
  }
  free(deque);
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
  *returnSize = 0;
  int* arr = malloc((numsSize+1) * sizeof(*arr));
  if (numsSize == 0) {
    return arr;
  }
  Deque* deque = createQueue();
  for (int i = 0; i < k; i++) {
    while (!isQueueEmpty(deque) && nums[i] > nums[peekLast(deque)]) {
      popLast(deque);
    }
    push(deque, i);
  }
  arr[(*returnSize)++] = nums[peekFirst(deque)];
  for (int i = k; i < numsSize; i++) {
    while (!isQueueEmpty(deque) && nums[i] > nums[peekLast(deque)]) {
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
  free(arr);
  return 0;
}

