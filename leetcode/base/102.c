#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (2e3 + 3)
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

typedef struct {
  QueueNode* front;
  QueueNode* rear;
  int size;
} Queue;

Queue* queueCreate() {
  Queue* queue = malloc(sizeof(*queue));
  queue->front = NULL;
  queue->rear = NULL;
  queue->size = 0;
  return queue;
}

bool isQueueEmpty(Queue* queue) {
  return queue->front == NULL && queue->rear == NULL;
}

void queuePush(Queue* queue, TreeNode* data) {
  QueueNode* node = malloc(sizeof(*node));
  node->data = data;
  queue->size++;
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
  queue->size--;
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

int** levelOrder(Tree* root, int* m, int** n) {
  *m = 0;
  *n = calloc(MAX_SIZE, sizeof(**n));
  int** arr = malloc(MAX_SIZE * sizeof(*arr));
  Queue* queue = queueCreate();
  if (root != NULL) {
    queuePush(queue, root);
  }
  while (!isQueueEmpty(queue)) {
    int size = queue->size;
    arr[*m] = malloc(size * sizeof(**arr));
    for (int i = 0; i < size; i++) {
      TreeNode* node = queuePop(queue);
      arr[(*m)][(*n)[*m]++] = node->val;
      if (node->left != NULL) {
        queuePush(queue, node->left);
      }
      if (node->right != NULL) {
        queuePush(queue, node->right);
      }
    }
    (*m)++;
  }
  queueFree(queue);
  return arr;
}

Tree* buildTree() {
  Tree* root = NULL;
  char* s = malloc((1 << 3) * sizeof(*s));
  Queue* queue = queueCreate();
  if (~scanf("%s", s) && strcmp(s, "null") != 0) {
    root = malloc(sizeof(*root));
    root->val = atoi(s);
    queuePush(queue, root);
  }
  while (!isQueueEmpty(queue)) {
    TreeNode* node = queuePop(queue);
    node->left = NULL;
    node->right = NULL;
    if (~scanf("%s", s) && strcmp(s, "null") != 0) {
      node->left = malloc(sizeof(*(node->left)));
      node->left->val = atoi(s);
      queuePush(queue, node->left);
    }
    if (~scanf("%s", s) && strcmp(s, "null") != 0) {
      node->right = malloc(sizeof(*(node->right)));
      node->right->val = atoi(s);
      queuePush(queue, node->right);
    }
  }
  free(s);
  queueFree(queue);
  return root;
}

void deleteTree(Tree* root) {
  if (root == NULL) {
    return;
  }
  debug("delete %d", root->val);
  deleteTree(root->left);
  deleteTree(root->right);
  free(root);
}

int main() {
  // define
  int m;
  int* n = NULL;
  int** arr = NULL;
  // input
  Tree* root = buildTree();
  // output and free
  arr = levelOrder(root, &m, &n);
  for (int i = 0; i < m ; i++) {
    for (int j = 0; j < n[i]; j++) {
      log("%d ", arr[i][j]);
    }
    free(arr[i]);
  }
  log("\n");
  free(arr);
  free(n);
  deleteTree(root);
  return 0;
}

