#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct StackNode {
  int val;
  int min;
  struct StackNode* next;
} StackNode, MinStack;

MinStack* minStackCreate() {
  MinStack* stack = malloc(sizeof(*stack));
  stack->next = NULL;
  return stack;
}

bool minStackEmpty(MinStack* stack) {
  return stack->next == NULL;
}

void minStackPush(MinStack* stack, int val) {
  StackNode* node = malloc(sizeof(*node));
  node->val = val;
  if (minStackEmpty(stack) || val <= stack->min) {
    stack->min = val;
    node->min = val;
  } else {
    node->min = stack->next->min;
  }
  node->next = stack->next;
  stack->next = node;
}

void minStackPop(MinStack* stack) {
  if (minStackEmpty(stack)) {
    return;
  }
  StackNode* node = stack->next;
  if (node->val == stack->min && node->next != NULL) {
    stack->min = node->next->min;
  }
  stack->next = node->next;
  free(node);
  node = NULL;
}

int minStackTop(MinStack* stack) {
  return stack->next->val;
}

int minStackMin(MinStack* stack) {
  return stack->min;
}

void minStackFree(MinStack* stack) {
  free(stack);
  stack = NULL;
}

int main() {
  return 0;
}

