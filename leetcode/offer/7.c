#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "uthash.h"

#define MAX_SIZE (5e3 + 3)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct TreeNode TreeNode;
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
};

typedef struct HashMap {
  int key;
  int value;
  UT_hash_handle hh;
} HashMap;

typedef struct QueueNode QueueNode;
struct QueueNode {
  TreeNode* val;
  QueueNode* next;
};
typedef struct Queue {
  QueueNode* front;
  QueueNode* rear;
} Queue;


/**
 * Build a binary tree by recursive.
 *
 * @param preorder preorder array
 * @param inorder inorder array
 * @param map map[node->val] = index
 * @param root preorder root node index
 * @param left inorder left index
 * @param right inorder right index
 */
TreeNode* build(
    int* preorder,
    int* inorder,
    HashMap* map,
    int root,
    int left,
    int right
 ) {
  if (left > right) {
    return NULL;
  }
  // inorder root node index
  HashMap* item;
  HASH_FIND_INT(map, &preorder[root], item);
  int i = item->value;
  // create a node
  TreeNode* node = malloc(sizeof(*node));
  // the value of the preorder root node
  node->val = preorder[root];
  node->left = build(preorder, inorder, map, root+1, left, i-1);
  node->right = build(preorder, inorder, map, (i-left) + (root+1), i+1, right);
  return node;
}

TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
  // int* map = malloc(inorderSize * sizeof(*map));
  HashMap* map = NULL;
  // create the map for searching the root node quickly
  for (int i = 0; i < inorderSize; i++) {
    HashMap* item = malloc(sizeof(*item));
    item->key = inorder[i];
    item->value = i;
    HASH_ADD_INT(map, key, item);
  }
  // recursive build the binary tree.
  TreeNode* root = build(preorder, inorder, map, 0, 0, inorderSize-1);
  // free and return
  HashMap* item;
  HashMap* temp;
  HASH_ITER(hh, map, item, temp) {
    HASH_DEL(map, item);
    free(item);
    item = NULL;
  }
  return root;
}

/**
 * Return true when the queue is empty, otherwise, false is returned.
 */
bool isQueueEmpty(Queue* queue) {
  return queue->front == NULL && queue->rear == NULL;
}

/**
 * Push a element into the queue.
 */
void Qpush(Queue* queue, TreeNode* val) {
  QueueNode* node = malloc(sizeof(*node));
  node->val = val;
  if (isQueueEmpty(queue)) {
    node->next = queue->rear;
    queue->front = node;
    queue->rear = node;
    return;
  }
  node->next = queue->rear->next;
  queue->rear->next = node;
  queue->rear = queue->rear->next;
}

/**
 * Pop a element from the queue.
 */
TreeNode* Qpop(Queue* queue) {
  if (isQueueEmpty(queue)) {
    return NULL;
  }
  QueueNode* node = queue->front;
  TreeNode* val = node->val;
  if (queue->front == queue->rear) {
    queue->front = NULL;
    queue->rear = NULL;
  } else {
    queue->front = node->next;
  }
  free(node);
  return val;
}


int main() {
  // define
  int m, n;
  int* preorder = malloc(MAX_SIZE * sizeof(*preorder));
  int* inorder = malloc(MAX_SIZE * sizeof(*inorder));
  TreeNode* root = NULL;
  // input
  scanf("%d %d", &m, &n);
  for (int i = 0; i < m; i++) {
    scanf("%d", &preorder[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &inorder[i]);
  }
  // output
  root = buildTree(preorder, m, inorder, n);
  Queue* queue = calloc(1, sizeof(*queue));
  Qpush(queue, root);
  while (!isQueueEmpty(queue)) {
    TreeNode* node = Qpop(queue);
    if (node == NULL) {
      log("null ");
      free(node);
      node = NULL;
      continue;
    }
    log("%d ", node->val);
    Qpush(queue, node->left);
    Qpush(queue, node->right);
    free(node);
    node = NULL;
  }
  log("\n");
  free(queue);
  queue = NULL;
  root = NULL;
  return 0;
}

