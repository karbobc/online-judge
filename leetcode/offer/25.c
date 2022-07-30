#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 0x3f3f3f3f
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct ListNode {
  int val;
  struct ListNode* next;
} ListNode, List;

/**
 * Given two linked lists `list1` and `list2` that in ascending order.
 * Merge the two linked lists become a new linked `list` that also in ascending order.
 */
List* mergeTwoLists(List* list1, List* list2) {
  List* head = malloc(sizeof(*head));
  List* list = head;
  head->next = NULL;
  // merge two lists
  while (list1 != NULL && list2 != NULL) {
    // append the minimum node into list.
    if (list1->val < list2->val) {
      list->next = list1;
      list1 = list1->next;
    } else {
      list->next = list2;
      list2 = list2->next;
    }
    list = list->next;
  }
  // merge the non NULL linked list.
  list->next = list1 != NULL ? list1 : list2;
  // free the head node that don't have any value.
  ListNode* temp = head;
  head = head->next;
  free(temp);
  temp = NULL;
  // return the list
  return head;
}

int main() {
  // define
  int m, n;
  List* head1 = malloc(sizeof(*head1));
  head1->next = NULL;
  List* list1 = head1;
  List* head2 = malloc(sizeof(*head2));
  head2->next = NULL;
  List* list2 = head2;
  // input
  scanf("%d %d", &m, &n);
  while (m-- > 0) {
    ListNode* node = malloc(sizeof(*node));
    scanf("%d", &node->val);
    node->next = list1->next;
    list1->next = node;
    list1 = list1->next;
  }
  while (n-- > 0) {
    ListNode* node = malloc(sizeof(*node));
    scanf("%d", &node->val);
    node->next = list2->next;
    list2->next = node;
    list2 = list2->next;
  }
  // output and free memory
  List* list = mergeTwoLists(head1->next, head2->next);
  while (list != NULL) {
    ListNode* node = list;
    list = list->next;
    log("%d ", node->val);
    free(node);
    node = NULL;
  }
  log("\n");
  free(head1);
  head1 = NULL;
  free(head2);
  head2 = NULL;
  list1 = NULL;
  list2 = NULL;
  list = NULL;
  return 0;
}

