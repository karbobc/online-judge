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
 * Given a linked list and a node value,
 * delete the node from the linked list.
 */
List* deleteNode(List* head, int val) {
  List* list = head;
  if (list->val == val) {
    ListNode* node = list;
    list = list->next;
    debug("deleted %d", node->val);
    free(node);
    node = NULL;
    return list;
  }
  while (list->next != NULL) {
    if (list->next->val == val) {
      ListNode* node = list->next;
      list->next = list->next->next;
      debug("deleted %d", node->val);
      free(node);
      node = NULL;
      break;
    }
    list = list->next;
  }
  return head;
}

int main() {
  // define
  int n;
  int val;
  List* head = malloc(sizeof(*head));
  head->next = NULL;
  List* list = head;
  // input
  scanf("%d %d", &n, &val);
  while (n-- > 0) {
    ListNode* node = malloc(sizeof(*node));
    scanf("%d", &node->val);
    node->next = list->next;
    list->next = node;
    list = list->next;
  }
  // output
  list = deleteNode(head->next, val);
  while (list != NULL) {
    log("%d ", list->val);
    list = list->next;
  }
  log("\n");
  // free memory
  list = head;
  while (list != NULL) {
    ListNode* node = list;
    list = list->next;
    debug("deleted %d", node->val);
    free(node);
    node = NULL;
  }
  list = NULL;
  head = NULL;
  return 0;
}

