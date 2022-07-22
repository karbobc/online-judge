#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE (1e4 + 4)
#define INF 0x3f3f3f3f
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct ListNode ListNode;
typedef ListNode Stack;
struct ListNode {
  int val;
  ListNode* next;
};

/**
 * Determine whether the stack is empty.
 */
bool isEmpty(Stack* stack) {
  return stack->next == NULL;
}

/**
 * Push a `val` into the stack.
 */
void Spush(Stack* stack, int val) {
  Stack* node = malloc(sizeof(*node));
  node->val = val;
  node->next = stack->next;
  stack->next = node;
}

/**
 * Pop a `val` from the stack.
 */
int Spop(Stack* stack) {
  if (isEmpty(stack)) {
    return INF;
  }
  Stack* node = stack->next;
  int val = node->val;
  stack->next = node->next;
  free(node);
  node = NULL;
  return val;
}

/**
 * Given a linked list `head` node, reverse all the node values.
 */
int* reversePrint(ListNode* head, int* returnSize) {
  // define
  *returnSize = 0;
  int* arr = malloc(MAX_SIZE * sizeof(*arr));
  Stack* stack = malloc(sizeof(*stack));
  stack->next = NULL;
  // push into stack
  while (head != NULL) {
    Spush(stack, head->val);
    head = head->next;
  }
  // pop from stack
  while (!isEmpty(stack)) {
    arr[(*returnSize)++] = Spop(stack);
  }
  // free
  free(stack);
  stack = NULL;
  return arr;
}

int main() {
  // define
  int m, val;
  int returnSize;
  int* arr = NULL;
  ListNode* head = malloc(sizeof(*head));
  ListNode* list = head;
  head->next = NULL;
  // input
  scanf("%d", &m);
  while (m-- > 0) {
    scanf("%d", &val);
    ListNode* node = malloc(sizeof(*node));
    node->val = val;
    node->next = list->next;
    list->next = node;
    list = list->next;
  }
  // output
  arr = reversePrint(head->next, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    log("%d ", arr[i]);
  }
  log("\n");
  // free memroy
  free(arr);
  arr = NULL;
  while (head != NULL) {
    ListNode* node = head;
    head = head->next;
    free(node);
    node = NULL;
  }
  return 0;
}

