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
  unsigned int size;
  QueueNode* front;
  QueueNode* rear;
} Queue;

typedef struct StackNode {
  TreeNode* data;
  struct StackNode* next;
} StackNode, Stack;

/**
 * Create and initialize a queue.
 */
Queue* Qcreate() {
  Queue* queue = malloc(sizeof(*queue));
  queue->size = 0;
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

/**
 * True is returned when the queue is empty.
 */
bool isQueueEmpty(Queue* queue) {
  return queue->front == NULL && queue->rear == NULL;
}

/**
 * Push data into the queue.
 */
void Qpush(Queue* queue, TreeNode* data) {
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

/**
 * Pop data from the queue.
 */
TreeNode* Qpop(Queue* queue) {
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
  node = NULL;
  return data;
}

/**
 * Create and initialize a stack.
 */
Stack* Screate() {
  Stack* stack = malloc(sizeof(*stack));
  stack->next = NULL;
  return stack;
}

/**
 * True is returned when the stack is empty.
 */
bool isStackEmpty(Stack* stack) {
  return stack->next == NULL;
}

/**
 * Push data into the stack.
 */
void Spush(Stack* stack, TreeNode* data) {
  StackNode* node = malloc(sizeof(*node));
  node->data = data;
  node->next = stack->next;
  stack->next = node;
}

/**
 * Pop data from the stack.
 */
TreeNode* Spop(Stack* stack) {
  if (isStackEmpty(stack)) {
    return NULL;
  }
  StackNode* node = stack->next;
  TreeNode* data = node->data;
  stack->next = stack->next->next;
  free(node);
  node = NULL;
  return data;
}

/**
 * Even layers are printed from left to right,
 * odd layers are printed from right to left,
 * and the layer index starts from 0.
 */
int** levelOrder(Tree* root, int* rowSize, int** columnSizes) {
  // initialize
  *rowSize = 0;
  *columnSizes = calloc(MAX_SIZE, sizeof(**columnSizes));
  int** arr = malloc(MAX_SIZE * sizeof(*arr));
  // create a queue and stack.
  Queue* queue = Qcreate();
  Stack* stack = Screate();
  // push root node into the queue when the root is non-null.
  if (root != NULL) {
    Qpush(queue, root);
  }
  // level order traversal the binary tree
  while (!isQueueEmpty(queue)) {
    arr[*rowSize] = malloc(MAX_SIZE * sizeof(**arr));
    for (int i = 0, size = queue->size; i < size; i++) {
      TreeNode* node = Qpop(queue);
      if (*rowSize & 1) {
        Spush(stack, node);
      } else {
        arr[*rowSize][((*columnSizes)[*rowSize])++] = node->val;
      }
      if (node->left != NULL) {
        Qpush(queue, node->left);
      }
      if (node->right != NULL) {
        Qpush(queue, node->right);
      }
    }
    while (!isStackEmpty(stack)) {
      TreeNode* node = Spop(stack);
      arr[*rowSize][((*columnSizes)[*rowSize])++] = node->val;
    }
    (*rowSize)++;
  }
  // free and return
  free(queue);
  queue = NULL;
  free(stack);
  stack = NULL;
  return arr;
}

/**
 * Build a binary tree.
 */
Tree* buildTree() {
  int val;
  Tree* root = NULL;
  Queue* queue = Qcreate();
  if (~scanf("%d", &val) && val != -1) {
    root = malloc(sizeof(*root));
    root->val = val;
    Qpush(queue, root);
  }
  while (!isQueueEmpty(queue)) {
    TreeNode* node = Qpop(queue);
    if (~scanf("%d", &val) && val != -1) {
      node->left = malloc(sizeof(*(node->left)));
      node->left->val = val;
      Qpush(queue, root->left);
    } else {
      node->left = NULL;
    }
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
 * Given a root node, delete the binary tree.
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
  debug("deleted %d", root->val);
  free(root);
  root = NULL;
}

int main() {
  // define
  int rowSize;
  int* columnSizes = NULL;
  int** arr = NULL;
  // input
  Tree* root = buildTree();
  // output
  arr = levelOrder(root, &rowSize, &columnSizes);
  for (int i = 0; i < rowSize; i++) {
    for (int j = 0; j < columnSizes[i]; j++) {
      log("%d ", arr[i][j]);
    }
    log("\n");
  }
  // free memory
  for (int i = 0; i < rowSize; i++) {
    free(arr[i]);
    arr[i] = NULL;
  }
  free(arr);
  arr = NULL;
  free(columnSizes);
  columnSizes = NULL;
  deleteTree(root);
  root = NULL;
  return 0;
}

