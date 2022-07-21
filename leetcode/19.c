#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct ListNode ListNode;
struct ListNode {
  int val;
  ListNode* next;
};

/**
 * Given the `head` of linked list, remove the `nth` node from
 * the end of the list and return it's head.
 */
ListNode* removeNthFromEnd(ListNode* head, int n) {
  // define
  ListNode* list = head;
  int len = 0;
  // calculate the length of the linked list
  while (list != NULL) {
    len++;
    list = list->next;
  }
  // remove the head node
  if (len - n == 0) {
    ListNode* node = head;
    head = head->next;
    free(node);
    return head;
  }
  // remove the `nth` node
  list = head;
  for (int i = 0; i < len - n - 1; i++) {
    list = list->next;
  }
  ListNode* node = list->next;
  list->next = list->next->next;
  free(node);
  return head;
}

int main() {
  // define
  int val;
  int m, n;
  ListNode* head = (ListNode*) calloc(1, sizeof(ListNode));
  ListNode* list = head;
  // input
  scanf("%d %d", &m, &n);
  for (int i = 0; i < m; i++) {
    scanf("%d", &val);
    ListNode* node = (ListNode*) calloc(1, sizeof(ListNode));
    node->val = val;
    node->next = list->next;
    list->next = node;
    list = list->next;
  }
  // output
  ListNode* temp = head;
  head = head->next;
  free(temp);
  head = removeNthFromEnd(head, n);
  while (head != NULL) {
    ListNode* node = head;
    log("%d\n", node->val);
    head = head->next;
    free(node);
  }
  return 0;
}
