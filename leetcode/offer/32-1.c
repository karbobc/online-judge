#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE (1e3 + 3)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
} TreeNode, Tree;

typedef struct QueueNode {
  TreeNode* data;
  struct QueueNode* next;
} QueueNode;

typedef struct Queue {
  QueueNode* front;
  QueueNode* rear;
} Queue;

/**
 * True is returned when the queue is empty.
 */
bool isQueueEmpty(Queue* queue) {
  return queue->front == NULL && queue->rear == NULL;
}

/**
 * Create and initialize a queue.
 */
Queue* Qcreate() {
  Queue* queue = malloc(sizeof(*queue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

/**
 * Push data into the queue.
 */
void Qpush(Queue* queue, TreeNode* data) {
  QueueNode* node = malloc(sizeof(*node));
  node->data = data;
  if (isQueueEmpty(queue)) {
    node->next = NULL;
    queue->front = node;
    queue->rear = node;
    return;
  }
  node->next = queue->rear->next;
  queue->rear->next = node;
  queue->rear = queue->rear->next;
}

/**
 * Pop data from the queue.
 */
TreeNode* Qpop(Queue* queue) {
  if (isQueueEmpty(queue)) {
    return NULL;
  }
  QueueNode* node = queue->front;
  TreeNode* data = node->data;
  if (queue->front == queue->rear) {
    queue->front = NULL;
    queue->rear = NULL;
  } else {
    queue->front = queue->front->next;
  }
  free(node);
  node = NULL;
  return data;
}

/**
 * Print each nodes of the binary tree from top to bottom,
 * and the nodes of the same layer are printed from left to right.
 */
int* levelOrder(Tree* root, int* returnSize) {
  int* arr = malloc(MAX_SIZE * sizeof(*arr));
  *returnSize = 0;
  Queue* queue = Qcreate();
  Qpush(queue, root);
  while (!isQueueEmpty(queue)) {
    TreeNode* node = Qpop(queue);
    arr[(*returnSize)++] = node->val;
    if (node->left != NULL) {
      Qpush(queue, node->left);
    }
    if (node->right != NULL) {
      Qpush(queue, node->right);
    }
  }
  free(queue);
  queue = NULL;
  return arr;
}

/**
 * Build a binary tree.
 */
Tree* buildTree() {
  // initialize
  int val;
  Tree* root = NULL;
  Queue* queue = Qcreate();
  // root node
  if (~scanf("%d", &val) && val != -1) {
    root = malloc(sizeof(*root));
    root->val = val;
    root->left = NULL;
    root->right = NULL;
    Qpush(queue, root);
  }
  while (!isQueueEmpty(queue)) {
    TreeNode* node = Qpop(queue);
    // left child
    if (~scanf("%d", &val) && val != -1) {
      node->left = malloc(sizeof(*(node->left)));
      node->left->val = val;
      Qpush(queue, node->left);
    } else {
      node->left = NULL;
    }
    // right child
    if (~scanf("%d", &val) && val != -1) {
      node->right = malloc(sizeof(*(node->right)));
      node->right->val = val;
      Qpush(queue, node->right);
    } else {
      node->right = NULL;
    }
  }
  free(queue);
  queue = NULL;
  return root;
}

/**
 * Delete a binary tree.
 */
void deleteTree(Tree* root) {
  if (root == NULL) {
    return;
  }
  if (root->left != NULL) {
    deleteTree(root->left);
  }
  if (root->right != NULL) {
    deleteTree(root->right);
  }
  debug("delete %d", root->val);
  free(root);
  root = NULL;
  return;
}

int main() {
  // define
  int returnSize;
  int* arr = NULL;
  // input
  Tree* root = buildTree();
  // output
  arr = levelOrder(root, &returnSize);
  for (int i = 0; i < returnSize; i++) {
    log("%d ", arr[i]);
  }
  log("\n");
  // free memory
  free(arr);
  arr = NULL;
  deleteTree(root);
  root = NULL;
  return 0;
}

