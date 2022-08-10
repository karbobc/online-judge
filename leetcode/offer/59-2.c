#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE (1e4 + 4)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct DequeNode {
  int data;
  struct DequeNode* prev;
  struct DequeNode* next;
} DequeNode;

typedef struct {
  DequeNode* front;
  DequeNode* rear;
} Deque;

typedef struct QueueNode {
  int data;
  struct QueueNode* next;
} QueueNode;

typedef struct {
  QueueNode* front;
  QueueNode* rear;
} Queue;

typedef struct {
  Deque* deque;
  Queue* queue;
} MaxQueue;

Deque* dequeCreate() {
  Deque* deque = malloc(sizeof(*deque));
  deque->front = NULL;
  deque->rear = NULL;
  return deque;
}

bool isDequeEmpty(Deque* deque) {
  return deque->front == NULL && deque->rear == NULL;
}

void dequePush(Deque* deque, int data) {
  DequeNode* node = malloc(sizeof(*node));
  node->data = data;
  if (isDequeEmpty(deque)) {
    node->next = NULL;
    node->prev = NULL;
    deque->front = node;
    deque->rear = node;
    return;
  }
  node->prev = deque->rear;
  node->next = deque->rear->next;
  deque->rear->next = node;
  deque->rear = deque->rear->next;
}

void dequePopFirst(Deque* deque) {
  if (isDequeEmpty(deque)) {
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
  node = NULL;
}

void dequePopLast(Deque* deque) {
  if (isDequeEmpty(deque)) {
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
  node = NULL;
}

int dequePeekFirst(Deque* deque) {
  if (isDequeEmpty(deque)) {
    return -1;
  }
  return deque->front->data;
}

int dequePeekLast(Deque* deque) {
  if (isDequeEmpty(deque)) {
    return -1;
  }
  return deque->rear->data;
}

void dequeFree(Deque* deque) {
  while (!isDequeEmpty(deque)) {
    dequePopFirst(deque);
  }
  free(deque);
  deque = NULL;
}

Queue* queueCreate() {
  Queue* queue = malloc(sizeof(*queue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

bool isQueueEmpty(Queue* queue) {
  return queue->front == NULL && queue->rear == NULL;
}

void queuePush(Queue* queue, int data) {
  QueueNode* node = malloc(sizeof(*node));
  node->data = data;
  if (isQueueEmpty(queue)) {
    node->next = NULL;
    queue->front = node;
    queue->rear = node;
    return;
  }
  node->next = queue->rear->next;
  queue->rear->next = node;
  queue->rear = queue->rear->next;
}

int queuePop(Queue* queue) {
  if (isQueueEmpty(queue)) {
    return -1;
  }
  QueueNode* node = queue->front;
  int data = node->data;
  if (queue->front == queue->rear) {
    queue->front = NULL;
    queue->rear = NULL;
  } else {
    queue->front = queue->front->next;
  }
  free(node);
  node = NULL;
  return data;
}

void queueFree(Queue* queue) {
  while (!isQueueEmpty(queue)) {
    queuePop(queue);
  }
  free(queue);
  queue = NULL;
}

MaxQueue* maxQueueCreate() {
  MaxQueue* maxque = malloc(sizeof(*maxque));
  maxque->deque = dequeCreate();
  maxque->queue = queueCreate();
  return maxque;
}

int maxQueueMax_value(MaxQueue* maxque) {
  return dequePeekFirst(maxque->deque);
}

void maxQueuePush_back(MaxQueue* maxque, int value) {
  while (!isDequeEmpty(maxque->deque) && value > dequePeekLast(maxque->deque)) {
    dequePopLast(maxque->deque);
  }
  dequePush(maxque->deque, value);
  queuePush(maxque->queue, value);
}

int maxQueuePop_front(MaxQueue* maxque) {
  if (isQueueEmpty(maxque->queue)) {
    return -1;
  }
  int value = queuePop(maxque->queue);
  if (value == dequePeekFirst(maxque->deque)) {
    dequePopFirst(maxque->deque);
  }
  return value;
}

void maxQueueFree(MaxQueue* maxque) {
  dequeFree(maxque->deque);
  queueFree(maxque->queue);
  free(maxque);
  maxque = NULL;
}

int main() {
  return 0;
}

