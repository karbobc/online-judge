#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

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

Queue* queueCreate() {
  Queue* queue = malloc(sizeof(*queue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

bool isQueueEmpty(Queue* queue) {
  return queue->front == NULL && queue->rear == NULL;
}

void queuePush(Queue* queue, TreeNode* data) {
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

TreeNode* queuePop(Queue* queue) {
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
  return data;
}

void queueFree(Queue* queue) {
  while (!isQueueEmpty(queue)) {
    TreeNode* data = queuePop(queue);
    free(data);
  }
  free(queue);
}

Tree* buildTree() {
  char* s = malloc((1 << 4) * sizeof(*s));
  Tree* root = NULL;
  Queue* queue = queueCreate();
  if (~scanf("%s", s) && strcmp("null", s) != 0) {
    root = malloc(sizeof(*root));
    root->val = atoi(s);
    queuePush(queue, root);
  }
  while (!isQueueEmpty(queue)) {
    TreeNode* node = queuePop(queue);
    node->left = NULL;
    node->right = NULL;
    if (~scanf("%s", s) && strcmp("null", s) != 0) {
      node->left = malloc(sizeof(*(node->left)));
      node->left->val = atoi(s);
      queuePush(queue, node->left);
    }
    if (~scanf("%s", s) && strcmp("null", s) != 0) {
      node->right = malloc(sizeof(*(node->right)));
      node->right->val = atoi(s);
      queuePush(queue, node->right);
    }
  }
  queueFree(queue);
  free(s);
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
}

int maxDepth(Tree* root) {
  if (root == NULL) {
    return 0;
  }
  int left = maxDepth(root->left);
  int right = maxDepth(root->right);
  return 1 + max(left, right);
}

int main() {
  Tree* root = buildTree();
  log("%d\n", maxDepth(root));
  deleteTree(root);
  return 0;
}

