#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)
#define min(a, b) (a < b ? a : b)

typedef struct StackNode {
  int val;
  struct StackNode* next;
} StackNode, Stack;

typedef struct {
  Stack* s1;
  Stack* s2;
} MinStack;

Stack* stackCreate() {
  Stack* stack = malloc(sizeof(*stack));
  stack->next = NULL;
  return stack;
}

bool isStackEmpty(Stack* stack) {
  return stack->next == NULL;
}

void stackPush(Stack* stack, int val) {
  StackNode* node = malloc(sizeof(*node));
  node->val = val;
  node->next = stack->next;
  stack->next = node;
}

void stackPop(Stack* stack) {
  if (isStackEmpty(stack)) {
    return;
  }
  StackNode* node = stack->next;
  stack->next = node->next;
  free(node);
}

int stackPeek(Stack* stack) {
  return stack->next->val;
}

void stackFree(Stack* stack) {
  while (!isStackEmpty(stack)) {
    stackPop(stack);
  }
  free(stack);
}

MinStack* minStackCreate() {
  MinStack* stack = malloc(sizeof(*stack));
  stack->s1 = stackCreate();
  stack->s2 = stackCreate();
  return stack;
}

void minStackPush(MinStack* stack, int val) {
  stackPush(stack->s1, val);
  stackPush(stack->s2, isStackEmpty(stack->s2) ? val : min(val, stackPeek(stack->s2)));
}

void minStackPop(MinStack* stack) {
  stackPop(stack->s1);
  stackPop(stack->s2);
}

int minStackTop(MinStack* stack) {
  return stackPeek(stack->s1);
}

int minStackGetMin(MinStack* stack) {
  return stackPeek(stack->s2);
}

void minStackFree(MinStack* stack) {
  stackFree(stack->s1);
  stackFree(stack->s2);
  free(stack);
}

int main() {
  return 0;
}

