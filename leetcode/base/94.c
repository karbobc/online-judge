#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE (1e2 + 2)
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

/**
 * Create a queue.
 */
Queue* queueCreate() {
  Queue* queue = malloc(sizeof(*queue));
  queue->size = 0;
  queue->capacity = 1 << 4;
  queue->data = malloc(queue->capacity * sizeof(**(queue->data)));
  queue->front = -1;
  queue->rear = -1;
  return queue;
}

/**
 * True is returned when the queue is empty.
 */
bool isQueueEmpty(Queue* queue) {
  return queue->size == 0;
}

/**
 * True is returned when the queue is full.
 */
bool isQueueFull(Queue* queue) {
  return queue->size == queue->capacity;
}

/**
 * Push a tree node into the queue.
 */
void queuePush(Queue* queue, TreeNode* data) {
  // double capacity
  if (isQueueFull(queue)) {
    queue->capacity += queue->capacity;
    TreeNode** a = malloc(queue->capacity * sizeof(**a));
    int n = queue->front;
    int size = queue->size;
    memcpy(a, queue->data+n, (size-n) * sizeof(**a));
    memcpy(a+(size-n), queue->data, n * sizeof(**a));
    queue->front = 0;
    queue->rear = size-1;
  }
  // push
  queue->rear = (queue->rear + 1) % queue->capacity;
  queue->data[queue->rear] = data;
  if (isQueueEmpty(queue)) {
    queue->front = queue->rear;
  }
  queue->size++;
}

/**
 * Pop a tree node from the queue.
 */
TreeNode* queuePop(Queue* queue) {
  if (isQueueEmpty(queue)) {
    return NULL;
  }
  TreeNode* data = queue->data[queue->front];
  queue->front = (queue->front + 1) % queue->capacity;
  queue->size--;
  return data;
}

/**
 * Clear and free the queue.
 */
void queueFree(Queue* queue) {
  while (!isQueueEmpty(queue)) {
    queuePop(queue);
  }
  free(queue);
}

/**
 * Build the binary tree.
 */
TreeNode* buildTree() {
  TreeNode* root = NULL;
  char* s = (char*) malloc((1 << 4) * sizeof(*s));
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
  free(s);
  queueFree(queue);
  return root;
}

/**
 * Delete a binary tree.
 */
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

/**
 * In-Order traversal the binary tree.
 */
int* inorderTraversal(TreeNode* root, int* returnSize) {
    *returnSize = 0;
    int* arr = malloc(MAX_SIZE * sizeof(*arr));
    while (root != NULL) {
      if (root->left == NULL) {
        arr[(*returnSize)++] = root->val;
        root = root->right;
        continue;
      }
      TreeNode* node = root->left;
      while (node->right != NULL && node->right != root) {
        node = node->right;
      }
      if (node->right == NULL) {
        node->right = root;
        root = root->left;
      } else {
        arr[(*returnSize)++] = root->val;
        node->right = NULL;
        root = root->right;
      }
    }
    return arr;
}

int main() {
    // define
    int returnSize;
    int* arr = NULL;
    TreeNode* root = buildTree();
    // output
    arr = inorderTraversal(root, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        log("%d\n", arr[i]);
    }
    // free memory
    free(arr);
    deleteTree(root);
    return 0;
}
