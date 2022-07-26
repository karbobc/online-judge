#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE 1024
#define QUEUE_CREATE "CQueue"
#define QUEUE_PUSH "appendTail"
#define QUEUE_POP "deleteHead"
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct StackNode StackNode;
typedef StackNode Stack;
struct StackNode {
  int val;
  StackNode* next;
};

typedef struct {
  Stack* s1;
  Stack* s2;
} CQueue;

/**
 * True is returned when the stack is empty.
 */
bool isStackEmpty(Stack* stack) {
  return stack->next == NULL;
}

/**
 * Push a node into the stack.
 */
void sPush(Stack* stack, int val) {
  StackNode* node = malloc(sizeof(*node));
  node->val = val;
  node->next = stack->next;
  stack->next = node;
}

/**
 * Pop a node from the stack.
 */
int sPop(Stack* stack) {
  if (isStackEmpty(stack)) {
    return -1;
  }
  StackNode* node = stack->next;
  int val = node->val;
  stack->next = node->next;
  free(node);
  node = NULL;
  return val;
}

/**
 * Create a queue.
 */
CQueue* cQueueCreate() {
  CQueue* queue = malloc(sizeof(*queue));
  queue->s1 = malloc(sizeof(*(queue->s1)));
  queue->s1->next = NULL;
  queue->s2 = malloc(sizeof(*(queue->s2)));
  queue->s2->next = NULL;
  return queue;
}

/**
 * Append a node into the queue.
 */
void cQueueAppendTail(CQueue* queue, int val) {
  sPush(queue->s1, val);
}

/**
 * Delete a node from the queue.
 */
int cQueueDeleteHead(CQueue* queue) {
  if (isStackEmpty(queue->s1) && isStackEmpty(queue->s2)) {
    return -1;
  }
  if (isStackEmpty(queue->s2)) {
    while (!isStackEmpty(queue->s1)) {
      sPush(queue->s2, sPop(queue->s1));
    }
  }
  return sPop(queue->s2);
}

/**
 * Delete the queue.
 */
void cQueueFree(CQueue* queue) {
  free(queue->s1);
  queue->s1 = NULL;
  free(queue->s2);
  queue->s2 = NULL;
  free(queue);
  queue = NULL;
}

int main() {
  // define
  int m;
  int val;
  CQueue* queue;
  char* s = malloc(sizeof(*s));
  // input and output
  scanf("%d", &m);
  while (m-- > 0) {
    scanf("%s", s);
    if (strcmp(QUEUE_CREATE, s) == 0) {
      queue = cQueueCreate();
      log("null ");
      continue;
    }
    if (strcmp(QUEUE_PUSH, s) == 0) {
      scanf("%d", &val);
      cQueueAppendTail(queue, val);
      log("null ");
      continue;
    }
    if (strcmp(QUEUE_POP, s) == 0) {
      log("%d ", cQueueDeleteHead(queue));
    }
  }
  log("\n");
  // free memory
  cQueueDeleteHead(queue);
  free(s);
  s = NULL;
  return 0;
}

