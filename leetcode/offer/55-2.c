#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_SIZE (1e4 + 4)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)
#define max(a, b) (a > b ? a : b)

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

Queue* Qcreate() {
  Queue* queue = malloc(sizeof(*queue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

bool isQueueEmpty(Queue* queue) {
  return queue->front == NULL && queue->rear == NULL;
}

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

Tree* buildTree() {
  int val;
  Tree* root = NULL;
  Queue* queue = Qcreate();
  if (~scanf("%d", &val) && ~val) {
    root = malloc(sizeof(*root));
    root->val = val;
    Qpush(queue, root);
  }
  while (!isQueueEmpty(queue)) {
    TreeNode* node = Qpop(queue);
    node->left = NULL;
    node->right = NULL;
    if (~scanf("%d", &val) && ~val) {
      node->left = malloc(sizeof(*(node->left)));
      node->left->val = val;
      Qpush(queue, node->left);
    }
    if (~scanf("%d", &val) && ~val) {
      node->right = malloc(sizeof(*(node->right)));
      node->right->val = val;
      Qpush(queue, node->right);
    }
  }
  free(queue);
  queue = NULL;
  return root;
}

void deleteTree(Tree* root) {
  if (root == NULL) {
    return;
  }
  deleteTree(root->left);
  deleteTree(root->right);
  debug("deleted %d", root->val);
  free(root);
  root = NULL;
}

int depth(Tree* root) {
  if (root == NULL) {
    return 0;
  }
  int left = depth(root->left);
  if (left == -1) {
    return -1;
  }
  int right = depth(root->right);
  if (right == -1) {
    return -1;
  }
  return abs(left - right) > 1 ? -1 : 1 + max(left, right);
}

bool isBalanced(Tree* root) {
  return depth(root) >= 0;
}

int main() {
  Tree* root = buildTree();
  log(isBalanced(root) ? "true" : "false");
  log("\n");
  deleteTree(root);
  root = NULL;
  return 0;
}

