#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5e1 + 1
#define INF 0x3f3f3f3f
#define log(S, ...) printf(S, ##__VA_ARGS__)

typedef struct ListNode ListNode;
struct ListNode {
    int val;
    ListNode* next;
};

/**
 * create a node
 */
ListNode* createNode() {
    ListNode* node = (ListNode*) malloc(sizeof(ListNode));
    node->next = NULL;
    node->val = INF;
    return node;
}

/**
 * merge two asc order list
 */
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    ListNode* head = createNode();
    ListNode* list = head;
    while (list1 != NULL && list2 != NULL) {
        if (list1->val < list2->val) {
            list->next = list1;
            list1 = list1->next;
        } else {
            list->next = list2;
            list2 = list2->next;
        }
        list = list->next;
    }
    list->next = list1 == NULL ? list2 : list1;
    return head->next;
}

int main() {
    // define
    int m, n;
    int val;
    ListNode* head = NULL;
    ListNode* list = NULL;
    ListNode* head1 = NULL;
    ListNode* head2 = NULL;
    ListNode* list1 = NULL;
    ListNode* list2 = NULL;
    // input
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        scanf("%d", &val);
        if (i == 0) {
            head1 = createNode();
            list1 = head1;
            list1->val = val;
            continue;
        }
        ListNode* node = createNode();
        node->val = val;
        list1->next = node;
        list1 = list1->next;
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        if (i == 0) {
            head2 = createNode();
            list2 = head2;
            list2->val = val;
            continue;
        }
        ListNode* node = createNode();
        node->val = val;
        list2->next = node;
        list2 = list2->next;
    }
    // output
    head = mergeTwoLists(head1, head2);
    list = head;
    while (list != NULL) {
        printf("%d ", list->val);
        list = list->next;
    }
    printf("\n");
    // free memory
    while (head != NULL) {
        ListNode* node = head;
        head = head->next;
        free(node);
    }
    return 0;
}
