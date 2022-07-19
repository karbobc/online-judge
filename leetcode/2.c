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
 * Give two non-empty linked lists representing two non-negative integers.
 * The digits are stored in reverse order,
 * and each of their nodes contains a single digit.
 * Add the two numbers and return the sum as a linked list.
 */
ListNode* addTwoNumbers(ListNode* list1, ListNode* list2) {
  // define
  int carry = 0;
  ListNode* head = (ListNode*) calloc(1, sizeof(ListNode));
  ListNode* list = head;
  // add the two numbers
  while (list1 != NULL || list2 != NULL) {
    int val1 = list1 != NULL ? list1->val : 0;
    int val2 = list2 != NULL ? list2->val : 0;
    int val = val1 + val2 + carry;
    ListNode* node = (ListNode*) calloc(1, sizeof(ListNode));
    node->val = val % 10;
    node->next = list->next;
    list->next = node;
    carry = val / 10;
    if (list1 != NULL) {
      list1 = list1->next;
    }
    if (list2 != NULL) {
      list2 = list2->next;
    }
    list = list->next;
  }
  if (carry) {
    ListNode* node = (ListNode*) calloc(1, sizeof(ListNode));
    node->val = carry;
    node->next = list->next;
    list->next = node;
  }
  // free the head node and then return.
  ListNode* node = head;
  head = head->next;
  free(node);
  return head;
}

int main() {
  // define
  int val;
  int m, n;
  ListNode* list = NULL;
  ListNode* head1 = (ListNode*) calloc(1, sizeof(ListNode));
  ListNode* head2 = (ListNode*) calloc(1, sizeof(ListNode));
  ListNode* list1 = head1;
  ListNode* list2 = head2;
  // input
  scanf("%d %d", &m , &n);
  while (m--) {
    scanf("%d", &val);
    ListNode* node = (ListNode*) calloc(1, sizeof(ListNode));
    node->val = val;
    node->next = list1->next;
    list1->next = node;
    list1 = list1->next;
  }
  while (n--) {
    scanf("%d", &val);
    ListNode* node = (ListNode*) calloc(1, sizeof(ListNode));
    node->val = val;
    node->next = list2->next;
    list2->next = node;
    list2 = list2->next;
  }
  // output
  list = addTwoNumbers(head1->next, head2->next);
  while (list != NULL) {
    log("%d", list->val);
    ListNode* node = list;
    list = list->next;
    free(node);
  }
  log("\n");
  // free memory
  list1 = head1;
  while (list1 != NULL) {
    ListNode* node = list1;
    list1 = list1->next;
    free(node);
  }
  list2 = head2;
  while (list2 != NULL) {
    ListNode* node = list2;
    list2 = list2->next;
    free(node);
  }
  return 0;
}

