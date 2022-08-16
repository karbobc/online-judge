#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

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
  queue->capacity = 1 << 4;
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
    int n = queue->size;
    int l = queue->front;
    TreeNode** temp = malloc(queue->capacity * sizeof(**temp));
    memcpy(temp, queue->data+l, (n-l) * sizeof(**temp));
    memcpy(temp+(n-l), queue->data, l * sizeof(**temp));
    free(queue->data);
    queue->data = temp;
    queue->front = 0;
    queue->rear = n-1;
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
  queue->front = (queue->front + 1) % queue->capacity;
  queue->size--;
  return data;
}

void queueFree(Queue* queue) {
  while (!isQueueEmpty(queue)) {
    TreeNode* data = queuePop(queue);
    free(data);
  }
  free(queue->data);
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
  free(s);
  queueFree(queue);
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

bool dfs(Tree* root1, Tree* root2) {
  if (root2 == NULL) return true;
  if (root1 == NULL || root1->val != root2->val) return false;
  return dfs(root1->left, root2->left) &&
         dfs(root1->right, root2->right);
}

bool isSubStructure(Tree* root1, Tree* root2) {
  if (root1 == NULL || root2 == NULL) return false;
  return dfs(root1, root2) ||
         isSubStructure(root1->left, root2) ||
         isSubStructure(root1->right, root2);
}

int main() {
  Tree* root1 = buildTree();
  Tree* root2 = buildTree();
  log(isSubStructure(root1, root2) ? "true" : "false");
  log("\n");
  deleteTree(root1);
  deleteTree(root2);
  return 0;
}

