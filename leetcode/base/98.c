#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_SIZE (1e4 + 4)
#define log(S, ...) printf(S, ##__VA_ARGS__)
#define debug(S, ...) fprintf(stderr, S"\n", ##__VA_ARGS__)

typedef struct TreeNode {
  int val;
  struct TreeNode* left;
  struct TreeNode* right;
} TreeNode, Tree;

typedef struct {
  int size;
  int capacity;
  TreeNode** data;
  int front;
  int rear;
} Queue;

Queue* queueCreate() {
  Queue* queue = malloc(sizeof(*queue));
  queue->size = 0;
  queue->capacity = 10;
  queue->data = malloc(queue->capacity * sizeof(**(queue->data)));
  queue->front = -1;
  queue->rear = -1;
  return queue;
}

bool isQueueEmpty(Queue* queue) {
  return queue->size == 0;
}

bool isQueueFull(Queue* queue) {
  return queue->size == queue->capacity;
}

void queuePush(Queue* queue, TreeNode* data) {
  if (isQueueFull(queue)) {
    queue->capacity += queue->capacity;
    TreeNode** a = malloc(queue->capacity * sizeof(**(queue->data)));
    int n = queue->front;
    int size = queue->size;
    memcpy(a, queue->data+n, (size-n) * sizeof(**a));
    memcpy(a+(size-n), queue->data, n * sizeof(**a));
    free(queue->data);
    queue->data = a;
    queue->front = 0;
    queue->rear = size-1;
  }
  queue->rear = (queue->rear + 1) % queue->capacity;
  queue->data[queue->rear] = data;
  if (isQueueEmpty(queue)) {
    queue->front = queue->rear;
  }
  queue->size++;
}

TreeNode* queuePop(Queue* queue) {
  if (isQueueEmpty(queue)) {
    return NULL;
  }
  TreeNode* data = queue->data[queue->front];
  queue->size--;
  queue->front = (queue->front + 1) % queue->capacity;
  return data;
}

void queueFree(Queue* queue) {
  while (!isQueueEmpty(queue)) {
    queuePop(queue);
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
      queuePush(queue, node->left);
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
  root = NULL;
}

bool dfs(Tree* root, long l, long r) {
  if (root == NULL) {
    return true;
  }
  if (root->val <= l || root->val >= r) {
    return false;
  }
  return dfs(root->left, l, root->val)
         && dfs(root->right, root->val, r);
}

bool isValidBST(Tree* root) {
  // initialize edge: [l, r] = [-INF, INF]
  return dfs(root, LONG_MIN, LONG_MAX);
}

int main() {
  Tree* root = buildTree();
  log(isValidBST(root) ? "true" : "false");
  log("\n");
  deleteTree(root);
  return 0;
}

