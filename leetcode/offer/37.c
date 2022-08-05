#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SIZE (1e5 + 5)
#define INF 0x3f3f3f3f
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

bool isQueueEmpty(Queue* queue) {
  return queue->front == NULL && queue->rear == NULL;
}

Queue* Qcreate() {
  Queue* queue = malloc(sizeof(*queue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
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

/**
 * Serialize a binary tree.
 */
char* serialize(Tree* root) {
  char* s = malloc(MAX_SIZE * sizeof(*s));
  char* temp = malloc(1e1 * sizeof(*temp));
  s[0] = '\0';
  Queue* queue = Qcreate();
  Qpush(queue, root);
  while (!isQueueEmpty(queue)) {
    TreeNode* node = Qpop(queue);
    if (node == NULL) {
      strcat(s, "NULL,");
      continue;
    }
    snprintf(temp, MAX_SIZE, "%d,", node->val);
    strcat(s, temp);
    Qpush(queue, node->left);
    Qpush(queue, node->right);
  }
  // remove the last `,`
  s[strlen(s)-1] = '\0';
  free(temp);
  temp = NULL;
  free(queue);
  queue = NULL;
  return s;
}

/**
 * find the tree node value in the binary tree that is serialized.
 */
void findTreeNumber(char* str, int* l, int* r, int n, const char* data) {
  int i = 0;
  while (*r <= n) {
    if (data[*r] == ',' || *r == n) {
      while (i < (*r-*l)) {
        str[i] = data[*l+i];
        i++;
      }
      str[i] = '\0';
      *l = ++(*r);
      break;
    }
    (*r)++;
  }
}

/**
 * Deserialize a binary tree.
 */
Tree* deserialize(char* data) {
  int n = strlen(data);
  int l = 0, r = 0;
  char* str = malloc((n+1) * sizeof(*str));
  Tree* root = NULL;
  Queue* queue = Qcreate();
  findTreeNumber(str, &l, &r, n, data);
  if (strcmp("NULL", str) != 0) {
    root = malloc(sizeof(*root));
    root->val = atoi(str);
    Qpush(queue, root);
  }
  while (!isQueueEmpty(queue)) {
    TreeNode* node = Qpop(queue);
    node->left = NULL;
    node->right = NULL;
    findTreeNumber(str, &l, &r, n, data);
    if (strcmp("NULL", str) != 0) {
      node->left = malloc(sizeof(*(node->left)));
      node->left->val = atoi(str);
      Qpush(queue, node->left);
    }
    findTreeNumber(str, &l, &r, n, data);
    if (strcmp("NULL", str) != 0) {
      node->right = malloc(sizeof(*(node->right)));
      node->right->val = atoi(str);
      Qpush(queue, node->right);
    }
  }
  free(str);
  str = NULL;
  free(queue);
  queue = NULL;
  return root;
}

/**
 * build a binary tree.
 */
Tree* buildTree() {
  int val;
  Tree* root = NULL;
  Queue* queue = Qcreate();
  if (~scanf("%d", &val) && val != -1) {
    root = malloc(sizeof(*root));
    root->val = val;
  }
  if (root != NULL) {
    Qpush(queue, root);
  }
  while (!isQueueEmpty(queue)) {
    TreeNode* node = Qpop(queue);
    node->left = NULL;
    node->right = NULL;
    if (~scanf("%d", &val) && val != -1) {
      node->left = malloc(sizeof(*(node->left)));
      node->left->val = val;
      Qpush(queue, node->left);
    }
    if (~scanf("%d", &val) && val != -1) {
      node->right = malloc(sizeof(*(node->right)));
      node->right->val = val;
      Qpush(queue, node->right);
    }
  }
  free(queue);
  queue = NULL;
  return root;
}

/**
 * Delete the binary tree.
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

int main() {
  char* s = NULL;
  Tree* root = buildTree();
  s = serialize(root);
  debug("%s", s);
  root = deserialize(s);
  deleteTree(root);
  free(s);
  s = NULL;
  root = NULL;
  return 0;
}

