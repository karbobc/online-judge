#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (3e4 + 4)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)
#define max(a, b) (a >= b ? a : b)

typedef struct {
  int top;
  int size;
  int capacity;
  int* data;
} Stack;

Stack* stackCreate() {
  Stack* stack = malloc(sizeof(*stack));
  stack->top = -1;
  stack->size = 0;
  stack->capacity = 1 << 4;
  stack->data = malloc(stack->capacity * sizeof(*(stack->data)));
  return stack;
}

bool isStackFull(Stack* stack) {
  return stack->size == stack->capacity;
}

bool isStackEmpty(Stack* stack) {
  return stack->size == 0;
}

void stackPush(Stack* stack, int data) {
  if (isStackFull(stack)) {
    stack->capacity += stack->capacity;
    int* a = malloc(stack->capacity * sizeof(*a));
    memcpy(a, stack->data, stack->size * sizeof(*a));
    free(stack->data);
    stack->data = a;
  }
  stack->data[++stack->top] = data;
  stack->size++;
}

int stackPop(Stack* stack) {
  int data = stack->data[stack->top--];
  stack->size--;
  return data;
}

int stackPeek(Stack* stack) {
  return stack->data[stack->top];
}

void stackFree(Stack* stack) {
  while (!isStackEmpty(stack)) {
    stackPop(stack);
  }
  free(stack->data);
  free(stack);
}

int longestValidParentheses(char* s) {
  int ans = 0;
  int n = strlen(s);
  Stack* stack = stackCreate();
  stackPush(stack, -1);
  for (int i = 0; i < n; i++) {
    if (s[i] == '(') {
      stackPush(stack, i);
      continue;
    }
    stackPop(stack);
    if (isStackEmpty(stack)) {
      stackPush(stack, i);
      continue;
    }
    ans = max(ans, i - stackPeek(stack));
  }
  stackFree(stack);
  return ans;
}

int main() {
  char* s = malloc(MAX_SIZE * sizeof(*s));
  fgets(s, MAX_SIZE, stdin);
  s[strlen(s)-1] = '\0';
  log("%d\n", longestValidParentheses(s));
  free(s);
  return 0;
}

