#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct ListNode {
  int val;
  struct ListNode* next;
} ListNode, List;

List* reverseList(List* head) {
  List* prev = NULL;
  List* curr = head;
  while (curr != NULL) {
    ListNode* node = curr->next;
    curr->next = prev;
    prev = curr;
    curr = node;
  }
  return prev;
}

int main() {
  // define
  int n;
  List* head = malloc(sizeof(*head));
  head->next = NULL;
  List* list = head;
  // input
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    ListNode* node = malloc(sizeof(*node));
    scanf("%d", &node->val);
    node->next = list->next;
    list->next = node;
    list = list->next;
  }
  // output and free memory
  list = reverseList(head->next);
  while (list != NULL) {
    ListNode* node = list;
    log("%d ", node->val);
    list = list->next;
    free(node);
  }
  log("\n");
  free(head);
  return 0;
}

