#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct ListNode {
  int val;
  struct ListNode* next;
} ListNode;

/**
 * Given a linked list, return the Penultimate `k` node in the linked list.
 */
ListNode* getKthFromEnd(ListNode* head, int k) {
  // i is the length of the linked list.
  int i = 0;
  ListNode* list = head;
  // calculate the length of the linked list.
  while (list != NULL) {
    i++;
    list = list->next;
  }
  // find the result.
  list = head;
  while ((i - k) > 0) {
    i--;
    list = list->next;
  }
  return list;
}

int main() {
  // define
  int n, k;
  int val;
  ListNode* head = malloc(sizeof(*head));
  ListNode* list = head;
  head->next = NULL;
  // input
  scanf("%d %d", &n, &k);
  while (n-- > 0) {
    scanf("%d", &val);
    ListNode* node = malloc(sizeof(*node));
    node->val = val;
    node->next = list->next;
    list->next = node;
    list = list->next;
  }
  // output
  list = getKthFromEnd(head->next, k);
  while (list != NULL) {
    log("%d ", list->val);
    list = list->next;
  }
  log("\n");
  // free memory
  while (head != NULL) {
    ListNode* node = head;
    head = node->next;
    free(node);
    debug("%p", node);
  }
  head = NULL;
  list = NULL;
  return 0;
}

