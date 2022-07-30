#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct ListNode {
  int val;
  struct ListNode* next;
} ListNode, List;

/**
 * Given a linked list, reverse all the nodes.
 */
List* reverseList(List* head) {
  List* list = NULL;
  List* curr = head;
  while (curr != NULL) {
    ListNode* node = curr->next;
    curr->next = list;
    list = curr;
    curr = node;
  }
  return list;
}

int main() {
  // define
  int n;
  List* head = malloc(sizeof(*head));
  List* list = head;
  head->next = NULL;
  // input
  scanf("%d", &n);
  while (n-- > 0) {
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
    list = node->next;
    log("%d ", node->val);
    free(node);
  }
  log("\n");
  free(head);
  head = NULL;
  list = NULL;
  return 0;
}

