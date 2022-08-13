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

List* rotateRight(List* head1, int k) {
  int n = 0;
  List* list1 = head1;
  while (list1 != NULL) {
    n++;
    list1 = list1->next;
  }
  if (n == 0 || k%n == 0) {
    return head1;
  }
  k %= n;
  list1 = head1;
  int i = n-k;
  while (--i > 0) {
    list1 = list1->next;
  }
  List* list2 = list1->next;
  List* head2 = list2;
  list1->next = NULL;
  while (list2->next != NULL) {
    list2 = list2->next;
  }
  list2->next = head1;
  return head2;
}

int main() {
  // define
  int n, k;
  List* head1 = malloc(sizeof(*head1));
  head1->next = NULL;
  List* list1 = head1;
  List* head2 = NULL;
  List* list2 = NULL;
  // input
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i++) {
    ListNode* node = malloc(sizeof(*node));
    scanf("%d", &node->val);
    node->next = list1->next;
    list1->next = node;
    list1 = list1->next;
  }
  // output and free memory
  head2 = rotateRight(head1->next, k);
  list2 = head2;
  while (list2 != NULL) {
    ListNode* node = list2;
    log("%d ", node->val);
    list2 = list2->next;
    free(node);
  }
  log("\n");
  free(head1);
  return 0;
}

